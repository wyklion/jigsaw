#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "MainMenu.h"
USING_NS_CC;
#define TRANSITION_DURATION 1.2f   

class SceneManager : public CCObject
{
public:
	SceneManager(void);
	~SceneManager(void);
	
    static void goMenu();  
	static void goPlay();
	static void goStop();
    static void go(CCLayer* layer);  
    static void push(CCLayer* layer);  
	static void pop();
    static CCScene* wrap(CCLayer* layer);      
	
	//去CreditsLayer那边去   
    static int nIdx;  
    //声明静态旗标   
    static CCTransitionScene* createTransition(float t,CCScene* s);  
    //用来返回 CCTransitionScene 对象，具体看.cpp中的实现
};

#endif