#include "TextureImg.hpp"
#include <math.h>



TextureImg::TextureImg(const std::string& _path, bool _makeMipMap)
{
    mainBmpPtr = stbi_load(_path.c_str(), &width, &height, &channels, 0);
    dataSize = ((width*channels) * height) * sizeof(unsigned char);

    if(mainBmpPtr == nullptr)
    {
        std::cerr << "TextureImg.h :: error of image loading\n";
        return;
    }


    if(_makeMipMap)
        this->CreateMipMap(log2((width < height) ? width : height));
}

void TextureImg::CreateMipMap(unsigned int _numOfLevels)
{
    if(mainBmpPtr == nullptr)
    {
        std::cerr << "TextureImg.h :: no source image for mipmapping founded\n";
        return;
    }
    dataSize = 0;

    mipMapLevels = _numOfLevels + 1;
    mipMapBmpPtrs = new unsigned char*[mipMapLevels];
    mipMapDataSizes = new int[mipMapLevels];

    mipMapBmpPtrs[0] = new unsigned char[resLookUp[_numOfLevels] * resLookUp[_numOfLevels] * channels];
    stbir_resize_uint8(mainBmpPtr, width, height, channels*width,
                       mipMapBmpPtrs[0], resLookUp[_numOfLevels], resLookUp[_numOfLevels],
                       channels*resLookUp[_numOfLevels], channels);

    dataSize += resLookUp[_numOfLevels] * resLookUp[_numOfLevels] * channels * sizeof(unsigned char);
    mipMapDataSizes[0] = dataSize;

    delete[] mainBmpPtr;

    mainBmpPtr = nullptr;

    width = height = resLookUp[_numOfLevels];

    for(unsigned int i = 1; i <= _numOfLevels; i++)
    {
        mipMapBmpPtrs[i] = new unsigned char[resLookUp[_numOfLevels - i] * resLookUp[_numOfLevels - i] * channels];

        stbir_resize_uint8(mipMapBmpPtrs[i - 1],
                           resLookUp[_numOfLevels - i + 1],
                           resLookUp[_numOfLevels - i + 1],
                           channels * resLookUp[_numOfLevels - i + 1],
                           mipMapBmpPtrs[i],
                           resLookUp[_numOfLevels - i],
                           resLookUp[_numOfLevels - i],
                           channels * resLookUp[_numOfLevels - i],
                           channels);

        mipMapDataSizes[i] = resLookUp[_numOfLevels - i] * resLookUp[_numOfLevels - i] * channels * sizeof(unsigned char);
        dataSize += mipMapDataSizes[i];
    }

    stbi_image_free(mainBmpPtr);
}

void TextureImg::SaveMipMapPackage(const std::string& _path)
{
    if(mipMapLevels == 0)
    {
        std::cerr << "TextureImg.h :: create mipmap before saving it\n";
        return;
    }

    for(unsigned int i = 0; i < mipMapLevels; i++)
        stbi_write_png((_path+"/level0"+std::to_string(i)+".png").c_str(), resLookUp[mipMapLevels - i - 1], resLookUp[mipMapLevels - i - 1],
                       channels, mipMapBmpPtrs[i], channels*resLookUp[mipMapLevels  -  i - 1]);

}

TextureImg::~TextureImg()
{
    if(mipMapBmpPtrs != nullptr)
        for(int i=0; i<mipMapLevels; i++)
            delete [] mipMapBmpPtrs[i];

    if(mainBmpPtr != nullptr)
        delete [] mainBmpPtr;

    if(mipMapDataSizes != nullptr)
        delete [] mipMapDataSizes;
}