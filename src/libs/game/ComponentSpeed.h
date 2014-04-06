//
//  ComponentPosition.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__ComponentSpeed__
#define __aunteater__ComponentSpeed__

#include <aunteater/Component.h>
#include <memory>

class ComponentSpeed : public aunteater::Component
{
public:
	ComponentSpeed() : aunteater::Component(),
		vX(0),
		vY(0)
	{}

	const std::type_info & getTypeInfo()
	{
		return typeid(*this);
	}
public:
	double vX;
	double vY;

};

#endif /* defined(__aunteater__ComponentSpeed__) */
