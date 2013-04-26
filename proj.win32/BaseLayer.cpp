#include <iostream>   
#include "BaseLayer.h"

  
bool BaseLayer::init()  
{  
    if (!CCLayerColor::initWithColor(ccc4(255,255,255,0)))
    {  
        return false;  
    }  
    this->setTouchEnabled(true);  
    //ÆôÓÃ´¥Ãş   
      
	CCSprite* bg = CCSprite::create("back960_640_2.png");  
    
	// elastic effect
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    bg->setPosition(ccp(s.width/2, s.height/2));
      
    this->addChild(bg,0);  
      
    return true;  
      
}  
