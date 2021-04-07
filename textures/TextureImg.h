#ifndef OPENGL_TEXTUREIMG_H
#define OPENGL_TEXTUREIMG_H

#include <stb/stb_image.h>
#include <stb/stb_image_write.h>
#include <stb/stb_image_resize.h>
#include <string>
#include <array>
#include <iostream>

const std::array<int, 14> resLookUp
{
        2,     4,    8,     16,
        32,    64,   128,  256,    512,
        1024, 2048, 4096, 8192, 16384
};

class TextureImg
{
    public:
        TextureImg(const std::string& path, bool makeMipMap = false);
        void CreateMipMap(unsigned int numOfLevels);
        void SaveMipMapPackage(const std::string& path);


        inline unsigned char* Data() const { return mainBmpPtr; }
        inline unsigned char* DataMM(unsigned int level) const { return (level < mipMapLevels) ? mipMapBmpPtrs[level] : nullptr; }

        inline int Width(unsigned int level) const { return (mipMapLevels - level > 0) ? resLookUp[mipMapLevels - level - 1] : resLookUp[0]; }
        inline int Height(unsigned int level) const { return (mipMapLevels - level > 0) ? resLookUp[mipMapLevels - level - 1] : resLookUp[0];  }
        inline int Width() const { return width; }
        inline int Height() const { return height; }
        inline int mipMapLvls() const { return mipMapLevels; }
        inline int channles() const { return channels; }


    private:
        int channels = 0;
        int width = 0;
        int height = 0;
        int mipMapLevels = 0;
        unsigned char* mainBmpPtr = nullptr;
        unsigned char** mipMapBmpPtrs = nullptr;

};


#endif
