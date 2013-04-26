#ifndef __STOP_LAYER_H__
#define __STOP_LAYER_H__   
#include "cocos2d.h"   
#include "SceneManager.h"   

using namespace cocos2d; 


class StopLayer : public CCLayerColor
{
public:	
	virtual bool init(); //CCLayer�Ķ����Ƕ������������������virtual�ؼ���   

	CREATE_FUNC(StopLayer);   
	//ǧ�����������������ֵĺ�
	
	void resume(CCObject* pSender);
	void retry(CCObject* pSender);
	void quit(CCObject* pSender);
	
    void onEnter();
    void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

private:
    // ģ̬�Ի���˵�
    CCMenu* m_menu;
    // ��¼�˵����
    bool m_touchedMenu;
};

#endif