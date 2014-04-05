//
//  ComponentSprite.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__ComponentSprite__
#define __aunteater__ComponentSprite__

#include <aunteater/Component.h>

#include <Polycode.h>

#include <string>

class ComponentSprite : public aunteater::Component
{
public:
    ComponentSprite(const std::string &aFile) : aunteater::Component(),
    image(new Polycode::ScreenImage(aFile))
    {}
    
public:
    std::shared_ptr<Polycode::ScreenImage> image;
};

#endif /* defined(__aunteater__ComponentSprite__) */
