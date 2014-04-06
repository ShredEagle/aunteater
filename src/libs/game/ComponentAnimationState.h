//
//  ComponentPosition.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__ComponentAnimationState__
#define __aunteater__ComponentAnimationState__

#include <Polycode.h>

#include <aunteater/Component.h>
#include <memory>
#include <map>

class ComponentAnimationState : public aunteater::Component
{
public:
	ComponentAnimationState() : aunteater::Component(),
		state("idle"),
		animationsMap(std::map<std::string, std::pair<std::string, float>>())
	{}

	void addAnimation(std::string state, std::string frames, float speed, Polycode::ScreenSprite &sprite);

	const std::type_info & getTypeInfo()
	{
		return typeid(*this);
	}
public:
	std::string state;
	//<animation state,<frames,speed>>
	std::map< std::string, std::pair<std::string, float>> animationsMap;

};

#endif /* defined(__aunteater__ComponentAnimationState__) */
