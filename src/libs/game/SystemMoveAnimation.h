//
//  ComponentSprite.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__SystemMoveAnimation__
#define __aunteater__SystemMoveAnimation__

#include <aunteater/System.h>
#include <aunteater/Engine.h>
#include <aunteater/Node.h>
#include "ComponentSpeed.h"
#include "ComponentAnimationState.h"
#include "NodeMoveAnimation.h"


class SystemMoveAnimation : public aunteater::System
{
public:
	SystemMoveAnimation(aunteater::Engine & aEngine);
	void addedToEngine(aunteater::Engine &aEngine);
	void update(float time);

public:
	std::list<aunteater::Node> & mNodeList;
};

#endif /* defined(__aunteater__SystemMoveAnimation__) */
