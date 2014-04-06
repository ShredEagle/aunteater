#include "SystemInteraction.h"


SystemInteraction::SystemInteraction(aunteater::Engine & aEngine) :
mActorList(aEngine.getNodes<NodeActor>()),
mInteractionList(aEngine.getNodes<NodeInteraction>())
{
	aEngine.addSystem(this);
}

void SystemInteraction::addedToEngine(aunteater::Engine &aEngine)
{
}

void SystemInteraction::update(float time)
{
	for (aunteater::Node node : mActorList)
	{
		ComponentPosition posPlayer = (ComponentPosition&)node.get(&typeid(ComponentPosition));
		Polycode::CoreInput * keyboard = Polycode::CoreServices::getInstance()->getCore()->getInput();

		if (keyboard->getKeyState(Polycode::KEY_SPACE))
		{
			for (aunteater::Node interaction : mInteractionList)
			{
				ComponentInteraction & intComp = (ComponentInteraction&)interaction.get(&typeid(ComponentInteraction));
				int maxX = MAX(intComp.x1, intComp.x2);
				int maxY = MAX(intComp.y1, intComp.y2);
				int minX = MIN(intComp.x1, intComp.x2);
				int minY = MIN(intComp.y1, intComp.y2);

				if (posPlayer.x < maxX && posPlayer.x > minX && posPlayer.y < maxY && posPlayer.y > minY && intComp.active)
				{
					intComp.active = false;
					intComp.mHandler->handleInteraction(intComp);
				}
			}
		}
	}
}