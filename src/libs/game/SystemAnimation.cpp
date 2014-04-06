#include "SystemAnimation.h"

SystemAnimation::SystemAnimation(aunteater::Engine & aEngine):
mNodeList(aEngine.getNodes<NodeAnimation>())
{
	aEngine.addSystem(this);
}

void SystemAnimation::addedToEngine(aunteater::Engine &aEngine)
{}

void SystemAnimation::update(float time)
{
	for (aunteater::Node node : mNodeList) {

		ComponentAnimationState animState = (ComponentAnimationState&)(node.get(&typeid(ComponentAnimationState)));
		ComponentSprite sprite = (ComponentSprite&)(node.get(&typeid(ComponentSprite)));

		if (sprite.image->getCurrentAnimation() == NULL || sprite.image->getCurrentAnimation()->name != animState.state)
			sprite.image->playAnimation(animState.state, 0, false);
		
	}
}