//
//  ComponentSprite.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__ComponentZBoundary__
#define __aunteater__ComponentZBoundary__

#include <aunteater/Component.h>

#include <Polycode.h>

#include <string>
#include <memory>

class ComponentZBoundary : public aunteater::Component
{
public:
	ComponentZBoundary(int aYBoundary,int aZBoundary) : aunteater::Component(),
		yBoundary(aYBoundary),
		zBoundary(aZBoundary)
	{}

	const std::type_info & getTypeInfo()
	{
		return typeid(*this);
	}
public:
	int yBoundary;
	int zBoundary;
};

#endif /* defined(__aunteater__ComponentZBoundary__) */
