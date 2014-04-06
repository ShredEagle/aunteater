//
//  NodeInteraction.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__NodeInteraction__
#define __aunteater__NodeInteraction__

#include <set>
#include <typeinfo>

class NodeInteraction
{
public:
	static const std::set<const std::type_info *> gComponentTypes;
};

#endif /* defined(__aunteater__NodePlayerCollision__) */
