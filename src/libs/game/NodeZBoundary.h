//
//  ComponentPosition.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__NodeZBoundary__
#define __aunteater__NodeZBoundary__

#include <set>
#include <typeinfo>

class NodeZBoundary
{
public:
	static const std::set<const std::type_info *> gComponentTypes;
};

#endif /* defined(__aunteater__NodeZBoundary__) */
