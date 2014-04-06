//
//  ComponentSprite.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__SystemZReorder__
#define __aunteater__SystemZReorder__

#include <aunteater/System.h>
#include <aunteater/Engine.h>
#include <aunteater/Node.h>

#include "ComponentZord.h"
#include "ComponentZBoundary.h"
#include "ComponentPosition.h"
#include "NodeZOrder.h"
#include "NodeZBoundary.h"

class SystemZReorder : public aunteater::System
{
public:
	SystemZReorder(aunteater::Engine & aEngine);
	void addedToEngine(aunteater::Engine &aEngine);
	void update(float time);

public:
	std::list<aunteater::Node> & mZOrderedList;
	std::list<aunteater::Node> & mZBoundariesList;
};

#endif /* defined(__aunteater__SystemZReorder__) */
