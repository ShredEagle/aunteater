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
#include <memory>

class ComponentSprite : public aunteater::Component
{
public:
	ComponentSprite(const std::string &aFile, Number width, Number height,Number scaleX,Number scaleY) : aunteater::Component(),
		image(new Polycode::ScreenSprite(aFile,width,height))
    {
		image->setScale(scaleX, scaleY);
	}

	const std::type_info & getTypeInfo()
	{
		return typeid(*this);
	}
    
public:
    std::shared_ptr<Polycode::ScreenSprite> image;
};

#endif /* defined(__aunteater__ComponentSprite__) */
