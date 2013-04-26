#include "MySound.h"

void JigsawSound::loadSounds()
{
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("backgound1.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("sound1.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("sound2.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("sound3.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("sound4.mp3");
}

void JigsawSound::playBackGround()
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("backgound1.mp3", true);
}

void JigsawSound::playTouch()
{
	//SimpleAudioEngine::sharedEngine()->playEffect("sound1.mp3");
}

void JigsawSound::playMerge()
{
	SimpleAudioEngine::sharedEngine()->playEffect("sound4.mp3");
}

void JigsawSound::playFinish()
{
	SimpleAudioEngine::sharedEngine()->playEffect("sound2.mp3");
}

void JigsawSound::stopAll()
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->stopAllEffects();
}

void JigsawSound::pauseMusic()
{
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void JigsawSound::resumeMusic()
{
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
