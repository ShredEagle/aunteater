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
#include "Factories.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

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
                                       Polycode::Screen *aScreen,
                                       const std::string &aInitialDoc,
                                       const std::string &aConversationDoc) :
        mPlayers(aEngine.getNodes<NodeInitiators>()),
        mPNJs (aEngine.getNodes<NodeTalkers>()),
        mEngine(aEngine),
        mScreen(aScreen)
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
    
    return drugState.name + "_0_0_" + alignment.sign;
}

void SystemConversation::update(float time)
{
    for (auto & initiator : mPlayers)
    {
        auto & addressee = static_cast<ComponentAddressee &>(initiator.get(&typeid(ComponentAddressee)));
        if (addressee.entityName != "")
        {
            //std::string next_sentence_id = mInitialTree.get<std::string>(addressee.entityName + "." + stateKey(initiator));
			std::string next_sentence_id = "";
			
			BOOST_FOREACH(boost::property_tree::ptree::value_type & value,
				mInitialTree.get_child(addressee.entityName + "." + stateKey(initiator)))
			{
				next_sentence_id = value.second.get<std::string>("");
				if (next_sentence_id != "")
				{
					break;
				}
			}

			std::vector<std::string> strs;
			boost::split(strs, next_sentence_id, boost::is_any_of("_"));
        }
    }
    
    for (auto & talker : mPNJs)
    {
        auto & sentence = talker.get<ComponentSentence>();
        auto & position = talker.get<ComponentPosition>();
        if(sentence.identifier != "")
        {
            TextPairList textPairList;
            
            std::list< std::pair<std::string, std::string> > mParams;
            BOOST_FOREACH(boost::property_tree::ptree::value_type & value,
                          mConversationTree.get_child(sentence.identifier))
            {
                int i = 0;
                std::pair<std::string, std::string> pair;
                BOOST_FOREACH(boost::property_tree::ptree::value_type & subvalue,
                              value.second)
                {
                    if(i)
                    {
                        pair.first = subvalue.second.get<std::string>("");
                    }
                    else
                    {
                        pair.second = subvalue.second.get<std::string>("");
                    }
                    ++i;
                }
                
                textPairList.push_back(pair);
            }
            
            mEngine.addEntity(createTextBox(mScreen, textPairList, position.x, position.y));
        }
    }
}