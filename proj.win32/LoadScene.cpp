#include "jigsaw.h"


LoadScene* LoadScene::createWithScene(LoadSceneType scene)
{
	LoadScene* loadScene = LoadScene::create();
    if(loadScene)
	{  
		//loadScene->autorelease();
        loadScene->initWithScene(scene);
        return loadScene;
    }

    CC_SAFE_DELETE(loadScene);
    return loadScene;
}

LoadScene* LoadScene::initWithScene(LoadSceneType scene)
{
	if (CCScene::init())  
    {
		m_loadScene = scene;
		
		CCLabelTTF* label = CCLabelTTF::create("Loading", "Marker Felt", 64);
		CCSize s = CCDirector::sharedDirector()->getWinSize();
		label->setPosition(ccp(s.width * 0.5, s.height * 0.5));
		addChild(label);

		//this->scheduleUpdate();
    }
	return this;
}

void LoadScene::onEnter()
{
	CCScene::onEnter();
	switch(m_loadScene)
	{
		case LOAD_SCENE_PLAY:
		{
			CCLayer* layer = PlayLayer::create();
			SceneManager::go(layer); 
			break;
		}
		case LOAD_SCENE_MENU:
		{
			CCLayer* layer = MainMenuLayer::create();
			CCScene* newScene = SceneManager::wrap(layer);
			CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(TRANSITION_DURATION, newScene));
			break;
		}
		default:
			break;
	}
}

void LoadScene::update(float t)
{
	this->unscheduleAllSelectors();

	switch(m_loadScene)
	{
		case LOAD_SCENE_PLAY:
		{
			CCLayer* layer = PlayLayer::create();
			SceneManager::go(layer); 
			break;
		}
		case LOAD_SCENE_MENU:
		{
			CCLayer* layer = MainMenuLayer::create();
			CCScene* newScene = SceneManager::wrap(layer);
			CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(TRANSITION_DURATION, newScene));
			break;
		}
		default:
			break;
	}
}