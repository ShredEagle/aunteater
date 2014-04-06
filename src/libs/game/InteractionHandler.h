//
//  InteractionHandler.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef aunteater_InteractionHandler_h
#define aunteater_InteractionHandler_h

class ComponentInteraction;

class InteractionHandler
{
public:
	virtual void handleInteraction(ComponentInteraction & interaction) = 0;
};

#endif