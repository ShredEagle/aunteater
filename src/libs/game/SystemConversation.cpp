//
//  SystemConversation.cpp
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#include "SystemConversation.h"

#include "ComponentAddressee.h"
#include "ComponentAlignment.h"
#include "ComponentDrugState.h"
#include "ComponentPosition.h"
#include "ComponentSentence.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/algorithm/string.hpp>

using namespace aunteater;

class NodeInitiators
{
public:
    static const ComponentIds gComponentTypes;
};

const ComponentIds NodeInitiators::gComponentTypes = { &typeid(ComponentDrugState),
                                                       &typeid(ComponentAddressee),
                                                       &typeid(ComponentAlignment) };

class NodeTalkers
{
public:
    static const ComponentIds gComponentTypes;
};

const ComponentIds NodeTalkers::gComponentTypes = { &typeid(ComponentSentence),
                                                    &typeid(ComponentPosition) };

SystemConversation::SystemConversation(Engine &aEngine,
                                       const std::string &aInitialDoc,
                                       const std::string &aConversationDoc) :
        mPlayers(aEngine.getNodes<NodeInitiators>()),
        mPNJs (aEngine.getNodes<NodeTalkers>()),
        mEngine(aEngine)
{
    
    mEngine.addSystem(this);
    boost::property_tree::read_json(aInitialDoc, mInitialTree);
    boost::property_tree::read_json(aConversationDoc, mConversationTree);
}

void SystemConversation::addedToEngine(Engine &aEngine)
{
}

std::string SystemConversation::stateKey(aunteater::Node &aInitiatorNode)
{
    auto & drugState = aInitiatorNode.get<ComponentDrugState>();
    auto & alignment = aInitiatorNode.get<ComponentAlignment>();
//        static_cast<ComponentDrugState &>(aInitiatorNode.get(&typeid(ComponentDrugState)));
    return drugState.name + "0_0_" + alignment.sign;
}

void SystemConversation::update(float time)
{
    for (auto & initiator : mPlayers)
    {
        auto & addressee = static_cast<ComponentAddressee &>(initiator.get(&typeid(ComponentAddressee)));
        if (addressee.entityName != "")
        {
            std::string next_sentence_id = mInitialTree.get<std::string>(addressee.entityName + "." + stateKey(initiator));
            std::vector<std::string> strs;
            boost::split(strs, next_sentence_id, boost::is_any_of("_"));
            
            Handle<Entity> nextTalking = mEngine.getEntity(strs.at(0));
            if ((*nextTalking).has(&typeid(ComponentSentence)))
            {
                auto & nextSentence = *nextTalking->get<ComponentSentence>();
                nextSentence.identifier = next_sentence_id;
            }
//            mSentencesTree.get<std::stri
        }
    }
    
    for (auto & talker : mPNJs)
    {
        auto & sentence = talker.get<ComponentSentence>();
        if(sentence.identifier != "")
        {
            //mConversationTree.
        }
    }
}