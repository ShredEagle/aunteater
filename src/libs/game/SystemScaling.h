//
//  ComponentSprite.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__SystemScaling__
#define __aunteater__SystemScaling__

#include <aunteater/System.h>
#include <aunteater/Engine.h>
#include <aunteater/Node.h>

#include "ComponentSprite.h"
#include "ComponentPosition.h"
#include "ComponentScale.h"
#include "NodeScaling.h"

#define BASE_LINE_DEPTH 384.0
#define BASE_SCALE 0.45
#define MIN_SCALE 0.35


class SystemScaling : public aunteater::System
{
public:
	SystemScaling(aunteater::Engine & aEngine);
	void addedToEngine(aunteater::Engine &aEngine);
	void update(float time);

public:
	std::list<aunteater::Node> & mNodeList;
};

#endif /* defined(__aunteater__SystemScaling__) */
