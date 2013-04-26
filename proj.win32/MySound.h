#ifndef __MYSOUND_H__
#define __MYSOUND_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

class JigsawSound
{
public:
	JigsawSound() {}
public:
	static void loadSounds();
	static void playBackGround();
	static void playTouch();
	static void playMerge();
	static void playFinish();
	static void stopAll();
	static void pauseMusic();
	static void resumeMusic();
};

#endif