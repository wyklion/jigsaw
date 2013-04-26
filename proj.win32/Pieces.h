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

	//��д������غ���----   
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
    //��ʼ��������Ϣ
    bool initWithUV(const cocos2d::CCPoint *uvs,
                    const int *indices,
                    int verCnt);
    
    //�����е�
    CCPoint getCenter();
    void translate(const CCPoint&);
    void drawPoly();
    void releasePoly();

private:
    //����ζ���
    ccVertex2F *vertexs_;
    //������������
    ccVertex2F *uvs_;
    //����������
    unsigned short *indices_;
    //������ɫ
    unsigned char *colors_;
    //������Ŀ
    int verCnt_;
};

#endif