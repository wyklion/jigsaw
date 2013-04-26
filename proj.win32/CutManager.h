#ifndef __CUT_MANAGER__H_
#define __CUT_MANAGER__H_

#include "cocos2d.h"
using namespace cocos2d; 

typedef std::vector<CCPoint> CCPointVector;
class CutManager
{
	enum PIECE_SIDE
	{
		SIDE_LEFT,
		SIDE_RIGHT,
		SIDE_UP,
		SIDE_DOWN
	};
public:
	CutManager(void);
	~CutManager(void);
	CutManager(int m_row, int m_col, int eachWidth, int eachHeight);

public:
	void getVPoints();
	void getHPoints();
	void getRandomVPoints(CCPointVector& points);
	void getRandomHPoints(CCPointVector& points);

	void getPiecePoints(int row, int col, CCPointVector& points);
	void addPoints(int row, int col, PIECE_SIDE side, CCPointVector& points);

private:
	int m_row;
	int m_col;
	int m_eachWidth;
	int m_eachHeight;

	CCPointVector** m_vPoints;
	CCPointVector** m_hPoints;
};

#endif