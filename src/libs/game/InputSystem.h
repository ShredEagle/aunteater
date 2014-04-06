//
//  ComponentSprite.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__InputSystem__
#define __aunteater__InputSystem__

#include "NodeControl.h"

#include "ComponentSpeed.h"

#include <Polycode.h>

#include <aunteater/System.h>
#include <aunteater/Node.h>
#include <aunteater/Engine.h>

#include <list>

#define BASE_SPEED 1.0

class InputSystem : public aunteater::System
{
public:
	InputSystem(aunteater::Engine &aEngine);
	void addedToEngine(aunteater::Engine &aEngine);
	void update(float time);

public:
	std::list<aunteater::Node> & mNodeList;
};

#endif /* defined(__aunteater__InputSystem__) */
