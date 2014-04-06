//
//  ComponentSprite.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__SytemCollision__
#define __aunteater__SytemCollision__

#include "Polycode.h"

#include "aunteater\System.h"
#include "aunteater\Engine.h"

#include "ComponentBarrier.h"
#include "ComponentPosition.h"
#include "NodeBarrier.h"
#include "NodePlayerCollision.h"

#include "aunteater\Node.h"

#include <typeinfo>

class SystemCollision : public aunteater::System
{
public:
	SystemCollision(aunteater::Engine & aEngine);
	void addedToEngine(aunteater::Engine &aEngine);
	void update(float time);

public:
	std::list<aunteater::Node> & mBarrierList;
	std::list<aunteater::Node> & mPlayerList;
};

#endif /* defined(__aunteater__SytemCollision__) */
