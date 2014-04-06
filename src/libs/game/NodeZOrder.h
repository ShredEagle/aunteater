//
//  ComponentPosition.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__NodeZOrder__
#define __aunteater__NodeZOrder__

#include <set>
#include <typeinfo>

class NodeZOrder
{
public:
	static const std::set<const std::type_info *> gComponentTypes;
};

#endif /* defined(__aunteater__NodeZOrder__) */
