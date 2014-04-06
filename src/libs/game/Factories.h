//
//  Factories.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__Factories__
#define __aunteater__Factories__

#define BASE_PATH "C:/work/aunteater/Resources/"

#include <aunteater/Entity.h>
#include <aunteater/Engine.h>
#include <Polycode.h>

#include <vector>

aunteater::Entity createPlayer(Polycode::Screen *aScreen);
std::vector<aunteater::Entity> createPnj(Polycode::Screen *aScreen);
aunteater::Entity createVideur(Polycode::Screen *aScreen);
std::vector<aunteater::Entity> createBackground(Polycode::Screen *aScreen);
std::vector<aunteater::Entity> createBarriers();
aunteater::Entity createInteractionVideur(aunteater::Engine &aEngine);

#endif /* defined(__aunteater__Factories__) */
