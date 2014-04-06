//
//  ComponentDrugState.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef aunteater_ComponentDrugState_h
#define aunteater_ComponentDrugState_h

#include <aunteater/Component.h>

class ComponentDrugState : public aunteater::Component
{
public:
    	const std::type_info & getTypeInfo()
	{
		return typeid(*this);
	}
    std::string name;
//    enum class drug
//    {
//        COKE,
//        SPRITE
//    };
};

#endif
