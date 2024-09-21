#include "../include/SXL.h"

__SXL_NAMESPACE_BEGIN
__SXL_SUB_NAMESPACE(utils, inline)
{
    SDL_Texture *texture_exceptions::blank_texture = nullptr;

    SDL_Texture *create_sdl_texture_from_bitfield(SDL_Renderer * ren, MVector<MVector<int>> data)
    {
        int  width  = (int)data.size();
        int  height = (int)data.size();
        int *pixels = AMALLOC_ARRAY(pixels, (width * height));
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                int           brightness      = data[x][y];
                unsigned char grayscale_value = (brightness * 255) / 100;
                unsigned int  color           = (255 << 24) | (grayscale_value << 16) |
                                     (grayscale_value << 8) | grayscale_value;
                pixels[y * width + x] = (int)color;
            }
        }
        /* The pitch is the number of bytes per row, which is width * 4 (for 32-bit RGBA) */
        int pitch = width * 4;
        /* Create a surface from the pixel data using the correct SDL3 function */
        SDL_Surface *surface =
            SDL_CreateSurfaceFrom(width, height, SDL_PIXELFORMAT_RGBA32, pixels, pitch);
        if (surface == nullptr)
        {
            /* Handle error in case SDL_CreateSurfaceFrom fails */
            logE("Failed to create surface: %s", SDL_GetError());
            free(pixels);
            return nullptr;
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surface);
        if (texture == nullptr)
        {
            logE("Failed to create texture from bitfield surface, SDL_ERROR: %s.", SDL_GetError());
        }
        SDL_DestroySurface(surface);
        free(pixels);
        return texture;
    }
}
__SXL_NAMESPACE_END
