#include "Jigsaw.h"

void PieceManager::finishAction(int tag)
{
	/*
	CCSprite* piece = NULL;
	std::vector<int>* pieces = getGroupPieces(tag);
	if(pieces == NULL)
	{
		piece = (CCSprite*)m_batchNode->getChildByTag(tag);
		piece->getActionManager();
		CCPoint pos = piece->getPosition();
		CCActionInterval* actionTo = CCMoveTo::create(0.3f, ccp(pos.x + delta.x, pos.y + delta.y));
		piece->runAction(actionTo);
	}
	else
	{
		std::vector<int>::iterator pieceIter;
		for (pieceIter=pieces->begin();pieceIter!=pieces->end();pieceIter++)  
		{
			piece = (CCSprite*)m_batchNode->getChildByTag(*pieceIter);
			CCPoint pos = piece->getPosition();
			CCActionInterval* actionTo = CCMoveTo::create(0.3f, ccp(pos.x + delta.x, pos.y + delta.y));
			piece->runAction(actionTo);
		}
	}
	*/
}

void PieceManager::beginTouch(CCTouch* touch, int tag)
{
	JigsawSound::playTouch();
	setTopOrder(tag);
	m_touchedSprites.push_back(TouchedSprite(touch, tag));
	finishAction(tag);
}

void PieceManager::setMergePieceSameOrder(int from, int to)
{	
	CCSprite* fromPiece = (CCSprite*)m_batchNode->getChildByTag(from);
	CCSprite* toPiece = (CCSprite*)m_batchNode->getChildByTag(to);
	
	int fromOrder = fromPiece->getZOrder();
	int toOrder = toPiece->getZOrder();
	m_batchNode->reorderChild(fromPiece, toOrder);
	
	int standOrder = fromOrder < toOrder ? fromOrder : toOrder;
	for(int i = 0; i < (int)m_batchNode->getChildrenCount(); i++)
	{
		CCSprite* onePiece = (CCSprite*)m_batchNode->getChildByTag(i);
		int oneOrder = onePiece->getZOrder();
		if(oneOrder > standOrder)
		{
			m_batchNode->reorderChild(onePiece, oneOrder - 1);
		}
	}
}

void PieceManager::setTopOrder(int tag)
{
	int partNum = getPartCount();
	//CCLog("partNum %d...", partNum);

	CCSprite* piece = (CCSprite*)m_batchNode->getChildByTag(tag);
	if(!piece) return;
	int order = piece->getZOrder();
	for(int i = 0; i < (int)m_batchNode->getChildrenCount(); i++)
	{
		CCSprite* onePiece = (CCSprite*)m_batchNode->getChildByTag(i);
		int oneOrder = onePiece->getZOrder();
		if(oneOrder == order)
		{
			m_batchNode->reorderChild(onePiece, partNum - 1);
		}
		if(oneOrder > order)
		{
			m_batchNode->reorderChild(onePiece, oneOrder - 1);
		}
	}
	/*
	for(int i = 0; i < (int)m_batchNode->getChildrenCount(); i++)
	{
		CCSprite* onePiece = (CCSprite*)m_batchNode->getChildByTag(i);
		int oneOrder = onePiece->getZOrder();
		CCLog("tag %d : order %d", i, oneOrder);
	}*/

}

void PieceManager::move(CCTouch* touch)
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
	std::vector<TouchedSprite>::iterator iter;  
    for (iter=m_touchedSprites.begin();iter!=m_touchedSprites.end();iter++)  
    {
		if(touch == iter->m_touch)
		{
			int tag = iter->m_tag;
			CCSprite* piece = (CCSprite*)m_batchNode->getChildByTag(tag);
			if(!piece)
				return;

			CCPoint delta = touch->getDelta();	
			
			/*CCRect rect = piece->boundingBox();
			if(newPos.x < 0 || newPos.x > s.width - rect.getMaxX() + rect.getMinX())
				return;
			if(newPos.y < 0 || newPos.y > s.height - rect.getMaxY() + rect.getMinY())
				return;*/
			
			std::vector<int>* group = getGroupPieces(tag);
			if(group == NULL)
			{
				CCPoint pos = piece->getPosition();
				piece->setPosition(ccp(pos.x + delta.x , pos.y + delta.y));
			}
			else
			{
				std::vector<int>::iterator pieceIter;
				for(pieceIter = group->begin(); pieceIter != group->end(); pieceIter++)
				{
					piece = (CCSprite*)m_batchNode->getChildByTag(*pieceIter);
					CCPoint pos = piece->getPosition();
					piece->setPosition(ccp(pos.x + delta.x , pos.y + delta.y));//ÍÏ¶¯¾«Áé
				}
			}
		}
	}
}

void PieceManager::endTouch(CCTouch* touch)
{
	std::vector<TouchedSprite>::iterator iter;  
    for (iter=m_touchedSprites.begin();iter!=m_touchedSprites.end();iter++)  
    {
		if(touch == iter->m_touch)
		{	
			int tag = iter->m_tag;
			m_touchedSprites.erase(iter);
			checkPieceMoveEnd(TouchedSprite(touch, tag));
			moveBackToScreen(tag);
			break;
		}
	}
}

bool PieceManager::getRectMoveBackDelta(const CCRect& rect, CCPoint& delta)
{
	delta.x = 0;
	delta.y = 0;
    CCSize s = CCDirector::sharedDirector()->getWinSize();
	
	float midX = rect.getMidX();
	float midY = rect.getMidY();
	bool b = false;
	if(midX < 0)
	{
		delta.x = -midX;
		b = true;
	}
	else if(midX > s.width)
	{
		delta.x = s.width - midX;
		b = true;
	}
	if(midY < 0)
	{
		delta.y = -midY;
		b = true;
	}
	else if(midY > s.height)
	{
		delta.y = s.height - midY;
		b = true;
	}

	return b;
}

void PieceManager::moveBackToScreen(int tag)
{
	CCSprite* piece = (CCSprite*)m_batchNode->getChildByTag(tag);
	CCRect rect = piece->boundingBox();
	CCPoint delta;
	if(!getRectMoveBackDelta(rect, delta))
		return;
	
	std::vector<int>* pieces = getGroupPieces(tag);
	if(pieces == NULL)
	{
		CCActionInterval* actionTo = CCMoveBy::create(0.3f, delta);
		piece->runAction(actionTo);
	}
	else
	{
		std::vector<int>::iterator pieceIter;
		for (pieceIter=pieces->begin();pieceIter!=pieces->end();pieceIter++)  
		{
			piece = (CCSprite*)m_batchNode->getChildByTag(*pieceIter);
			CCActionInterval* actionTo = CCMoveBy::create(0.3f, delta);
			piece->runAction(actionTo);
		}
	}
}

void PieceManager::checkPieceMoveEnd(TouchedSprite ts)
{
	int tag = ts.m_tag;
	CCSprite* piece = (CCSprite*)m_batchNode->getChildByTag(tag);
	if(!piece)
		return;
	
	std::vector<int>* pieces = getGroupPieces(tag);
	if(!pieces)
	{
		if(checkOnePieceRound(tag))
			JigsawSound::playMerge();
	}
	else
	{
		std::vector<int>::iterator pieceIter;
		for (pieceIter=pieces->begin();pieceIter!=pieces->end();pieceIter++)  
		{
			if(checkOnePieceRound(*pieceIter))
			{
				JigsawSound::playMerge();
				break;//merge one time once...
				pieces = getGroupPieces(tag);
				pieceIter = pieces->begin();
			}
		}
	}
}

bool PieceManager::checkOnePieceRound(int tag)
{
	bool b = false;
	b |= check(tag, MERGE_TO_LEFT);
	if(b) return b;
	b |= check(tag, MERGE_TO_RIGHT);
	if(b) return b;
	b |= check(tag, MERGE_TO_UP);
	if(b) return b;
	b |= check(tag, MERGE_TO_DOWN);
	if(b) return b;
	return b;
}

bool PieceManager::check(int tag, MERGE_ORIENT orient)
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
	int row = tag / m_col;
	int col = tag - row * m_col;
	int targetTag = 0;
	switch(orient)
	{
		case MERGE_TO_LEFT:
		{
			if(col == 0)
				return false;
			targetTag = tag - 1;
			break;
		}
		case MERGE_TO_RIGHT:
		{
			if(col == m_col - 1)
				return false;
			targetTag = tag + 1;
			break;
		}
		case MERGE_TO_UP:
		{
			if(row == 0)
				return false;
			targetTag = tag - m_col;
			break;
		}
		case MERGE_TO_DOWN:
		{
			if(row == m_row - 1)
				return false;
			targetTag = tag + m_col;
			break;
		}
		default:
			break;
	}
	std::vector<int>* touchPieceGroup = getGroupPieces(tag);
	std::vector<int>* pieceGroup = getGroupPieces(targetTag);
	if(pieceGroup != NULL && pieceGroup == touchPieceGroup)
		return false;
	
	CCSprite* touchPiece = (CCSprite*)m_batchNode->getChildByTag(tag);
	CCSprite* piece = (CCSprite*)m_batchNode->getChildByTag(targetTag);

	float height = s.height / 4 * 3 / m_row;
	float width = s.width / 4 * 3 / m_col;
	float x1_x2 = 0;
	float y1_y2 = 0;
	float dx = 0;
	float dy = 0;
	switch(orient)
	{
		case MERGE_TO_LEFT:
		{
			y1_y2 = touchPiece->boundingBox().getMinY() - piece->boundingBox().getMinY();
			x1_x2 = touchPiece->boundingBox().getMinX() - piece->boundingBox().getMaxX();
			dx = width;
			break;
		}
		case MERGE_TO_RIGHT:
		{
			y1_y2 = touchPiece->boundingBox().getMinY() - piece->boundingBox().getMinY();
			x1_x2 = touchPiece->boundingBox().getMaxX() - piece->boundingBox().getMinX();
			dx = -width;
			break;
		}
		case MERGE_TO_UP:
		{
			y1_y2 = touchPiece->boundingBox().getMaxY() - piece->boundingBox().getMinY();
			x1_x2 = touchPiece->boundingBox().getMinX() - piece->boundingBox().getMinX();
			dy = -height;
			break;
		}
		case MERGE_TO_DOWN:
		{
			y1_y2 = touchPiece->boundingBox().getMinY() - piece->boundingBox().getMaxY();
			x1_x2 = touchPiece->boundingBox().getMinX() - piece->boundingBox().getMinX();
			dy = +height;
			break;
		}
		default:
			break;
	}

	if(abs(y1_y2) < height / 2 && abs(x1_x2) < width / 2)
	{
		touchPiece->stopAllActions();
		CCArray* actionArray = CCArray::create();
		if(touchPieceGroup == NULL)
		{
			touchPiece->setRotation(0.0);
		}
		if(pieceGroup == NULL)
		{
			//piece->setRotation(0.0);			
			CCActionInterval* actionTo = CCRotateTo::create(0.3f, 0.0f);
			piece->runAction(actionTo);
		}
		
		CCPoint pos = piece->getPosition();
		CCPoint touchPiecePos = touchPiece->getPosition();
		CCPoint delta = ccp(pos.x + dx - touchPiecePos.x, pos.y + dy - touchPiecePos.y);
		if(touchPieceGroup == NULL)
		{
			//touchPiece->setPosition(ccp(touchPiecePos.x + delta.x, touchPiecePos.y + delta.y));
			CCActionInterval* actionTo = CCMoveTo::create(0.3f, ccp(touchPiecePos.x + delta.x, touchPiecePos.y + delta.y));
			touchPiece->runAction(actionTo);
		}
		else
		{
			std::vector<int>::iterator pieceIter;
			for(pieceIter = touchPieceGroup->begin(); pieceIter != touchPieceGroup->end(); pieceIter++)
			{
				touchPiece = (CCSprite*)m_batchNode->getChildByTag(*pieceIter);
				touchPiecePos = touchPiece->getPosition();
				//touchPiece->setPosition(ccp(touchPiecePos.x + delta.x, touchPiecePos.y + delta.y));
				CCLog("move %d to %d...", *pieceIter, tag - 1);
				CCActionInterval* actionTo = CCMoveTo::create(0.3f, ccp(touchPiecePos.x + delta.x, touchPiecePos.y + delta.y));
				touchPiece->runAction(actionTo);
			}
		}		

		CCParticleFlower* flower = CCParticleFlower::create();
		flower->setPosition(pos.x + dx, pos.y + dy);
		flower->setDuration(0.5);
		m_batchNode->getParent()->addChild(flower, 10);

		mergePiece(tag, targetTag);
		return true;
	}

	return false;
}

///************************
//map opreration...
PieceManager::~PieceManager()
{
	std::map<int, std::vector<int>*>::iterator groupIter;  
    for (groupIter=m_pieceGroups.begin();groupIter!=m_pieceGroups.end();groupIter++)  
    {
		delete groupIter->second;
		groupIter->second = NULL;
	}
}

int PieceManager::getPartCount()
{
	int groupPieceNum = m_pieceGroups.size();
	if(groupPieceNum == 0)
		return m_row * m_col;
	
	int groupNum = 0;
	std::set<int> recorder;
	std::map<int, std::vector<int>*>::iterator groupIter;
	for(groupIter = m_pieceGroups.begin(); groupIter != m_pieceGroups.end(); groupIter++)
	{
		if(recorder.find(groupIter->first) != recorder.end())
			continue;
		std::vector<int>* group = groupIter->second;
		std::vector<int>::iterator pieceIter;
		for(pieceIter = group->begin(); pieceIter != group->end(); pieceIter++)
		{
			recorder.insert(*pieceIter);
		}
		groupNum++;
	}
	return m_row * m_col - groupPieceNum + groupNum;
}

std::vector<int>* PieceManager::getGroupPieces(int tag)
{
	std::map<int, std::vector<int>*>::iterator groupIter;  
	groupIter = m_pieceGroups.find(tag);
	if(groupIter!=m_pieceGroups.end())
		return groupIter->second;
	return NULL;
}

void PieceManager::mergePiece(int touchTag, int targetTag)
{
	CCLog("mergePiece %d %d...", touchTag, targetTag);
	std::vector<int>* touchPieceGroup = getGroupPieces(touchTag);
	std::vector<int>* pieceGroup = getGroupPieces(targetTag);
	
	if(touchPieceGroup == NULL && pieceGroup == NULL)
	{
		std::vector<int>* group = new std::vector<int>;
		group->push_back(touchTag);
		group->push_back(targetTag);
		m_pieceGroups.insert(std::pair<int, std::vector<int>*>(touchTag, group));
		m_pieceGroups.insert(std::pair<int, std::vector<int>*>(targetTag, group));
		setMergePieceSameOrder(targetTag, touchTag);
	}
	else if(touchPieceGroup == NULL /*&& pieceGroup != NULL*/)
	{
		pieceGroup->push_back(touchTag);
		m_pieceGroups.insert(std::pair<int, std::vector<int>*>(touchTag, pieceGroup));
		
		std::vector<int>::iterator pieceIter;
		for (pieceIter=pieceGroup->begin();pieceIter!=pieceGroup->end();pieceIter++)  
		{
			setMergePieceSameOrder(*pieceIter, touchTag);
		}
	}
	else if(pieceGroup == NULL /*&& touchPieceGroup != NULL*/)
	{
		touchPieceGroup->push_back(targetTag);
		m_pieceGroups.insert(std::pair<int, std::vector<int>*>(targetTag, touchPieceGroup));
			setMergePieceSameOrder(targetTag, touchTag);
	}
	else
	{
		std::vector<int>::iterator pieceIter;
		for (pieceIter=touchPieceGroup->begin();pieceIter!=touchPieceGroup->end();pieceIter++)  
		{
			pieceGroup->push_back(*pieceIter);
			m_pieceGroups[*pieceIter] = pieceGroup;
			setMergePieceSameOrder(*pieceIter, touchTag);
		}
		touchPieceGroup->clear();
		delete touchPieceGroup;
	}
	
	pieceGroup = getGroupPieces(targetTag);
	if(pieceGroup->size() == m_row * m_col)
	{
		JigsawSound::playFinish();
		m_finish = true;
	}
	return;
}
//map opreration...
///************************
