#include "MainMenu.h"


MainMenuScene::MainMenuScene(void)
{
}


MainMenuScene::~MainMenuScene(void)
{
}

bool MainMenuScene::init()
{
	if (!CCScene::init())  
    {  
        return false;  
    }

	MainMenuLayer* layer = (MainMenuLayer*)MainMenuLayer::create();
	addChild(layer);
	return true;
}

	
bool MainMenuLayer::init()
{
	if (!BaseLayer::init())  
    {  
        return false;  
    }

	// 创建一个CCMenuItemFont    
    CCMenuItemFont *item1 = CCMenuItemFont::create("Play", this, menu_selector(MainMenuLayer::menuCallbackPlay) );  
	item1->setFontSizeObj(100);
    //item1->setFontName("American Typewriter");  
    CCMenuItemFont *item2 = CCMenuItemFont::create("Setting", this, menu_selector(MainMenuLayer::menuCallbackSetting) );  
    item2->setFontSizeObj(100);  
    //item2->setFontName("Marker Felt");  


	//创建CCMenu菜单，其他可认为是菜单项   
    CCMenu* menu = CCMenu::create( item1, item2, NULL);  
    menu->alignItemsVertically();//可以理解为设置成垂直排列   
    //menu->alignItemsHorizontally();//水平排列   
	
	// elastic effect
    CCSize s = CCDirector::sharedDirector()->getWinSize();

	addChild(menu);
    menu->setPosition(ccp(s.width/2, s.height/2));  

	
	/*CCParticleSystemQuad *system = CCParticleSystemQuad::create("mergeEffect.plist");
	system->setPosition(100,100);
	system->setTextureWithRect(CCTextureCache::sharedTextureCache()->addImage("stars.png"), CCRectMake(0,0,32,32));
	addChild(system, 10);
	CCParticleFire* fire = CCParticleFire::create();
	fire->setPosition(s.width/2, 800);
	addChild(fire);*/


	return true;

}

MainMenuLayer::~MainMenuLayer()
{
}

void MainMenuLayer::menuCallbackPlay(CCObject* sender) 
{
	SceneManager::goPlay();
}

void MainMenuLayer::menuCallbackSetting(CCObject* sender) 
{
	//SceneManager::goMenu();
}