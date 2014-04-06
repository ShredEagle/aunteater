//
//  Factories.cpp
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#include "Factories.h"

#include "ComponentSprite.h"
#include "ComponentPosition.h"
#include "ComponentKeyboard.h"
#include "ComponentSpeed.h"
#include "ComponentAnimationState.h"
#include "ComponentScale.h"
#include "ComponentBarrier.h"
#include "ComponentPlayer.h"
#include "ComponentZord.h"
#include "ComponentZBoundary.h"
#include "ComponentZReorderable.h"
#include "ComponentInteraction.h"

#include <string>
using namespace aunteater;

Entity createPlayer(Polycode::Screen * aScreen)
{
    Entity player;
	std::shared_ptr<ComponentSprite> sprite = std::make_shared<ComponentSprite>(std::string(BASE_PATH) + "sprites/spritesheet_hero.png",126,180,0.6,0.6);

	std::shared_ptr<ComponentAnimationState> animationComp = std::make_shared<ComponentAnimationState>();
	animationComp->addAnimation("idle", "18,19,20,21,22,23,24,25,26", 0.3,*sprite->image.get());
	animationComp->addAnimation("idle_r", "27,28,29,30,31,32,33,34,35", 0.3, *sprite->image.get());
	animationComp->addAnimation("left", "6,5,4,3,2,1", 0.2, *sprite->image.get());
	animationComp->addAnimation("right", "15,14,13,12,11,10", 0.2, *sprite->image.get());
	animationComp->addAnimation("up", "36,37,38,39,40,41,42,43,44", 0.16, *sprite->image.get());
	animationComp->addAnimation("down", "45,46,47,48,49,50,51,52,53", 0.16, *sprite->image.get());
	animationComp->state = "idle";
	
	aScreen->addChild(sprite->image.get());
	player.addComponent(std::make_shared<ComponentPosition>(100, 100));
	player.addComponent(std::make_shared<ComponentZord>(0));
	player.addComponent(sprite);
	player.addComponent(std::make_shared<ComponentKeyboard>());
	player.addComponent(std::make_shared<ComponentSpeed>());
	player.addComponent(std::make_shared<ComponentZReorderable>());
	player.addComponent(animationComp);
	player.addComponent(std::make_shared<ComponentScale>());
	player.addComponent(std::make_shared<ComponentPlayer>());
	
    return player;
}

std::vector<Entity> createPnj(Polycode::Screen *aScreen)
{
	Entity femme1;
	std::shared_ptr<ComponentSprite> sprite = std::make_shared<ComponentSprite>(std::string(BASE_PATH) + "sprites/femme_01.png", 126, 180, 0.6, 0.6);

	sprite->image->depthTest = true;
	sprite->image->depthWrite = true;
	sprite->image->setPositionZ(1);

	std::shared_ptr<ComponentAnimationState> animationComp = std::make_shared<ComponentAnimationState>();
	animationComp->addAnimation("idle", "0,1,2", 0.3, *sprite->image.get());
	animationComp->state = "idle";

	aScreen->addChild(sprite->image.get());
	femme1.addComponent(std::make_shared<ComponentPosition>(404, 612));
	femme1.addComponent(std::make_shared<ComponentZord>(0));
	femme1.addComponent(std::make_shared<ComponentZReorderable>());
	femme1.addComponent(sprite);
	femme1.addComponent(animationComp);
	femme1.addComponent(std::make_shared<ComponentScale>());

	Entity femme2;
	std::shared_ptr<ComponentSprite> sprite2 = std::make_shared<ComponentSprite>(std::string(BASE_PATH) + "sprites/femme_01_b.png", 126, 180, 0.6, 0.6);

	sprite2->image->depthTest = true;
	sprite2->image->depthWrite = true;
	sprite2->image->setPositionZ(1);

	std::shared_ptr<ComponentAnimationState> animationComp2 = std::make_shared<ComponentAnimationState>();
	animationComp2->addAnimation("idle", "0,1,2", 0.3, *sprite2->image.get());
	animationComp2->state = "idle";

	aScreen->addChild(sprite2->image.get());
	femme2.addComponent(std::make_shared<ComponentPosition>(748, 318));
	femme2.addComponent(std::make_shared<ComponentZord>(0));
	femme2.addComponent(std::make_shared<ComponentZReorderable>());
	femme2.addComponent(sprite2);
	femme2.addComponent(animationComp2);
	femme2.addComponent(std::make_shared<ComponentScale>());

	Entity femme3;
	std::shared_ptr<ComponentSprite> sprite3 = std::make_shared<ComponentSprite>(std::string(BASE_PATH) + "sprites/femme_01_c.png", 126, 180, 0.6, 0.6);

	sprite3->image->depthTest = true;
	sprite3->image->depthWrite = true;
	sprite3->image->setPositionZ(1);

	std::shared_ptr<ComponentAnimationState> animationComp3 = std::make_shared<ComponentAnimationState>();
	animationComp3->addAnimation("idle", "0,1,2", 0.3, *sprite3->image.get());
	animationComp3->state = "idle";

	aScreen->addChild(sprite3->image.get());
	femme3.addComponent(std::make_shared<ComponentPosition>(504, 264));
	femme3.addComponent(std::make_shared<ComponentZord>(0));
	femme3.addComponent(std::make_shared<ComponentZReorderable>());
	femme3.addComponent(sprite3);
	femme3.addComponent(animationComp3);
	femme3.addComponent(std::make_shared<ComponentScale>());

	Entity drummer;
	std::shared_ptr<ComponentSprite> sprite4 = std::make_shared<ComponentSprite>(std::string(BASE_PATH) + "sprites/drummer.png", 180, 180, 0.6, 0.6);

	std::shared_ptr<ComponentAnimationState> animationComp4 = std::make_shared<ComponentAnimationState>();
	animationComp4->addAnimation("idle", "0,1,2", 0.02, *sprite4->image.get());
	animationComp4->state = "idle";

	aScreen->addChild(sprite4->image.get());
	drummer.addComponent(std::make_shared<ComponentPosition>(686, 151));
	drummer.addComponent(std::make_shared<ComponentZord>(0));
	drummer.addComponent(std::make_shared<ComponentZReorderable>());
	drummer.addComponent(sprite4);
	drummer.addComponent(animationComp3);
	drummer.addComponent(std::make_shared<ComponentScale>());

	return{ femme1, femme2, femme3 ,drummer};
}

aunteater::Entity createVideur(Polycode::Screen *aScreen)
{
	Entity videur;
	std::shared_ptr<ComponentSprite> sprite4 = std::make_shared<ComponentSprite>(std::string(BASE_PATH) + "sprites/videur_01.png", 126, 180, 0.6, 0.6);

	sprite4->image->depthTest = true;
	sprite4->image->depthWrite = true;
	sprite4->image->setPositionZ(1);

	std::shared_ptr<ComponentAnimationState> animationComp4 = std::make_shared<ComponentAnimationState>();
	animationComp4->addAnimation("idle", "0,1,2,3", 0.3, *sprite4->image.get());
	animationComp4->addAnimation("red", "4,5", 0.3, *sprite4->image.get());
	animationComp4->addAnimation("green", "8,9", 0.3, *sprite4->image.get());
	animationComp4->state = "idle";

	aScreen->addChild(sprite4->image.get());
	videur.addComponent(std::make_shared<ComponentPosition>(290, 298));
	videur.addComponent(std::make_shared<ComponentZord>(0));
	videur.addComponent(std::make_shared<ComponentZReorderable>());
	videur.addComponent(sprite4);
	videur.addComponent(animationComp4);
	videur.addComponent(std::make_shared<ComponentScale>());

	return videur;
}

std::vector<Entity> createBackground(Polycode::Screen *aScreen)
{
	Entity bg;
	std::shared_ptr<ComponentSprite> sprite = std::make_shared<ComponentSprite>(std::string(BASE_PATH) + "sprites/bg.png", 1280, 768,1,1);
	sprite->image->setPositionMode(Polycode::ScreenEntity::POSITION_TOPLEFT);
	aScreen->addChild(sprite->image.get());
	bg.addComponent(std::make_shared<ComponentPosition>(0, 0));
	bg.addComponent(std::make_shared<ComponentZBoundary>(0, 20));
	bg.addComponent(std::make_shared<ComponentZord>(20));
	bg.addComponent(sprite);

	Entity bg1;
	std::shared_ptr<ComponentSprite> sprite1 = std::make_shared<ComponentSprite>(std::string(BASE_PATH) + "sprites/bg1.png", 1280, 768, 1, 1);
	sprite1->image->setPositionMode(Polycode::ScreenEntity::POSITION_TOPLEFT);
	aScreen->addChild(sprite1->image.get());
	bg1.addComponent(std::make_shared<ComponentPosition>(0, 0));
	bg1.addComponent(std::make_shared<ComponentZBoundary>(700, 0));
	bg1.addComponent(std::make_shared<ComponentZord>(0));
	bg1.addComponent(sprite1);

	Entity bg2;
	std::shared_ptr<ComponentSprite> sprite2 = std::make_shared<ComponentSprite>(std::string(BASE_PATH) + "sprites/bg2.png", 1280, 768, 1, 1);
	sprite2->image->setPositionMode(Polycode::ScreenEntity::POSITION_TOPLEFT);
	aScreen->addChild(sprite2->image.get());
	bg2.addComponent(std::make_shared<ComponentPosition>(0, 0));
	bg2.addComponent(std::make_shared<ComponentZBoundary>(571, 2));
	bg2.addComponent(std::make_shared<ComponentZord>(2));
	bg2.addComponent(sprite2);

	Entity bg3;
	std::shared_ptr<ComponentSprite> sprite3 = std::make_shared<ComponentSprite>(std::string(BASE_PATH) + "sprites/bg3.png", 1280, 768, 1, 1);
	sprite3->image->setPositionMode(Polycode::ScreenEntity::POSITION_TOPLEFT);
	aScreen->addChild(sprite3->image.get());
	bg3.addComponent(std::make_shared<ComponentPosition>(0, 0));
	bg3.addComponent(std::make_shared<ComponentZBoundary>(549, 4));
	bg3.addComponent(std::make_shared<ComponentZord>(4));
	bg3.addComponent(sprite3);

	Entity bg4;
	std::shared_ptr<ComponentSprite> sprite4 = std::make_shared<ComponentSprite>(std::string(BASE_PATH) + "sprites/bg4.png", 1280, 768, 1, 1);
	sprite4->image->setPositionMode(Polycode::ScreenEntity::POSITION_TOPLEFT);
	aScreen->addChild(sprite4->image.get());
	bg4.addComponent(std::make_shared<ComponentPosition>(0, 0));
	bg4.addComponent(std::make_shared<ComponentZBoundary>(433, 6));
	bg4.addComponent(std::make_shared<ComponentZord>(6));
	bg4.addComponent(sprite4);

	Entity bg5;
	std::shared_ptr<ComponentSprite> sprite5 = std::make_shared<ComponentSprite>(std::string(BASE_PATH) + "sprites/bg5.png", 1280, 768, 1, 1);
	sprite5->image->depthTest = true;
	sprite5->image->depthWrite = true;
	sprite5->image->setPositionZ(0.2f);
	sprite5->image->setPositionMode(Polycode::ScreenEntity::POSITION_TOPLEFT);
	aScreen->addChild(sprite5->image.get());
	bg5.addComponent(std::make_shared<ComponentPosition>(0, 0));
	bg5.addComponent(std::make_shared<ComponentZBoundary>(334, 8));
	bg5.addComponent(std::make_shared<ComponentZord>(8));
	bg5.addComponent(sprite5);

	Entity bg6;
	std::shared_ptr<ComponentSprite> sprite6 = std::make_shared<ComponentSprite>(std::string(BASE_PATH) + "sprites/bg6.png", 1280, 768, 1, 1);
	sprite6->image->setPositionMode(Polycode::ScreenEntity::POSITION_TOPLEFT);
	aScreen->addChild(sprite6->image.get());
	bg6.addComponent(std::make_shared<ComponentPosition>(0, 0));
	bg6.addComponent(std::make_shared<ComponentZBoundary>(198, 10));
	bg6.addComponent(std::make_shared<ComponentZord>(10));
	bg6.addComponent(sprite6);

	return {bg,bg1,bg2,bg3,bg4,bg5,bg6};
}


std::vector<Entity> createBarriers()
{
	std::vector<Entity> vec = std::vector<Entity>();

	Entity barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(249.0, 114.0, 181.0, 335.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(170.0, 392.0, 75.0, 676.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(133.0, 487.0, 341.0, 487.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(369.0, 388.0, 307.0, 768.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(376.0, 336.0, 395.0, 214.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(337.0, 573.0, 526.0, 573.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(574.0, 573.0, 667.0, 573.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(713.0, 573.0, 806.0, 573.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(844.0, 767.0, 806.0, 573.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(970.0, 767.0, 312.0, 767.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(617.0, 573.0, 617.0, 767.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(769.0, 379.0, 792.0, 575.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(769.0, 379.0, 818.0, 379.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(818.0, 379.0, 841.0, 575.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(914.0, 575.0, 841.0, 575.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(868.0, 367.0, 897.0, 511.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(904.0, 569.0, 911.0, 575.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(868.0, 367.0, 1072.0, 367.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(990.0, 115.0, 1072.0, 367.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(990.0, 115.0, 409.0, 117.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(404.0, 174.0, 409.0, 117.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(332.0, 115.0, 409.0, 117.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(332.0, 115.0, 329.0, 133.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(282.0, 136.0, 329.0, 133.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(282.0, 136.0, 271.0, 179.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(226.0, 179.0, 271.0, 179.0));
	vec.push_back(barrier);
	barrier = Entity();
	barrier.addComponent(std::make_shared<ComponentBarrier>(193.0, 277.0, 381.0, 277.0));
	vec.push_back(barrier);
	return vec;
}

aunteater::Entity createInteractionVideur(Engine &aEngine)
{
	Entity pillInteraction = Entity();

	class PillInteractionHandler : public InteractionHandler
	{
	public:
		PillInteractionHandler(Engine &aEngine) : InteractionHandler(),
			mEngine(aEngine)
		{}

		void handleInteraction(ComponentInteraction & interaction)
		{
			Handle<Entity> videur = mEngine.getEntity("videur");
			std::shared_ptr<ComponentAnimationState> animComp = std::dynamic_pointer_cast<ComponentAnimationState, aunteater::Component>(videur->get(&typeid(ComponentAnimationState)));
			animComp->state = "red";
		}

		Engine & mEngine;
	};

	pillInteraction.addComponent(std::make_shared<ComponentInteraction>(new PillInteractionHandler(aEngine), 245, 297, 306, 381));

	return pillInteraction;
}