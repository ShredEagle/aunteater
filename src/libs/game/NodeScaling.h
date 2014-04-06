//
//  ComponentPosition.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__NodeScaling__
#define __aunteater__NodeScaling__

#include <set>
#include <typeinfo>

class NodeScaling
{
public:
	static const std::set<const std::type_info *> gComponentTypes;
};

#endif /* defined(__aunteater__NodeScaling__) */
