#include "SystemMoveAnimation.h"

SystemMoveAnimation::SystemMoveAnimation(aunteater::Engine & aEngine) :
mNodeList(aEngine.getNodes<NodeMoveAnimation>())
{
	aEngine.addSystem(this);
}

void SystemMoveAnimation::addedToEngine(aunteater::Engine &aEngine)
{}

void SystemMoveAnimation::update(float time)
{
	for (aunteater::Node node : mNodeList) {

		ComponentAnimationState & animState = (ComponentAnimationState&)(node.get(&typeid(ComponentAnimationState)));
		ComponentSpeed & speed = (ComponentSpeed&)(node.get(&typeid(ComponentSpeed)));

		if (speed.vX > 0)
		{
			animState.state = "right";
			return;
		}

		if (speed.vY > 0)
		{
			animState.state = "up";
			return;
		}

		if (speed.vX < 0)
		{
			animState.state = "left";
			return;
		}

		if (speed.vY < 0)
		{
			animState.state = "down";
			return;
		}

		
		if (animState.state == "right")
		{
			animState.state = "idle_r";
			return;
		}

		animState.state = "idle";

	}
}