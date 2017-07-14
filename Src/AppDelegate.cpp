// Copyright (c) 2012-2017 Volodymyr Syvochka
#include "AppDelegate.h"

using namespace RioEngine;
#include "SimpleAudioEngine.h"
using namespace Audio;

static RioEngine::Size designResolutionSize = RioEngine::Size(480, 320);
static RioEngine::Size smallResolutionSize = RioEngine::Size(480, 320);
static RioEngine::Size mediumResolutionSize = RioEngine::Size(1024, 768);
static RioEngine::Size largeResolutionSize = RioEngine::Size(2048, 1536);

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
	// to close correctly audioEngine
	SimpleAudioEngine::end();
}

void AppDelegate::initGLContextAttrs()
{
	//set OpenGL context attributions,now can only set six attributions:
	//red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
	designResolutionSize = mediumResolutionSize;
	
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();

	if (glview == nullptr)
	{
#if (RIO_TARGET_PLATFORM == RIO_PLATFORM_WIN32) || (RIO_TARGET_PLATFORM == RIO_PLATFORM_MAC) || (RIO_TARGET_PLATFORM == RIO_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("Realm Chronicles", RioEngine::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("RealmChronicles");
#endif
        director->setOpenGLView(glview);
    }

	director->setDisplayStats(false);
	director->setAnimationInterval(1.0f / 60.0f);
	director->setDepthTest(false);
	
	// Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }

	return true;
}

void AppDelegate::applicationDidEnterBackground()
{
	Director::getInstance()->pause();
	Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground()
{
	Director::getInstance()->resume();
	Director::getInstance()->startAnimation();
}
// Copyright (c) 2012-2017 Volodymyr Syvochka