#include "SystemMove.h"


SystemMove::SystemMove(aunteater::Engine & aEngine) :
mNodeList(aEngine.getNodes<NodeMove>())
{
	aEngine.addSystem(this);
}

void SystemMove::addedToEngine(aunteater::Engine &aEngine)
{
}

void SystemMove::update(float time)
{
	for (aunteater::Node node : mNodeList)
	{
		ComponentSpeed speed = (ComponentSpeed&)(node.get(&typeid(ComponentSpeed)));
		((ComponentPosition&)(node.get(&typeid(ComponentPosition)))).x += speed.vX;
		((ComponentPosition&)(node.get(&typeid(ComponentPosition)))).y += speed.vY;
	}
}