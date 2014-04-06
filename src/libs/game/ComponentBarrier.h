//
//  ComponentPosition.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__ComponentBarrier__
#define __aunteater__ComponentBarrier__

#include <aunteater/Component.h>

class ComponentBarrier : public aunteater::Component
{
public:
	ComponentBarrier(float x1, float y1, float x2, float y2) : Component(),
		x1(x1), y1(y1), x2(x2), y2(y2)
	{}

	const std::type_info & getTypeInfo()
	{
		return typeid(*this);
	}
public:
	float x1;
	float y1;
	float x2;
	float y2;

};

#endif /* defined(__aunteater__ComponentBarrier__) */
