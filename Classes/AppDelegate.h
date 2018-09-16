#pragma  once

#include "cocos2d.h"

class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    void initGLContextAttrs() override final;

    bool applicationDidFinishLaunching() override final;

    void applicationDidEnterBackground() override final;

    void applicationWillEnterForeground() override final;
};
