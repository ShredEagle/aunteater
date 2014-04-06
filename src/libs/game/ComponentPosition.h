//
//  ComponentPosition.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__ComponentPosition__
#define __aunteater__ComponentPosition__

#include <aunteater/Component.h>

class ComponentPosition : public aunteater::Component
{
public:
	ComponentPosition(float x, float y) : Component(),
		x(x), y(y)
    {}

	const std::type_info & getTypeInfo()
	{
		return typeid(*this);
	}
public:
	float x;
	float y;
    
};

#endif /* defined(__aunteater__ComponentPosition__) */
