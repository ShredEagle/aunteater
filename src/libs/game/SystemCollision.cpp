#include "SystemCollision.h"


SystemCollision::SystemCollision(aunteater::Engine & aEngine) :
mBarrierList(aEngine.getNodes<NodeBarrier>()),
mPlayerList(aEngine.getNodes<NodePlayerCollision>())
{
	aEngine.addSystem(this);
}

void SystemCollision::addedToEngine(aunteater::Engine &aEngine)
{

}

void SystemCollision::update(float time)
{
	for (aunteater::Node barrier : mBarrierList)
	{
		ComponentBarrier posBarrier = (ComponentBarrier&)barrier.get(&typeid(ComponentBarrier));

		Polycode::Vector2 line = Polycode::Vector2(posBarrier.x2 - posBarrier.x1, posBarrier.y2 - posBarrier.y1);
		Number length = line.length();
		line.Normalize();
		Polycode::Vector2 origin = Polycode::Vector2(posBarrier.x1, posBarrier.y1);
		Polycode::Vector2 end = Polycode::Vector2(posBarrier.x2, posBarrier.y2);

		for (aunteater::Node player : mPlayerList)
		{
			ComponentPosition& posPlayer = (ComponentPosition&)player.get(&typeid(ComponentPosition));
			Polycode::Vector2 player = Polycode::Vector2(posPlayer.x-40, posPlayer.y+37);
			
			Polycode::Vector2 normal = (origin - player) - line*line.dot(origin - player);

			if (normal.length() < 20 && (origin.distance(player) < length && end.distance(player) < length))
			{
				normal.Normalize();
				posPlayer.x -= normal.x * 5;
				posPlayer.y -= normal.y * 5;
			}
			
		}
	}
}