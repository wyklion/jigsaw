#ifndef __PIECE_MANAGER_H__
#define __PIECE_MANAGER_H__   
#include "cocos2d.h"   

using namespace cocos2d; 

class PieceManager
{
	enum MERGE_ORIENT
	{
		MERGE_TO_LEFT,
		MERGE_TO_RIGHT,
		MERGE_TO_UP,
		MERGE_TO_DOWN
	};
	struct TouchedSprite
	{
		TouchedSprite(CCTouch* touch, int tag)
			: m_touch(touch), m_tag(tag){}
		CCTouch* m_touch;
		int m_tag;
	};
public:
	PieceManager() { m_batchNode = NULL;}
	PieceManager(CCSpriteBatchNode* batchNode, int row, int col)
		: m_batchNode(batchNode), m_row(row), m_col(col), m_finish(false) { }
	~PieceManager();
public:
	void beginTouch(CCTouch* touch, int tag);
	void move(CCTouch* touch);
	void endTouch(CCTouch* touch);
public:
	void checkPieceMoveEnd(TouchedSprite ts);
	std::vector<int>* getGroupPieces(int tag);

	bool checkOnePieceRound(int tag);
	bool check(int tag, MERGE_ORIENT orient);
	void mergePiece(int touchTag, int tag);

	void setTopOrder(int tag);
	void setMergePieceSameOrder(int from, int to);
	int getPartCount();
	bool isFinished() { return m_finish; }

	bool getRectMoveBackDelta(const CCRect& rect, CCPoint& delta);
	void moveBackToScreen(int tag);
	void finishAction(int tag);

private:
	CCSpriteBatchNode* m_batchNode;
	int m_row;
	int m_col;
	bool m_finish;
	std::vector<TouchedSprite> m_touchedSprites;
	std::map<int, std::vector<int>*> m_pieceGroups;
};

#endif