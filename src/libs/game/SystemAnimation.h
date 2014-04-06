//
//  ComponentSprite.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__SystemAnimation__
#define __aunteater__SystemAnimation__

#include <aunteater/System.h>
#include <aunteater/Engine.h>
#include <aunteater/Node.h>

#include "ComponentSprite.h"
#include "ComponentAnimationState.h"
#include "NodeAnimation.h"


class SystemAnimation : public aunteater::System
{
public:
	SystemAnimation(aunteater::Engine & aEngine);
	void addedToEngine(aunteater::Engine &aEngine);
	void update(float time);

public:
	std::list<aunteater::Node> & mNodeList;
};

#endif /* defined(__aunteater__SystemAnimation__) */
