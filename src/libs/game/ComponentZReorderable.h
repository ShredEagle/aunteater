//
//  ComponentSprite.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__ComponentZReorderable__
#define __aunteater__ComponentZReorderable__

#include <aunteater/Component.h>

#include <Polycode.h>

#include <string>
#include <memory>

class ComponentZReorderable : public aunteater::Component
{
public:
	ComponentZReorderable() : aunteater::Component()
	{}

	const std::type_info & getTypeInfo()
	{
		return typeid(*this);
	}
};

#endif /* defined(__aunteater__ComponentZReorderable__) */
