#include "ComponentAnimationState.h"

void ComponentAnimationState::addAnimation(std::string state, std::string frames, float speed, Polycode::ScreenSprite &sprite) {
	animationsMap.insert(std::pair < std::string, std::pair<std::string, float>>(state, std::pair<std::string, float>(frames, speed)));

	sprite.addAnimation(state, frames, speed);
}