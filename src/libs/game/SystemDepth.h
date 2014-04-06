//
//  ComponentSprite.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__SystemDepth__
#define __aunteater__SystemDepth__

#include "aunteater\System.h"
#include "aunteater\Engine.h"

#include "ComponentPosition.h"
#include "ComponentAnimationState.h"
#include "NodeAnimation.h"

#include "aunteater\Node.h"

class SystemDepth : public aunteater::System
{
public:
	SystemDepth(aunteater::Engine & aEngine);
	void addedToEngine(aunteater::Engine &aEngine);
	void update(float time);

public:
	std::list<aunteater::Node> & mNodeList;
};

#endif /* defined(__aunteater__SystemDepth__) */
