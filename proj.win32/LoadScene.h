#ifndef __LOAD_SCENE_H__
#define __LOAD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

enum LoadSceneType
{
	LOAD_SCENE_PLAY,
	LOAD_SCENE_MENU
};

class LoadScene : public CCScene
{
public:

	static LoadScene* createWithScene(LoadSceneType scene);
	LoadScene* initWithScene(LoadSceneType scene);
	CREATE_FUNC(LoadScene);
	
    void onEnter();
	virtual void update(float t);

private:
	LoadSceneType m_loadScene;	
};


#endif