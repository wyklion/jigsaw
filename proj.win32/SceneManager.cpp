#include "SceneManager.h"

//--------------Translation��Ķ���----------------------   
//���涨�������ֲ�ͬ��ת����   
class FadeWhiteTransition :public CCTransitionFade  
{  
public:  
	static CCTransitionFade* transitionWithDuration (float t ,CCScene* s)  
	{  
		return CCTransitionFade::create(t, s,ccBLACK);  
	}  
};  

class ZoomFlipXLeftOver : public CCTransitionZoomFlipX  
{  
public:  
	static CCTransitionZoomFlipX* transitionWithDuration(float t, CCScene* s)  
	{  
		return CCTransitionZoomFlipX::create(t, s, kCCTransitionOrientationLeftOver);  
	}  

};  

class FlipYDownOver :public CCTransitionZoomFlipY  
{  
public:  
	static CCTransitionZoomFlipY* transitionWithDuration(float t, CCScene* s)  
	{  
		return CCTransitionZoomFlipY::create(t, s, kCCTransitionOrientationDownOver);  
	}  
};  
//-----------------end--------------------------------------------   

#define MAX_TRANS_SCENE 3 //��������ת��������   

int SceneManager::nIdx= -1; //��ʼ����̬����   

CCTransitionScene* SceneManager::createTransition(float t, cocos2d::CCScene *s)  
{  
	nIdx++;  
	//�����ʵд�Ĳ���...������������Ǵӵڶ�����ʼ���ŵ�   

	nIdx=nIdx%MAX_TRANS_SCENE;  

	//�������ת����ȡ�࣬ȷ���������0-3֮�����   
	switch (nIdx) {  
	case 0: return FadeWhiteTransition::transitionWithDuration(t, s);  
	case 1: return ZoomFlipXLeftOver::transitionWithDuration(t, s);  
	case 2: return FlipYDownOver::transitionWithDuration(t, s);  
		break;            
	default:  
		break;  
	}  
	//�ֱ𷵻������ֲ�ͬ��ת��   
	return NULL;       
}  

SceneManager::SceneManager(void)
{
}


SceneManager::~SceneManager(void)
{
}

void SceneManager::goMenu()  
{
	CCLayer* layer = MainMenuLayer::create();  
	SceneManager::go(layer);  
}

void SceneManager::goPlay()
{
	/*LoadScene* loadScene = LoadScene::createWithScene(LOAD_SCENE_PLAY);
	CCDirector* director = CCDirector::sharedDirector();  
	director->replaceScene(CCTransitionFade::create(TRANSITION_DURATION, loadScene));
	return;*/
	CCLayer* layer = PlayLayer::create();
	//����һ��PlayLayer�Ľڵ�   
	SceneManager::go(layer);  
	//����go�����Ķ���...���layerֱ�ӱ����ӵ�Scene����  
}  

void SceneManager::goStop()
{
	CCLayerColor* layer = StopLayer::create();
	layer->initWithColor(ccc4(0, 0, 0, 125));
	SceneManager::push(layer);
}

void SceneManager::go(CCLayer* layer)  
{      
	nIdx++;  
    //�����ʵд�Ĳ���...������������Ǵӵڶ�����ʼ���ŵ�   
  
    nIdx=nIdx%MAX_TRANS_SCENE;  

	CCDirector* director = CCDirector::sharedDirector();  
	CCScene* newScene = SceneManager::wrap(layer);  
	if (director->getRunningScene()) //��仰 ���п���д�Ĳ��԰�  ����λ����֪����ôд ��֪��...   
	{  
		director->replaceScene(CCTransitionFade::create(TRANSITION_DURATION, newScene));
		//director->replaceScene(createTransition(TRANSITION_DURATION, newScene));
	}  
	else   
	{  
		director->runWithScene(newScene);  
	}  
}

CCScene* SceneManager::wrap(CCLayer* layer)  
{  
	CCScene* newScene = CCScene::create();  
	newScene->addChild(layer);  
	return newScene;  
}  

void SceneManager::push(CCLayer* layer)  
{
	CCDirector* director = CCDirector::sharedDirector();  
	CCScene* newScene = SceneManager::wrap(layer);  
	if (director->getRunningScene()) //��仰 ���п���д�Ĳ��԰�  ����λ����֪����ôд ��֪��...   
	{  
		director->pushScene( newScene);
	}
}

void SceneManager::pop()
{
	CCDirector* director = CCDirector::sharedDirector();  
	if (director->getRunningScene())
	{  
		director->popScene();
	}
}