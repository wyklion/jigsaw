#ifndef __PLAY_LAYER_H__
#define __PLAY_LAYER_H__   
#include "cocos2d.h"   
#include "SceneManager.h"   

using namespace cocos2d; 

class PlayLayer : public BaseLayer  
{  
public:
	~PlayLayer();
	virtual bool init(); //CCLayer的儿子们都有这玩意儿。别忘了virtual关键字   

	CREATE_FUNC(PlayLayer);   
	//千万别忘了这个风情万种的宏
	
	bool getPiecesSprite();
	bool createPieces();
	bool createPieces2();

	//重写触屏相关函数----   
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

