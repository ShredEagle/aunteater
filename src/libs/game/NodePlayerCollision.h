//
//  ComponentPosition.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__NodePlayerCollision__
#define __aunteater__NodePlayerCollision__

#include <set>
#include <typeinfo>

class NodePlayerCollision
{
public:
	static const std::set<const std::type_info *> gComponentTypes;
};

#endif /* defined(__aunteater__NodePlayerCollision__) */
