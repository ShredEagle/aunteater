#include "ImageReader.h"

#define cimg_display 0
#define cimg_use_jpeg
#include "CImg.h"

using namespace tutorial;

ImageReader::ImageReader(const std::string &aFilename)
{
    mDatastore =  std::make_unique<cimg_library::CImg<GLfloat>>(aFilename.c_str());
    mDatastore->normalize(0., 1.);
    mDatastore->mirror('y');
    mWidth = mDatastore->width();
    mHeight = mDatastore->height();
    mDatastore->permute_axes("cxyz"); //must be done after saving the width and height, because it also 'permutes' them.
    mData = mDatastore->data();
}

Image::~Image()
{}
