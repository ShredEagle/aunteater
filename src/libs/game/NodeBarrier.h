//
//  ComponentPosition.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__NodeBarrier__
#define __aunteater__NodeBarrier__

#include <set>
#include <typeinfo>

class NodeBarrier
{
public:
	static const std::set<const std::type_info *> gComponentTypes;
};

#endif /* defined(__aunteater__NodeBarrier__) */
