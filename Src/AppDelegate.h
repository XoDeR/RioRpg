// Copyright (c) 2012-2017 Volodymyr Syvochka
#pragma once

#include "RioEngine.h"

class AppDelegate : private RioEngine::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();
	
	virtual void initGLContextAttrs();
    virtual bool applicationDidFinishLaunching();
    virtual void applicationDidEnterBackground();
    virtual void applicationWillEnterForeground();
};
// Copyright (c) 2012-2017 Volodymyr Syvochka

