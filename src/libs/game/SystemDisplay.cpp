#include "SystemDisplay.h"


SystemDisplay::SystemDisplay(aunteater::Engine & aEngine):
	mNodeList(aEngine.getNodes<NodeDisplay>())
{
	aEngine.addSystem(this);
}

void SystemDisplay::addedToEngine(aunteater::Engine &aEngine)
{
	
}

void SystemDisplay::update(float time)
{
	for (aunteater::Node node : mNodeList)
	{
		ComponentPosition pos = (ComponentPosition&)(node.get(&typeid(ComponentPosition)));
		((ComponentSprite&)(node.get(&typeid(ComponentSprite)))).image->setPosition(pos.x, pos.y);
	}
}