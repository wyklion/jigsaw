#include "Jigsaw.h"


bool PlayLayer::init()  
{  
	if (!BaseLayer::init())  
	{  
		return false;  
	}  
	// elastic effect
    CCSize s = CCDirector::sharedDirector()->getWinSize();

	//CCMenuItemFont* back=CCMenuItemFont::create("back",this,menu_selector(PlayLayer::back));
	//back->setFontSize(50);
	//CCSize backsize = back->getContentSize();
	////老问题 别忘记类名 还有这个只需要函数名就够了  
	//CCMenu* menu=CCMenu::create(back,NULL);   
	////Items！ 单复数 要注意   
	//menu->setPosition(ccp(s.width*0.5, backsize.height*0.5));
	//this->addChild(menu);  
	
	m_picName = "girl.png";	
	CCTextureCache::sharedTextureCache()->addImage(m_picName);
	CCTextureCache::sharedTextureCache()->addImage("bottom.png");

	CCMenuItemImage* stopItem = CCMenuItemImage::create(
            "stopButton.png",
            "stopButtonSelected.png",
            this,
            menu_selector(PlayLayer::menuStopCallback));
	stopItem->setPosition(ccp(s.width - 20, s.height - 20));
	// Create a menu with the "close" menu item, it's an auto release object.
	m_stopMenu = CCMenu::create(stopItem, NULL);
	m_stopMenu->setPosition(CCPointZero);
	this->addChild(m_stopMenu, 10);
	
	JigsawSound::playBackGround();
	m_pieceLayer = NULL;
	m_batchNode = NULL;
	m_pieceManager = NULL;
	
	CCSprite* bottomSprite = CCSprite::create("bottom.png");
	CCSize contSize = bottomSprite->getContentSize();
	bottomSprite->setPosition(ccp(s.width / 2, contSize.height / 2));
	//this->addChild(bottomSprite, 0);
	createBottomLayer();

	JigsawSound::loadSounds();

	//player->setScale(0.8f);
	m_row = 4;
	m_col = 3;
	
	//if(createPieces2())
	if(getPiecesSprite())
		return true;
	else
		return false;

}  

bool PlayLayer::createPieces2()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
	m_pieceLayer = CCLayer::create();
	m_pieceLayer->setContentSize(s);
	addChild(m_pieceLayer);
	
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(m_picName);
	int picWidth = texture->getPixelsWide();
	int picHeight = texture->getPixelsHigh();
	int eachWidth = picWidth / m_col;
	int eachHeight = picHeight / m_row;

	CutManager cutManager(m_row, m_col, eachWidth, eachHeight);
	std::vector<CCPoint> points;
	cutManager.getPiecePoints(0, 0, points);
	for(size_t i = 0; i < points.size(); i++)
	{
		//CCLog("(%f, %f) ", points[i].x, points[i].y);
	}

	int order = 0;
	for(int i = 0; i < m_row; i++)
	{
		for(int j = 0; j < m_col; j++)
		{
			CCClippingNode *clipper = CCClippingNode::create();
			clipper->setContentSize(CCSizeMake(eachWidth*2, eachHeight*2));
			clipper->setAnchorPoint(ccp(0.5, 0.5));
			//clipper->setPosition( ccp(s.width / 2,s.height / 2) );
			clipper->setAlphaThreshold(0.05f);
			//clipper->runAction(CCRepeatForever::create(CCRotateBy::create(1, 45)));
			//随机摆放
			int randX = rand() % ((int)s.width - eachWidth) + eachWidth/2;
			int randY = rand() % ((int)s.height - eachHeight) + eachHeight/2;
			if(i==0&&j==0)
			{
				randX=eachWidth;randY=eachHeight;
			}
			clipper->setPosition(ccp(randX, randY));
			int randRotate = rand() % 30 - 15;
			//%clipper->setRotation((float)randRotate);
			order++;
			m_pieceLayer->addChild(clipper, order, order);

			//创建“裁减模板”
			std::vector<CCPoint> points;
			cutManager.getPiecePoints(i, j, points);
			size_t count = points.size();
			CCPoint* p = new CCPoint[count];
			for(size_t k = 0; k < count; k++)
			{
				p[k] = CCPoint(points[k].x + eachWidth/2, points[k].y + eachHeight/2);
				CCLog("(%f, %f) ", p[k].x, p[k].y);
			}

			CCDrawNode *stencil = CCDrawNode::create();			
			CCPoint p2[] = {ccp(80, 270), ccp(80, 90), ccp(240, 90), ccp(100, 150), };
			ccColor4F white = {1, 1, 1, 1};
			stencil->drawPolygon(p2, 4, white, 1, white);
			//stencil->setVisible(false);
			clipper->setStencil(stencil);
			delete[] p;

			//设置裁减节点类所放的内容
			int left = eachWidth * j - eachWidth/2;
			float x = 0.5;
			float y = 0.5;
			int width = eachWidth*2;
			int height = eachHeight*2;
			if(j == 0)
			{
				left = 0;
				x = 0.25;
			}
			else if(j == m_col - 1)
			{
				left = eachWidth * (j-1);
				x = 0.75;
			}
			int top = eachHeight * i - eachHeight/2;
			if(i == 0)
			{
				top = 0;
				y = 0.75;
			}
			else if(i == m_row - 1)
			{
				top = eachHeight * (i-1);
				y = 0.25;
			}
			CCSprite *content = CCSprite::create(m_picName, CCRectMake(left, top, width, height));
			content->setAnchorPoint(ccp(x, y));
			content->setPosition(ccp(clipper->getContentSize().width / 2, clipper->getContentSize().height / 2) );
			clipper->addChild(content);
			return true;
		}
	}
	return true;
}

bool PlayLayer::createPieces()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    //m_batchNode = CCSpriteBatchNode::create(m_picName, 100);
	//this->addChild(m_batchNode, 1);
	
	//CCTexture2D* texture = m_batchNode->getTexture();
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(m_picName);
	int picWidth = texture->getPixelsWide();
	int picHeight = texture->getPixelsHigh();
	int eachWidth = picWidth / m_col;
	int eachHeight = picHeight / m_row;
	//int eachWidth = s.width / 4 * 3 / m_col;
	//int eachHeight = s.height / 4 * 3 / m_row;

	int order = 0;
	//for(int i = 0; i < m_row; i++)
	//{
	//	for(int j = 0; j < m_col; j++)
	//	{
			CCPoint p[] = {ccp(0, 0), ccp(0, 0.4), ccp(0.4, 0.4), ccp(0.1, 0.3)};
			int index[] = {0, 1, 2, 4};
			PiecesSprite* piece = PiecesSprite::createPiece(m_picName, p, 4, index);
			
			if(!piece)
				return false;

			int randX = rand() % ((int)s.width - eachWidth) + eachWidth/2;
			int randY = rand() % ((int)s.height - eachHeight) + eachHeight/2;
			piece->setPosition(ccp(randX, randY));
			int randRotate = rand() % 30 - 15;
			piece->setRotation((float)randRotate);
			addChild(piece, order, order);
	//		m_batchNode->addChild(piece, order, order);
	//		order++;
	//	}
	//}
	//m_pieceManager = new PieceManager(m_batchNode, m_row, m_col);
	return true;

}

void PlayLayer::createBottomLayer()
{
 //   CCSize s = CCDirector::sharedDirector()->getWinSize();
	//CCScrollView *scrollView = CCScrollView::create();
	//CCLayer* layer = CCLayer::create();
 //   CCSprite *sprite1 = CCSprite::create("stopButton.png");
	//
 //   layer->setAnchorPoint(CCPointZero);
 //   layer->setPosition(CCPointZero);
 //   layer->setContentSize(CCSizeMake(640, 160));

	//scrollView->setPosition(CCPointZero);
 //   scrollView->setContentOffset(CCPointZero);
 //   scrollView->setContentSize(CCSizeMake(640, 160));
 //   scrollView->setContainer(layer);

	//scrollView->setDirection(CCScrollViewDirectionHorizontal);
 //   scrollView->setDelegate(this);

	//this->addChild(scrollView, 0);

}

bool PlayLayer::getPiecesSprite()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    m_batchNode = CCSpriteBatchNode::create(m_picName, 100);
	this->addChild(m_batchNode, 1);
	
	CCTexture2D* texture = m_batchNode->getTexture();
	int picWidth = texture->getPixelsWide();
	int picHeight = texture->getPixelsHigh();
	int eachWidth = picWidth / m_col;
	int eachHeight = picHeight / m_row;
	//int eachWidth = s.width / 4 * 3 / m_col;
	//int eachHeight = s.height / 4 * 3 / m_row;

	int order = 0;
	for(int i = 0; i < m_row; i++)
	{
		for(int j = 0; j < m_col; j++)
		{
			CCSprite* piece = CCSprite::create(m_picName, 
				CCRectMake(eachWidth * j, eachHeight * i, eachWidth, eachHeight));
			//CCSprite* piece = PiecesSprite::createPiece(m_picName, 
				//CCRectMake(eachWidth * j, eachHeight * i, eachWidth, eachHeight));
			/*CCPoint p[] = {ccp(0, 1.0), ccp(0.3, 0.3), ccp(0.4, 0.4), ccp(0.4, 0.2)};
			int index[] = {0, 1, 2, 3};
			PiecesSprite* piece = PiecesSprite::createPiece(m_picName, p, 4, index);*/
			
			if(!piece)
				return false;

			int randX = rand() % ((int)s.width - eachWidth) + eachWidth/2;
			int randY = rand() % ((int)s.height - eachHeight) + eachHeight/2;
			piece->setPosition(ccp(randX, randY));
			int randRotate = rand() % 30 - 15;
			piece->setRotation((float)randRotate);
			//addChild(piece, order, order);
			m_batchNode->addChild(piece, order, order);
			order++;
		}
	}
	m_pieceManager = new PieceManager(m_batchNode, m_row, m_col);
	return true;
}

void PlayLayer::back(cocos2d::CCObject *pSender)  
{  
	SceneManager::goMenu();  
	//back就是回主菜单，这里调用了人见人爱 花见花开的静态函数 goMenu  
}

PlayLayer::~PlayLayer()
{
	/*for(int i = 0; i < (int)m_pieces.count(); i++)
	{
		((PiecesSprite*)m_pieces.objectAtIndex(i))->release();
	}
	m_texture->release();*/
}


//---SpriteClassModel 按键-----------------
// 别忘记加入 TouchDispatcher  ,TouchDispatcher一般放在onenter 绑定，onexit 删除
bool PlayLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCPoint touchPoint = touch->getLocation();
	int topOrder = -1;
	int tag = 0;
	for(int i = 0; i < (int)m_batchNode->getChildrenCount(); i++)
	{
		CCSprite* piece = (CCSprite*)m_batchNode->getChildByTag(i);
		CCRect rect = piece->boundingBox();
		if(rect.containsPoint(touchPoint))
		{
			int order = piece->getZOrder();
			if(order > topOrder)
			{
				topOrder = order;
				tag = piece->getTag();
			}
		}
	}
	if(topOrder > -1)
		m_pieceManager->beginTouch(touch, tag);
	//CCLog("%s","精灵111~ccTouchBegan");   
	return true;
}

void PlayLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{   
	m_pieceManager->move(touch); 
	//CCPoint touchPoint = touch->getLocation();  	
	//获取当前用户触屏点坐标并将3d坐标映射2d坐标系   
	//touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	//touchPoint.x, getPosition().y   
	//if(touchPoint.x> CCDirector::sharedDirector()->getWinSize().width/2)
		//CCLog("%s","精灵22~~ccTouchMoved");
}

void PlayLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{    
	m_pieceManager->endTouch(touch);
	
	//if(m_pieceManager->isFinished())
	//	SceneManager::goMenu();
	//CCLog("%s","精灵33~~~ccTouchEnded");
}

void PlayLayer::onEnter()
{   
	//JigsawSound::resumeMusic();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 100, false);
	CCLayer::onEnter();
}

void PlayLayer::onExit()
{   
	JigsawSound::stopAll();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);  
	CCLayer::onExit();
}

void PlayLayer::menuStopCallback(CCObject* pSender)
{
	JigsawSound::pauseMusic();
	StopLayer* stop = StopLayer::create();
	stop->initWithColor(ccc4(0,0,0,125));
	this->addChild(stop, 2);
	//SceneManager::goStop(); 
}

void PlayLayer::setStopVisible(bool b)
{ 
	if(m_stopMenu)
		m_stopMenu->setVisible(b);
}

void PlayLayer::retry()
{
	this->removeFromParentAndCleanup(true);
	SceneManager::goPlay();
}