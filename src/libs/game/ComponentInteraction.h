//
//  ComponenInteraction.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef aunteater_ComponenInteraction_h
#define aunteater_ComponenInteraction_h

#include <aunteater/Component.h>
#include "InteractionHandler.h"

class ComponentInteraction : public aunteater::Component
{
public:
	ComponentInteraction(InteractionHandler * aHandler,int x1,int y1,int x2, int y2) :
		mHandler(aHandler),
		x1(x1),
		x2(x2),
		y1(y1),
		y2(y2),
		active(true)
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
	InteractionHandler * mHandler;
	bool active;
};

#endif
