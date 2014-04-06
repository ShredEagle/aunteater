//
//  ComponentSprite.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__SytemMove__
#define __aunteater__SytemMove__

#include "aunteater\System.h"
#include "aunteater\Engine.h"

#include "ComponentSpeed.h"
#include "ComponentPosition.h"
#include "NodeMove.h"

#include "aunteater\Node.h"

class SystemMove : public aunteater::System
{
public:
	SystemMove(aunteater::Engine & aEngine);
	void addedToEngine(aunteater::Engine &aEngine);
	void update(float time);

public:
	std::list<aunteater::Node> & mNodeList;
};

#endif /* defined(__aunteater__SytemDisplay__) */
