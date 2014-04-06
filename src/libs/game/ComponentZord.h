//
//  ComponentSprite.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__ComponentZord__
#define __aunteater__ComponentZord__

#include <aunteater/Component.h>

#include <Polycode.h>

#include <string>
#include <memory>

class ComponentZord : public aunteater::Component
{
public:
	ComponentZord(int aZOrder) : aunteater::Component(),
		zOrder(aZOrder)
	{}

	const std::type_info & getTypeInfo()
	{
		return typeid(*this);
	}
public:
	int zOrder;
};

#endif /* defined(__aunteater__ComponentZord__) */
