#pragma once

#ifdef STB_SDL_FONT_IMPORTANTIONAL
#include <SDL.h>
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>
#endif

#include <SDL.h>
#include <stb_truetype.h>
#include <stdio.h>

class stb_SDL_font
{
private:
    /* prepare font */
    stbtt_fontinfo info;
    unsigned char *fontBuffer = NULL;
public:
    bool open(const char *filename)
    {
        /* load font file */
        long size;
        FILE *fontFile = fopen(filename, "rb");
        fseek(fontFile, 0, SEEK_END);
        size = ftell(fontFile);       /* how long is the file ? */
        fseek(fontFile, 0, SEEK_SET); /* reset */

        fontBuffer = (unsigned char *)malloc(size);

        fread(fontBuffer, size, 1, fontFile);
        fclose(fontFile);
        if (!stbtt_InitFont(&info, fontBuffer, 0))
        {
            printf("failed\n");
            free(fontBuffer);
            fontBuffer = NULL;
            return false;
        }
        return true;
    }
};
