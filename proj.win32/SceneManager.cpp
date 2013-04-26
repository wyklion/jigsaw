#include "SceneManager.h"

//--------------Translation类的定义----------------------   
//下面定义了三种不同的转场，   
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

#define MAX_TRANS_SCENE 3 //定义最大的转换场景数   

int SceneManager::nIdx= -1; //初始化静态变量   

CCTransitionScene* SceneManager::createTransition(float t, cocos2d::CCScene *s)  
{  
	nIdx++;  
	//这块其实写的不好...这个场景现在是从第二个开始播放的   

	nIdx=nIdx%MAX_TRANS_SCENE;  

	//这块对最大转场数取余，确保不会出现0-3之外的数   
	switch (nIdx) {  
	case 0: return FadeWhiteTransition::transitionWithDuration(t, s);  
	case 1: return ZoomFlipXLeftOver::transitionWithDuration(t, s);  
	case 2: return FlipYDownOver::transitionWithDuration(t, s);  
		break;            
	default:  
		break;  
	}  
	//分别返回了三种不同的转场   
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
	//生成一个PlayLayer的节点   
	SceneManager::go(layer);  
	//看看go函数的定义...这个layer直接被他扔到Scene里了  
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
    //这块其实写的不好...这个场景现在是从第二个开始播放的   
  
    nIdx=nIdx%MAX_TRANS_SCENE;  

	CCDirector* director = CCDirector::sharedDirector();  
	CCScene* newScene = SceneManager::wrap(layer);  
	if (director->getRunningScene()) //这句话 很有可能写的不对啊  有哪位大侠知道怎么写 告知下...   
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
	if (director->getRunningScene()) //这句话 很有可能写的不对啊  有哪位大侠知道怎么写 告知下...   
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