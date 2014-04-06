//
//  ComponentAlignment.h
//  aunteater
//
//  Created by Adrien on 06/04/14.
//
//

#ifndef aunteater_ComponentAlignment_h
#define aunteater_ComponentAlignment_h

#include <aunteater/Component.h>

class ComponentAlignment : public aunteater::Component
{
public:
   	const std::type_info & getTypeInfo()
	{
		return typeid(*this);
	}
    std::string sign;
};


#endif
