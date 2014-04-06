//
//  SystemConversation.cpp
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#include "SystemConversation.h"

#include "ComponentAddressee.h"
#include "ComponentDrugState.h"
#include "ComponentPosition.h"
#include "ComponentSentence.h"

using namespace aunteater;

class NodeInitiators
{
public:
    static const ComponentIds gComponentTypes;
};

const ComponentIds NodeInitiators::gComponentTypes = { &typeid(ComponentDrugState),
                                                       &typeid(ComponentAddressee) };

class NodeTalkers
{
public:
    static const ComponentIds gComponentTypes;
};

const ComponentIds NodeTalkers::gComponentTypes = { &typeid(ComponentSentence),
                                                    &typeid(ComponentPosition) };

void SystemConversation::addToEngine(Engine &aEngine)
{
    mPlayers = aEngine.getNodes<NodeInitiators>();
    mPNJs = aEngine.getNodes<NodeTalkers>();
}