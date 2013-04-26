#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include "Jigsaw.h"

class MainMenuScene : public CCScene
{
public:
	MainMenuScene(void);
	~MainMenuScene(void);

	virtual bool init();
	CREATE_FUNC(MainMenuScene);
	
};


class MainMenuLayer : public BaseLayer
{
public:
	MainMenuLayer() {};
	virtual ~MainMenuLayer();
	virtual bool init();
	CREATE_FUNC(MainMenuLayer);

	void menuCallbackPlay(CCObject* sender);
	void menuCallbackSetting(CCObject* sender);
};

#endif