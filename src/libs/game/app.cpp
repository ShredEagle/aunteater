#include "app.h"

#include "SystemZReorder.h"

using namespace aunteater;

void HardCore::init()
{
	Polycode::CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Polycode::Renderer::TEX_FILTERING_NEAREST);

	Entity player = createPlayer(mScreen);
	mEngine.addEntity("player", player);

	std::vector<Entity> bgs = createBackground(mScreen);
	for (Entity bg : bgs)
	{
		mEngine.addEntity(bg);
	}

	/*std::vector<Entity> pngs = createPng(mScreen);
	for (Entity png : pngs)
	{
		mEngine.addEntity(png);
	}*/


	std::vector<Entity> barriers = createBarriers();
	for (Entity barrier : barriers)
	{
		mEngine.addEntity(barrier);
	}
	
	new SystemDisplay(mEngine,*mScreen);
	new SystemMove(mEngine);
	new InputSystem(mEngine);
	new SystemAnimation(mEngine);
	new SystemMoveAnimation(mEngine);
	new SystemScaling(mEngine);
	new SystemCollision(mEngine);
	new SystemZReorder(mEngine);
}