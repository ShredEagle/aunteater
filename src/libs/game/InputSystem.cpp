#include "InputSystem.h"


InputSystem::InputSystem(aunteater::Engine & aEngine) :
mNodeList(aEngine.getNodes<NodeControl>())
{
	aEngine.addSystem(this);
}

void InputSystem::addedToEngine(aunteater::Engine &aEngine)
{
}

void InputSystem::update(float time)
{
	Polycode::CoreInput * keyboard = Polycode::CoreServices::getInstance()->getCore()->getInput();
	for (aunteater::Node node : mNodeList)
	{
		if(keyboard->getKeyState(Polycode::KEY_UP))
		{
			((ComponentSpeed&)(node.get(&typeid(ComponentSpeed)))).vY = -BASE_SPEED;
		}
		else if (keyboard->getKeyState(Polycode::KEY_DOWN))
		{
			((ComponentSpeed&)(node.get(&typeid(ComponentSpeed)))).vY = BASE_SPEED;
		}
		else
		{
			((ComponentSpeed&)(node.get(&typeid(ComponentSpeed)))).vY = 0;
		}
		
		if (keyboard->getKeyState(Polycode::KEY_LEFT))
		{
			((ComponentSpeed&)(node.get(&typeid(ComponentSpeed)))).vX = -BASE_SPEED;
		}
		else if (keyboard->getKeyState(Polycode::KEY_RIGHT))
		{
			((ComponentSpeed&)(node.get(&typeid(ComponentSpeed)))).vX = BASE_SPEED;
		}
		else
		{
			((ComponentSpeed&)(node.get(&typeid(ComponentSpeed)))).vX = 0;
		}
	}
}