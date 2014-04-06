//
//  ComponentPosition.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__NodeMove__
#define __aunteater__NodeMove__

#include <set>
#include <typeinfo>

class NodeMove
{
public:
	static const std::set<const std::type_info *> gComponentTypes;
};

#endif /* defined(__aunteater__NodeMove__) */
