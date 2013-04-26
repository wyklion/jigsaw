#ifndef __PIECES_H__
#define __PIECES_H__

#include "cocos2d.h"

class PiecesSprite : public CCSprite
{
public:
	~PiecesSprite(){releasePoly();};
	//virtual draw (void);
	virtual bool init();
	//static PiecesSprite* createPieceByTexture(CCTexture2D *pTexture, const CCRect& rect);

	virtual void draw();
	/*
	void customInit();
	void setTouch();

	//重写触屏相关函数----   
	virtual void onExit();  
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);    
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);  
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	*/
	static PiecesSprite* createPiece(const char *pszFileName,
								 CCPoint *uvs,
                                 int verCnt,
                                 const int *indices);

private:
    //初始化顶点信息
    bool initWithUV(const cocos2d::CCPoint *uvs,
                    const int *indices,
                    int verCnt);
    
    //计算中点
    CCPoint getCenter();
    void translate(const CCPoint&);
    void drawPoly();
    void releasePoly();

private:
    //多边形顶点
    ccVertex2F *vertexs_;
    //定点纹理坐标
    ccVertex2F *uvs_;
    //三角形索引
    unsigned short *indices_;
    //顶点颜色
    unsigned char *colors_;
    //顶点数目
    int verCnt_;
};

#endif