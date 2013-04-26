#ifndef __PLAY_LAYER_H__
#define __PLAY_LAYER_H__   
#include "cocos2d.h"   
#include "SceneManager.h"   

using namespace cocos2d; 

class PlayLayer : public BaseLayer  
{  
public:
	~PlayLayer();
	virtual bool init(); //CCLayer�Ķ����Ƕ������������������virtual�ؼ���   

	CREATE_FUNC(PlayLayer);   
	//ǧ�����������������ֵĺ�
	
	bool getPiecesSprite();
	bool createPieces();
	bool createPieces2();

	//��д������غ���----   
	virtual void onEnter();
	virtual void onExit();  
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);    
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);  
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	
	void back (CCObject* pSender);  
	void menuStopCallback(CCObject* pSender);
	void setStopVisible(bool b);
	void retry();

	void createBottomLayer();

private:
	CCLayer* m_pieceLayer;
	CCMenu* m_stopMenu;
	CCSpriteBatchNode* m_batchNode;
	PieceManager* m_pieceManager;
	const char* m_picName;
	int m_row;
	int m_col;
};

#endif

