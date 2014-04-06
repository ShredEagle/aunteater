//
//  NodeActor.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__NodeActor__
#define __aunteater__NodeActor__

#include <set>
#include <typeinfo>

class NodeActor
{
public:
	static const std::set<const std::type_info *> gComponentTypes;
};

#endif /* defined(__aunteater__NodeActor__) */
