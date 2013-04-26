#include "Jigsaw.h"

PiecesSprite* PiecesSprite::createPiece(const char* picName,
								 CCPoint *uvs,
                                 int verCnt,
                                 const int *indices)
{
	PiecesSprite* piece = new PiecesSprite();
	//piece->create(picName);
	//piece->create(picName, rect);
	//piece->setTouch();
    if(piece)
    if (piece && piece->initWithFile(picName)
		&& piece->initWithUV(uvs, indices, verCnt))
	{
		piece->autorelease();
        //piece->customInit();//自定义的方法用来初始化自己的特殊属性
        return piece;
    }

    CC_SAFE_DELETE(piece);

    return piece;

}

//初始化顶点信息
bool PiecesSprite::initWithUV(const CCPoint *uvs,
                             const int *indices,
                             int verCnt)
{
    //内存分配
    vertexs_ = new ccVertex2F[verCnt];
    uvs_     = new ccVertex2F[verCnt];
    indices_ = new unsigned short[(verCnt-2)*3];
    colors_  = new unsigned char[verCnt*4];
    
    //失败处理
    if(!vertexs_ || !uvs_ || !indices_ || !colors_) {
        releasePoly();
        return false;
    }
    
    //贴图大小
    CCSize rc = m_pobTexture->getContentSize();
    
    for(int i = 0; i < verCnt; ++i) {
        //根据纹理坐标以及纹理大小计算顶点坐标
        vertexs_[i].x = uvs[i].x*rc.width;
        //cocos2dx纹理坐标以左上角为原点
        vertexs_[i].y = (1.0-uvs[i].y)*rc.height;
        
        uvs_[i].x = uvs[i].x;
        uvs_[i].y = uvs[i].y;
    }
    
    for(int i = 0; i < (verCnt-2)*3; ++i)
        indices_[i] = indices[i];
    
    memset(colors_, 255, sizeof(unsigned char)*verCnt*4);
    
    verCnt_ = verCnt;
    
    translate(getCenter());
    
    return true;
}

//计算中点
CCPoint PiecesSprite::getCenter()
{
    if(!vertexs_) return ccp(0,0);
    
    float minx = vertexs_[0].x,
          maxx = vertexs_[0].x,
          miny = vertexs_[0].y,
          maxy = vertexs_[0].y;
    
    //计算所有顶点坐标的中心点坐标
    for(int i = 0; i < verCnt_; ++i) {
        minx = minx>vertexs_[i].x?vertexs_[i].x:minx;
        maxx = maxx<vertexs_[i].x?vertexs_[i].x:maxx;
        
        miny = miny>vertexs_[i].y?vertexs_[i].y:miny;
        maxy = maxy<vertexs_[i].y?vertexs_[i].y:maxy;
    }
    
    return ccp((minx+maxx)*0.5, (miny+maxy)*0.5);
}

void PiecesSprite::translate(const cocos2d::CCPoint& pos)
{
    //设置锚点
    CCSize rc = m_pobTexture->getContentSize();
    setAnchorPoint(ccp(pos.x/rc.width, pos.y/rc.height));
}

void PiecesSprite::drawPoly()
{
    CC_NODE_DRAW_SETUP();
    
    ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );
    
    if (m_pobTexture != NULL) {
        ccGLBindTexture2D( m_pobTexture->getName() );
    }
    else {
        ccGLBindTexture2D(0);
    }
    
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);
    
    //顶点，纹理，颜色
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertexs_);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, uvs_);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, colors_);
    //根据索引draw三角形
    //glDrawElements(GL_TRIANGLES, (verCnt_-2)*3, GL_UNSIGNED_SHORT, indices_);
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, verCnt_);
	glDrawArrays(GL_POLYGON, 0, verCnt_);

    CC_INCREMENT_GL_DRAWS(1);
}

void PiecesSprite::releasePoly()
{
    CC_SAFE_DELETE(vertexs_);
    CC_SAFE_DELETE(uvs_);
    CC_SAFE_DELETE(indices_);
    CC_SAFE_DELETE(colors_);
}

void PiecesSprite::draw(void)
{
    drawPoly();
}

bool PiecesSprite::init()
{
	if (!CCSprite::init()) 
	{
		return false;
	}
	return true;
}
/*
void PiecesSprite::customInit()
{


}
//---SpriteClassModel 按键-----------------
// 别忘记加入 TouchDispatcher  ,TouchDispatcher一般放在onenter 绑定，onexit 删除
bool PiecesSprite::ccTouchBegan(CCTouch* touch, CCEvent* event)
{  
	CCLog("%s","精灵111~ccTouchBegan");   
	return true;
}

void PiecesSprite::ccTouchMoved(CCTouch* touch, CCEvent* event)
{    
	CCPoint touchPoint = touch->getLocation();  
	//获取当前用户触屏点坐标并将3d坐标映射2d坐标系   
	//touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	//touchPoint.x, getPosition().y   
	if(touchPoint.x> CCDirector::sharedDirector()->getWinSize().width/2)
	{     
		CCLog("%s","精灵22~~ccTouchMoved");   
	}
}

void PiecesSprite::ccTouchEnded(CCTouch* touch, CCEvent* event)
{    
	CCLog("%s","精灵33~~~ccTouchEnded");
} 

void PiecesSprite::setTouch()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
	//    false 是否被 点到下一层   事件是否被传递  ture 不能传递  false是可以传递
}


void PiecesSprite::onExit()
{   
	//移除监听   
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);  
	CCSprite::onExit();
}
*/