//
//  ComponentPosition.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__NodeControl__
#define __aunteater__NodeControl__

#include <set>
#include <typeinfo>

class NodeControl
{
public:
	static const std::set<const std::type_info *> gComponentTypes;
};

#endif /* defined(__aunteater__NodeControl__) */
