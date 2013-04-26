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

	// ����һ��CCMenuItemFont    
    CCMenuItemFont *item1 = CCMenuItemFont::create("Play", this, menu_selector(MainMenuLayer::menuCallbackPlay) );  
	item1->setFontSizeObj(100);
    //item1->setFontName("American Typewriter");  
    CCMenuItemFont *item2 = CCMenuItemFont::create("Setting", this, menu_selector(MainMenuLayer::menuCallbackSetting) );  
    item2->setFontSizeObj(100);  
    //item2->setFontName("Marker Felt");  


	//����CCMenu�˵�����������Ϊ�ǲ˵���   
    CCMenu* menu = CCMenu::create( item1, item2, NULL);  
    menu->alignItemsVertically();//�������Ϊ���óɴ�ֱ����   
    //menu->alignItemsHorizontally();//ˮƽ����   
	
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