//
//  ComponentPosition.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__NodeMoveAnimation__
#define __aunteater__NodeMoveAnimation__

#include <set>
#include <typeinfo>

class NodeMoveAnimation
{
public:
	static const std::set<const std::type_info *> gComponentTypes;
};

#endif /* defined(__aunteater__NodeMoveAnimation__) */
