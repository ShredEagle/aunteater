#include "SystemZReorder.h"


SystemZReorder::SystemZReorder(aunteater::Engine & aEngine) :
mZBoundariesList(aEngine.getNodes<NodeZBoundary>()),
mZOrderedList(aEngine.getNodes<NodeZOrder>())
{
	aEngine.addSystem(this);
}

void SystemZReorder::addedToEngine(aunteater::Engine &aEngine)
{
}

void SystemZReorder::update(float time)
{
	for (aunteater::Node ordered : mZOrderedList)
	{
		ComponentPosition posPlayer = (ComponentPosition&)ordered.get(&typeid(ComponentPosition));
		ComponentZord & zOrderPlayer = (ComponentZord&)ordered.get(&typeid(ComponentZord));

		for (aunteater::Node boundary : mZBoundariesList)
		{
			ComponentZBoundary zBoundary = (ComponentZBoundary&)boundary.get(&typeid(ComponentZBoundary));
			if (zBoundary.yBoundary > posPlayer.y && zOrderPlayer.zOrder < zBoundary.zBoundary)
			{
				zOrderPlayer.zOrder = zBoundary.zBoundary + 1;
			}
			else if (zOrderPlayer.zOrder > zBoundary.zBoundary)
			{
				zOrderPlayer.zOrder = zBoundary.zBoundary - 1;
			}
		}
	}
}