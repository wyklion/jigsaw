#include "jigsaw.h"

bool StopLayer::init()
{
	if (!CCLayerColor::init())
	{  
		return false;  
	}  
	
    this->setTouchEnabled(true);  
    //启用触摸   

	// elastic effect
    CCSize s = CCDirector::sharedDirector()->getWinSize();
	
	//CCSprite* bg = CCSprite::create("stopBackground.png");  
    //bg->setPosition(ccp(s.width/2, s.height/2));
    //this->addChild(bg,0);
	
	CCMenuItemFont* resume = CCMenuItemFont::create("Resume",this, menu_selector(StopLayer::resume));
	resume->setFontSize(100);
	CCMenuItemFont* retry = CCMenuItemFont::create("Retry",this, menu_selector(StopLayer::retry));
	retry->setFontSize(100);
	CCMenuItemFont* quit = CCMenuItemFont::create("Quit",this, menu_selector(StopLayer::quit));
	quit->setFontSize(100);
	//老问题 别忘记类名 还有这个只需要函数名就够了  
	m_menu = CCMenu::create(resume, retry, quit, NULL);   
	//Items！ 单复数 要注意   
	m_menu->setPosition(ccp(s.width*0.5, s.height*0.5));
	m_menu->alignItemsVertically();
	this->addChild(m_menu);  
	
	CCParticleSystemQuad *system = CCParticleSystemQuad::create("mergeEffect.plist");
	system->setPosition(100,100);
	system->setTextureWithRect(CCTextureCache::sharedTextureCache()->addImage("particale.png"), CCRectMake(0,0,32,32));
	addChild(system, 10);

	return true;
}

void StopLayer::onEnter()
{
    CCLayerColor::onEnter();
	((PlayLayer*)this->getParent())->setStopVisible(false);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void StopLayer::onExit()
{
    CCLayerColor::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool StopLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_touchedMenu = m_menu->ccTouchBegan(pTouch, pEvent);
    return true;
}

void StopLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_touchedMenu) 
	{
        m_menu->ccTouchMoved(pTouch, pEvent);
    }
}

void StopLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_touchedMenu)
	{
        m_menu->ccTouchEnded(pTouch, pEvent);
        m_touchedMenu = false;
    }
}

void StopLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_touchedMenu) 
	{
        m_menu->ccTouchEnded(pTouch, pEvent);
        m_touchedMenu = false;
    }
}

void StopLayer::resume(cocos2d::CCObject *pSender)  
{  
	((PlayLayer*)this->getParent())->setStopVisible(true);
	this->removeFromParentAndCleanup(false);
	JigsawSound::resumeMusic();
	//SceneManager::pop();
}

void StopLayer::retry(cocos2d::CCObject *pSender)  
{  
	((PlayLayer*)this->getParent())->retry();
	JigsawSound::resumeMusic();
	//SceneManager::pop();
}

void StopLayer::quit(cocos2d::CCObject *pSender)  
{  
	//SceneManager::pop();
	this->removeFromParentAndCleanup(false);
	SceneManager::goMenu();  
	//back就是回主菜单，这里调用了人见人爱 花见花开的静态函数 goMenu  
}
