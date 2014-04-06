//
//  Factories.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__Factories__
#define __aunteater__Factories__

#define BASE_PATH "/Users/adn/projects/Perso/aunteater/Resources/"

//for TextPairList
#include "ComponentTextList.h"

#include <aunteater/Entity.h>
#include <Polycode.h>

#include <vector>

aunteater::Entity createPlayer(Polycode::Screen *aScreen);
aunteater::Entity createTextBox(Polycode::Screen *aScreen, TextPairList aTpl, float x, float y);

std::vector<aunteater::Entity> createPng(Polycode::Screen *aScreen);
std::vector<aunteater::Entity> createBackground(Polycode::Screen *aScreen);
std::vector<aunteater::Entity> createBarriers();

#endif /* defined(__aunteater__Factories__) */
