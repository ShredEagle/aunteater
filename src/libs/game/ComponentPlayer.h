//
//  ComponentSprite.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__ComponentPlayer__
#define __aunteater__ComponentPlayer__

#include <aunteater/Component.h>

#include <Polycode.h>

#include <string>
#include <memory>

class ComponentPlayer : public aunteater::Component
{
public:
	ComponentPlayer() : aunteater::Component()
	{}

	const std::type_info & getTypeInfo()
	{
		return typeid(*this);
	}
};

#endif /* defined(__aunteater__ComponentPlayer__) */
