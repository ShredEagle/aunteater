//
//  ComponentTalkedTo.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef aunteater_ComponentTalkedTo_h
#define aunteater_ComponentTalkedTo_h

#include <aunteater/Component.h>

#include <list>

class ComponentTalkedTo : public aunteater::Component
{
public:
    std::list<std::string> list;
	const std::type_info & getTypeInfo()
	{
		return typeid(*this);
	}
}

#endif
