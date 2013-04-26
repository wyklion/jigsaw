#include "CutManager.h"
#include <math.h>

CutManager::CutManager(void)
{
}


CutManager::~CutManager(void)
{
	for(int i = 0; i < m_row; i++) 
		delete []m_vPoints[i]; 
	delete []m_vPoints; 
	
	//for(int i = 0; i < m_row+1; i++) 
	//	delete []m_hPoints[i]; 
	//delete []m_hPoints; 
}

CutManager::CutManager(int row, int col, int eachWidth, int eachHeight)
	: m_row(row), m_col(col), m_eachWidth(eachWidth), m_eachHeight(eachHeight)
{
	getVPoints();
	getHPoints();
}

void CutManager::getVPoints()
{
	m_vPoints = new CCPointVector* [m_row];
	for(int i = 0; i < m_row; i++)
	{
		m_vPoints[i] = new CCPointVector[m_col+1];
		for(int j = 1; j < m_col; j++)
		{
			getRandomVPoints(m_vPoints[i][j]);
		}
	}
}

void CutManager::getHPoints()
{
	m_hPoints = new CCPointVector* [m_row+1];
	for(int i = 0; i < m_row+1; i++)
	{
		m_hPoints[i] = new CCPointVector[m_col];
		if(i==0 || i == m_row)
			continue;
		for(int j = 0; j < m_col; j++)
		{				
			getRandomHPoints(m_hPoints[i][j]);
		}
	}
}

static CCPoint getCirclePoint(const CCPoint& ct, float radius, int i)
{
	float k = (float)i*3.1415927/180;
	float x = ct.x + radius * cosf(k);
	float y = ct.y + radius * sinf(k);
	return CCPoint(x, y);
}

void CutManager::getRandomVPoints(CCPointVector& points)
{
	CCPoint top(0, m_eachHeight);
	CCPoint bottom(0, 0);

	bool left = rand() % 2 == 1 ? true : false;	 
	int side = left ? -1 : 1;
	int unit = (top.y-bottom.y)/5;
	int xOffset = 0;//rand() % unit * side / 2;
	CCPoint top2(top.x-xOffset, top.y-unit*2);
	CCPoint bottom2(top2.x, bottom.y+unit*2);
	float radius = (float)unit/sqrtf(2);
	
	CCPoint ct(top2.x + unit*side/2, (top2.y+bottom2.y)/2);
	if(left)
	{
		for(int i = 45; i <= 315; i+=10)
		{
			points.push_back(getCirclePoint(ct, radius, i));
		}
	}
	else
	{
		for(int i = 135; i > 0; i-=10)
		{
			points.push_back(getCirclePoint(ct, radius, i));
		}
		for(int i = 355; i >= 225; i-=10)
		{
			points.push_back(getCirclePoint(ct, radius, i));
		}
	}
}

void CutManager::getRandomHPoints(CCPointVector& points)
{
	CCPoint left(0, 0);
	CCPoint right(m_eachWidth, 0);

	bool up = rand() % 2 == 1 ? true : false; 
	int side = up ? 1 : -1;
	int unit = (right.x-left.x)/5;
	int yOffset = 0;//rand() % unit * side / 2;
	CCPoint left2(left.x+unit*2, left.y-yOffset);
	CCPoint right2(right.x-unit*2, left2.y);
	float radius = (float)unit/sqrtf(2);

	CCPoint ct((left2.x+right2.x)/2, left2.y + unit*side/2);
	if(up)
	{
		for(int i = 225; i > 0; i-=10)
		{
			points.push_back(getCirclePoint(ct, radius, i));
		}
		for(int i = 355; i >= 315; i-=10)
		{
			points.push_back(getCirclePoint(ct, radius, i));
		}
	}
	else
	{
		for(int i = 135; i <360; i+=10)
		{
			points.push_back(getCirclePoint(ct, radius, i));
		}
		for(int i = 5; i <= 45; i+=10)
		{
			points.push_back(getCirclePoint(ct, radius, i));
		}
	}
}

void CutManager::getPiecePoints(int row, int col, CCPointVector& points)
{
	CCPoint topLeft(0, m_eachHeight);
	CCPoint bottomLeft(0, 0);
	CCPoint bottomRight(m_eachWidth, 0);
	CCPoint topRight(m_eachWidth, m_eachHeight);

	points.push_back(topLeft);
	//addPoints(row, col, SIDE_LEFT, points);
	points.push_back(bottomLeft);
	//addPoints(row, col, SIDE_DOWN, points);
	points.push_back(bottomRight);
	//addPoints(row, col, SIDE_RIGHT, points);
	points.push_back(topRight);
	//addPoints(row, col, SIDE_UP, points);

}

void CutManager::addPoints(int row, int col, PIECE_SIDE side, CCPointVector& points)
{
	switch(side)
	{
		case SIDE_LEFT:
		{
			CCPointVector& vpoints = m_vPoints[row][col];
			for(size_t i = 0; i < vpoints.size(); i++)
			{
				points.push_back(vpoints[i]);
			}
			break;
		}
		case SIDE_DOWN:
		{
			CCPointVector& hpoints = m_hPoints[row+1][col];
			for(size_t i = 0; i < hpoints.size(); i++)
			{
				points.push_back(hpoints[i]);
			}
			break;
		}
		case SIDE_RIGHT:
		{
			CCPointVector& vpoints = m_vPoints[row][col+1];
			if(vpoints.empty())
				break;
			for(size_t i = vpoints.size()-1; i > 0; i--)
			{
				CCPoint p(vpoints[i].x + m_eachWidth, vpoints[i].y);
				points.push_back(p);
			}
			break;
		}
		case SIDE_UP:
		{
			CCPointVector& hpoints = m_hPoints[row][col];
			if(hpoints.empty())
				break;
			for(size_t i = hpoints.size()-1; i > 0 ; i--)
			{
				CCPoint p(hpoints[i].x, hpoints[i].y + m_eachHeight);
				points.push_back(p);
			}
			break;
		}
		default:
			break;
	}
}


