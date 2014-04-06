//
//  ComponentTextList.h
//  aunteater
//
//  Created by Adrien on 06/04/14.
//
//

#ifndef aunteater_ComponentTextList_h
#define aunteater_ComponentTextList_h

#include <Polycode.h>
#include <aunteater/Component.h>

#include <string>
#include <list>

typedef std::list< std::pair<std::string, std::string> > TextPairList;

class ComponentTextList : public aunteater::Component
{
public:
    const std::type_info & getTypeInfo()
	{
		return typeid(*this);
	}
    
    ComponentTextList(Polycode::Screen *aScreen, TextPairList aTpl) :
        list(aTpl)
    {
        rectangle = new Polycode::ScreenShape(Polycode::ScreenShape::SHAPE_RECT, 100, 20*aTpl.size());
        rectangle->setPositionMode(Polycode::ScreenEntity::POSITION_TOPLEFT);
        
        Polycode::CoreServices::getInstance()->getFontManager()->registerFont("Script", "/Library/Fonts/Tahoma.ttf");
 
        int i = 0;
        for( const TextPairList::value_type & pair : aTpl)
        {
            Polycode::ScreenLabel * label = new Polycode::ScreenLabel(pair.first, 18);
            label->setPositionMode(Polycode::ScreenEntity::POSITION_TOPLEFT);
            label->setPosition(0, i*20);
            label->setColor(Polycode::Color(200, 0, 0, 255));
            rectangle->addChild(label);
            ++i;
        }
        
        aScreen->addChild(rectangle);
    }
    
     TextPairList list;
     Polycode::ScreenShape *rectangle;
     std::list<Polycode::ScreenLabel *> labels;
     Polycode::Scene * scene;
     
    
};


#endif
