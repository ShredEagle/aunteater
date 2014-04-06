//
//  ComponentPosition.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__NodeAnimation__
#define __aunteater__NodeAnimation__

#include <set>
#include <typeinfo>

class NodeAnimation
{
public:
	static const std::set<const std::type_info *> gComponentTypes;
};

#endif /* defined(__aunteater__NodeAnimation__) */
