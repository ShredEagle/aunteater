//
//  ComponentSprite.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__ComponentScale__
#define __aunteater__ComponentScale__

#include <aunteater/Component.h>

#include <Polycode.h>

#include <string>
#include <memory>

class ComponentScale : public aunteater::Component
{
public:
	ComponentScale() : aunteater::Component()
	{}

	const std::type_info & getTypeInfo()
	{
		return typeid(*this);
	}
};

#endif /* defined(__aunteater__ComponentScale__) */
