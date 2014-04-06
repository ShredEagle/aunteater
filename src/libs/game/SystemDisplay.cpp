#include "SystemDisplay.h"

#include "ComponentZord.h"

#include <algorithm>
#include <list>


SystemDisplay::SystemDisplay(aunteater::Engine & aEngine,Polycode::Screen &aScreen):
	mNodeList(aEngine.getNodes<NodeDisplay>()),
	mScreen(aScreen)
{
	aEngine.addSystem(this);
}

void SystemDisplay::addedToEngine(aunteater::Engine &aEngine)
{
	
}

bool sortZorder(aunteater::Node nodeA, aunteater::Node nodeB)
{
	int zOrderA = ((ComponentZord&)nodeA.get(&typeid(ComponentZord))).zOrder;
	int zOrderB = ((ComponentZord&)nodeB.get(&typeid(ComponentZord))).zOrder;
	return zOrderA > zOrderB;
}

void SystemDisplay::update(float time)
{
	mNodeList.sort(sortZorder);
	for (aunteater::Node node : mNodeList)
	{
		ComponentPosition pos = (ComponentPosition&)(node.get(&typeid(ComponentPosition)));
		((ComponentSprite&)(node.get(&typeid(ComponentSprite)))).image->setPosition(pos.x, pos.y);
		mScreen.rootEntity.moveChildTop(((ComponentSprite&)(node.get(&typeid(ComponentSprite)))).image.get());
	}


}