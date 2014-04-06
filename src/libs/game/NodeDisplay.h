//
//  ComponentPosition.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__NodeDisplay__
#define __aunteater__NodeDisplay__

#include <set>
#include <typeinfo>

class NodeDisplay
{
public:
	static const std::set<const std::type_info *> gComponentTypes;
};

#endif /* defined(__aunteater__NodeDisplay__) */
