//
//  ComponentSprite.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__SytemDisplay__
#define __aunteater__SytemDisplay__

#include "aunteater\System.h"
#include "aunteater\Engine.h"

#include "ComponentSprite.h"
#include "ComponentPosition.h"
#include "NodeDisplay.h"

#include "aunteater\Node.h"

class SystemDisplay : public aunteater::System
{
public:
	SystemDisplay(aunteater::Engine & aEngine,Polycode::Screen & aScreen);
	void addedToEngine(aunteater::Engine &aEngine);
	void update(float time);

public:
	std::list<aunteater::Node> & mNodeList;
	Polycode::Screen & mScreen;
};

#endif /* defined(__aunteater__SytemDisplay__) */
