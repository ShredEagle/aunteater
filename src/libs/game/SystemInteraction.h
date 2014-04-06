//
//  SystemInteraction.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__SystemInteraction__
#define __aunteater__SystemInteraction__

#include <aunteater/System.h>
#include <aunteater/Engine.h>
#include <aunteater/Node.h>
#include "ComponentInteraction.h"
#include "ComponentKeyboard.h"
#include "ComponentPlayer.h"
#include "ComponentPosition.h"
#include "NodeInteraction.h"
#include "NodeActor.h"


class SystemInteraction : public aunteater::System
{
public:
	SystemInteraction(aunteater::Engine & aEngine);
	void addedToEngine(aunteater::Engine &aEngine);
	void update(float time);

public:
	std::list<aunteater::Node> & mActorList;
	std::list<aunteater::Node> & mInteractionList;
};

#endif /* defined(__aunteater__SystemInteraction__) */
