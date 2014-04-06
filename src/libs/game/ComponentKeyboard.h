//
//  ComponentPosition.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__ComponentKeyboard__
#define __aunteater__ComponentKeyboard__

#include <Polycode.h>
#include <aunteater/Component.h>
#include <memory>

class ComponentKeyboard : public aunteater::Component
{
public:
	ComponentKeyboard() : aunteater::Component()
	{}

	const std::type_info & getTypeInfo()
	{
		return typeid(*this);
	}
};

#endif /* defined(__aunteater__ComponentKeyboard__) */
