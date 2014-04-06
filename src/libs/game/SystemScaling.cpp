#include "SystemScaling.h"


SystemScaling::SystemScaling(aunteater::Engine & aEngine) :
mNodeList(aEngine.getNodes<NodeScaling>())
{
	aEngine.addSystem(this);
}

void SystemScaling::addedToEngine(aunteater::Engine &aEngine)
{

}

void SystemScaling::update(float time)
{
	for (aunteater::Node node : mNodeList)
	{
		ComponentPosition pos = (ComponentPosition&)(node.get(&typeid(ComponentPosition)));
		Number newScale = ((BASE_SCALE - MIN_SCALE) / BASE_LINE_DEPTH) * pos.y + MIN_SCALE;
		((ComponentSprite&)(node.get(&typeid(ComponentSprite)))).image->setScale(newScale, newScale);
	}
}
