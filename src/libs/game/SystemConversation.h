//
//  SystemConversation.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__SystemConversation__
#define __aunteater__SystemConversation__

#include <aunteater/System.h>
#include <aunteater/Engine.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

class SystemConversation : public aunteater::System
{
public:
    void addToEngine(aunteater::Engine &aEngine);
    
    void update();
    
private:
    aunteater::Nodes mPlayers;
    aunteater::Nodes mPNJs;
};

#endif /* defined(__aunteater__SystemConversation__) */
