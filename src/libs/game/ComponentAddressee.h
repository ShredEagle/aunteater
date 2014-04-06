//
//  ComponentAddressee.h
//  aunteater
//
//  Created by Adrien on 06/04/14.
//
//

#ifndef aunteater_ComponentAddressee_h
#define aunteater_ComponentAddressee_h

#include <aunteater/Component.h>

#include <string>

class ComponentAddressee : public aunteater::Component
{
public:
    	const std::type_info & getTypeInfo()
	{
		return typeid(*this);
	}
    ComponentAddressee() : Component()
    {}
    
    std::string entityName;
    
};

#endif
