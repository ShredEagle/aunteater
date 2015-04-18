//
//  ImageReader.h
//
//  Created by Adrien David.
//
//

#ifndef tutorial_ImageReader_h
#define tutorial_ImageReader_h

#include "Globals.h"

#include <string>

namespace cimg_library
{
    template <class> class CImg;
}

namespace tutorial
{

struct Image
{
    GLfloat *mData = nullptr;
    unsigned mWidth = 0;
    unsigned mHeight = 0;

    // the default ctor has to be implemented in the cpp file.
    ~Image();
    
protected:
    std::unique_ptr<cimg_library::CImg<GLfloat>> mDatastore;
};

class ImageReader : public Image
{
public:
    ImageReader(const std::string &aFilename);
};

} // namespace tutorial

#endif
