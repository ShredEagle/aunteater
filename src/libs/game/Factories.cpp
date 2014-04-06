//
//  Factories.cpp
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#include "Factories.h"

#include "ComponentSprite.h"

#include <string>
#include <Polycode.h>

using namespace aunteater;

Entity createPlayer(Polycode::Screen *aScreen)
{
    Entity player;
    player.addComponent(std::make_shared<ComponentSprite>
                            (std::string(BASE_PATH) + "sprites/imgres.png", aScreen));
    return player;
}