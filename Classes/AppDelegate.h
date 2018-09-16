#pragma  once

#include "cocos2d.h"
#include "BoxPhysicsGameScene.h"

class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    bool applicationDidFinishLaunching() override final;

    void applicationDidEnterBackground() override final;

    void applicationWillEnterForeground() override final;
};
