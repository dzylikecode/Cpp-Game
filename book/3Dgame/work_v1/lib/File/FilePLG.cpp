#include "File/FilePLG.h"
#include <regex>

// defines for enhanced PLG file format -> PLX
// the surface descriptor is still 16-bit now in the following format
// d15                      d0
//   CSSD | RRRR| GGGG | BBBB

// C is the RGB/indexed color flag
// SS are two bits that define the shading mode
// D is the double sided flag
// and RRRR, GGGG, BBBB are the red, green, blue bits for RGB mode
// or GGGGBBBB is the 8-bit color index for 8-bit mode

// bit masks to simplify testing????
#define PLX_RGB_MASK 0x8000        // mask to extract RGB or indexed color
#define PLX_SHADE_MODE_MASK 0x6000 // mask to extract shading mode
#define PLX_2SIDED_MASK 0x1000     // mask for double sided
#define PLX_COLOR_MASK 0x0fff      // xxxxrrrrggggbbbb, 4-bits per channel RGB
                                   // xxxxxxxxiiiiiiii, indexed mode 8-bit index

#define PLX_COLOR_MODE_RGB_FLAG 0x8000       // this poly uses RGB color
#define PLX_COLOR_MODE_INDEXED_FLAG 0x0000   // this poly uses an indexed 8-bit color
#define PLX_2SIDED_FLAG 0x1000               // this poly is double sided
#define PLX_1SIDED_FLAG 0x0000               // this poly is single sided
#define PLX_SHADE_MODE_PURE_FLAG 0x0000      // this poly is a constant color
#define PLX_SHADE_MODE_CONSTANT_FLAG 0x0000  // alias
#define PLX_SHADE_MODE_FLAT_FLAG 0x2000      // this poly uses flat shading
#define PLX_SHADE_MODE_GOURAUD_FLAG 0x4000   // this poly used gouraud shading
#define PLX_SHADE_MODE_PHONG_FLAG 0x6000     // this poly uses phong shading
#define PLX_SHADE_MODE_FASTPHONG_FLAG 0x6000 // this poly uses phong shading (alias)

namespace
{
    const std::string WHITESPACE = " \n\r\t\f\v";

    std::string ltrim(const std::string &s)
    {
        size_t start = s.find_first_not_of(WHITESPACE);
        return (start == std::string::npos) ? "" : s.substr(start);
    }

    std::string rtrim(const std::string &s)
    {
        size_t end = s.find_last_not_of(WHITESPACE);
        return (end == std::string::npos) ? "" : s.substr(0, end + 1);
    }

    std::string trim(const std::string &s)
    {
        return rtrim(ltrim(s));
    }
}

namespace hui
{
    namespace triD
    {
        bool FilePLG::open(const std::string &filename)
        {
            auto ext = filename.substr(filename.find_last_of('.') + 1);
            if (ext != "plg" && ext != "PLG" &&
                ext != "plx" && ext != "PLX")
            {
                spdlog::warn("file extension should be .plg or .plx");
            }
            m_file.open(filename);
            return m_file.is_open() && analyze_file();
        }

        std::string FilePLG::getLine()
        {
            std::string line;
            std::regex re;
            std::string pattern;
            while (!m_file.eof())
            {
                std::getline(m_file, line);

                // skip the heading blank space
                // pattern = R"(^\s*(?=\S))";
                // re.assign(pattern);
                // line = regex_replace(line, re, "");
                line = ltrim(line);
                // skip the comment line or empty line
                // \r is for windows file in linux
                if (line.empty() || line[0] == '#' || line[0] == '\r')
                {
                    continue;
                }
                if (line[line.length() - 1] == '\r') // remove the \r
                {
                    line.erase(line.length() - 1);
                }
                break;
            }
            return line;
        }

        bool FilePLG::analyze_file()
        {
            std::string line;
            std::regex re;
            std::string pattern;
            std::cmatch m;
            // 第一部分是描述性文件
            // # object descriptor
            // object_name_string num_verts_int num_polys_int
            line = getLine();
            if (line.empty())
            {
                spdlog::error("no object descriptor");
                return false;
            }

            pattern = R"((\w+)\s+(\d+)\s+(\d+).*)";
            re.assign(pattern);
            if (!regex_match(line.c_str(), m, re))
            {
                spdlog::error("incorrect object descriptor");
                return false;
            }
            m_obj_name = m[1];
            m_num_vert = std::stoi(m[2]);
            m_num_poly = std::stoi(m[3]);

            spdlog::info("object descriptor: \n"
                         "name: {} \n"
                         "vert: {} \n"
                         "poly: {} \n",
                         m_obj_name, m_num_vert, m_num_poly);
            // 第二部分是顶点数据
            // # vertex list
            // x0_float y0_float z0_float
            // x1_float y1_float z1_float
            // x2_float y2_float z2_float
            // .
            // .
            // xn_float yn_float zn_float
            m_vert.resize(m_num_vert);
            for (std::size_t i = 0; i < m_num_vert; ++i)
            {
                line = getLine();
                if (line.empty())
                {
                    spdlog::error("no vertex data -> line {}", i);
                    return false;
                }
                pattern = R"(([-+]?[0-9]*\.?[0-9]+)\s+)"
                          R"(([-+]?[0-9]*\.?[0-9]+)\s+)"
                          R"(([-+]?[0-9]*\.?[0-9]+))"
                          R"(.*)";
                re.assign(pattern);
                if (!regex_match(line.c_str(), m, re))
                {
                    spdlog::error("incorrect vertex data -> line {}", i);
                    return false;
                }
                X(m_vert[i]) = std::stof(m[1]);
                Y(m_vert[i]) = std::stof(m[2]);
                Z(m_vert[i]) = std::stof(m[3]);

                spdlog::info("vertex data: \n"
                             "x: {} \n"
                             "y: {} \n"
                             "z: {} \n",
                             X(m_vert[i]), Y(m_vert[i]), Z(m_vert[i]));
            }

            estimate_radius();
            spdlog::info("\n"
                         "max radius: {} \n"
                         "avg radius: {} \n",
                         m_max_radius, m_avg_radius);

            // 第三部分是三角形数据
            // # polygon list
            // surface_description_ushort num_verts_int v0_index_int v1_index_int ..  vn_index_int
            // .
            // .
            // surface_description_ushort num_verts_int v0_index_int v1_index_int ..  vn_index_int
            m_poly.resize(m_num_poly);
            for (std::size_t i = 0; i < m_num_poly; ++i)
            {
                line = getLine();

                if (line.empty())
                {
                    spdlog::error("no polygon data -> line {}", i);
                    return false;
                }
                pattern = R"((0[xX][0-9a-fA-F]+|\d+)\s+)" // hex or decimal
                          R"((\d+)\s+)"
                          R"((\d+)\s+)"
                          R"((\d+)\s+)"
                          R"((\d+))"
                          R"(.*)";

                re.assign(pattern);
                if (!regex_match(line.c_str(), m, re))
                {
                    spdlog::error("incorrect polygon data -> line {}", i);
                    return false;
                }
                if (m[2].str() != "3")
                {
                    spdlog::error("{} not supported ", m[2].str());
                    spdlog::error("polygon data must be 3 -> line {}", i);
                    return false;
                }

                spdlog::info("polygon data: \n"
                             "surface: {} \n"
                             "num vert: {} \n"
                             "v0: {} \n"
                             "v1: {} \n"
                             "v2: {} \n",
                             m[1].str(), m[2].str(),
                             m[3].str(), m[4].str(),
                             m[5].str());
                m_poly[i][0] = std::stoi(m[3]);
                m_poly[i][1] = std::stoi(m[4]);
                m_poly[i][2] = std::stoi(m[5]);

                m_poly[i].attr = Poly_v1::Attribute::ATTR_NONE;
                decltype(std::stoi(m[3])) attr;
                if (m[1].str().substr(0, 2) == "0x" ||
                    m[1].str().substr(0, 2) == "0X")
                {
                    attr = std::stoi(m[1].str(), nullptr, 16);
                }
                else
                {
                    attr = std::stoi(m[1]);
                }

                if (attr & PLX_2SIDED_FLAG)
                {
                    m_poly[i].attr |= Poly_v1::Attribute::SIDED_DOUBLE;
                    spdlog::info("double sided");
                }
                else /*if (attr & PLX_1SIDED_FLAG)*/
                {
                    m_poly[i].attr |= Poly_v1::Attribute::SIDED_SINGLE;
                    spdlog::info("single sided");
                }
                // else
                // {
                //     spdlog::error("unknown polygon attribute");
                //     return false;
                // }
                // this is an RGB 4.4.4 surface

                if (attr & PLX_COLOR_MODE_RGB_FLAG)
                {
                    spdlog::info("color mode: RGB 16 bit");

#define PLX_RGB_RED_MASK 0x0F00
#define PLX_RGB_GREEN_MASK 0x00F0
#define PLX_RGB_BLUE_MASK 0x000F
                    typedef decltype(m_poly[i].color.r) Color_part_t;
                    Color_part_t red = (attr & PLX_RGB_RED_MASK) >> 8;
                    Color_part_t green = (attr & PLX_RGB_GREEN_MASK) >> 4;
                    Color_part_t blue = attr & PLX_RGB_BLUE_MASK;
                    // convert to 8.8.8
                    red <<= 4;
                    green <<= 4;
                    blue <<= 4;
                    m_poly[i].color = Color(red, green, blue);

                    spdlog::info("color: "
                                 "[r: {} g: {} b: {}]",
                                 m_poly[i].color.r,
                                 m_poly[i].color.g,
                                 m_poly[i].color.b);
                }
                else /*if (attr & PLX_COLOR_MODE_INDEXED_FLAG)*/
                {
                    spdlog::info("color mode: RGBA 8 bit");
#define PLX_INDEXED_RED_8_MASK 0xE0
#define PLX_INDEXED_GREEN_8_MASK 0x1C
#define PLX_INDEXED_BLUE_8_MASK 0x03
                    typedef decltype(m_poly[i].color.r) Color_part_t;
                    Color_part_t red = (attr & PLX_INDEXED_RED_8_MASK) >> 5;
                    Color_part_t green = (attr & PLX_INDEXED_GREEN_8_MASK) >> 2;
                    Color_part_t blue = attr & PLX_INDEXED_BLUE_8_MASK;
                    red <<= 5;
                    green <<= 5;
                    blue <<= 6;
                    m_poly[i].color = Color(red, green, blue);

                    spdlog::info("color: "
                                 "[r: {} g: {} b: {}]",
                                 m_poly[i].color.r,
                                 m_poly[i].color.g,
                                 m_poly[i].color.b);
                }
                // else
                // {
                //     spdlog::error("unknown color mode");
                //     return false;
                // }

                auto shade = attr & PLX_SHADE_MODE_MASK;
                switch (shade)
                {
                case PLX_SHADE_MODE_FLAT_FLAG:
                    m_poly[i].attr |= Poly_v1::Attribute::SHADE_FLAT;
                    spdlog::info("shade mode: flat");
                    break;
                case PLX_SHADE_MODE_GOURAUD_FLAG:
                    m_poly[i].attr |= Poly_v1::Attribute::SHADE_GOURAUD;
                    spdlog::info("shade mode: gouraud");
                    break;
                case PLX_SHADE_MODE_PHONG_FLAG:
                    m_poly[i].attr |= Poly_v1::Attribute::SHADE_PHONG;
                    spdlog::info("shade mode: phong");
                    break;
                default:
                    spdlog::warn("unknown shade mode");
                    break;
                }
            }
            return true;
        }
    }
}