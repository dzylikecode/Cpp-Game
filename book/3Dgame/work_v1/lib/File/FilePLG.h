#ifndef HUI_FILE_PLG_H
#define HUI_FILE_PLG_H

#include <fstream>
#include <iostream>
#include <string>
#include "basic.hpp"
#include <string>
#include <vector>
#include "Geometric/Geometric_v2.h"

namespace hui
{
    namespace triD
    {
        class FilePLG : public Data3D_v2
        {
        private:
            std::ifstream m_file;
            std::string m_obj_name;
            std::size_t m_num_vert;
            std::size_t m_num_poly;

        public:
            bool open(const std::string &filename);
            std::string getLine();
            bool eof() { return m_file.eof(); }
            std::string getObjName() const { return m_obj_name; }
            const Data3D_v2 &getData() const { return *this; }

        private:
            bool analyze_file();
        };
    }
}
#endif