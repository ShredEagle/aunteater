//
//  ComponentPosition.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__NodeDepth__
#define __aunteater__NodeDepth__

#include <set>
#include <typeinfo>

class NodeDepth
{
public:
	static const std::set<const std::type_info *> gComponentTypes;
};

#endif /* defined(__aunteater__NodeDepth__) */
