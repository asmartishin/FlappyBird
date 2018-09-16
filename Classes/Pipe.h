#pragma once

#include "cocos2d.h"

#include "Physics.h"

namespace NFlappyBird {
    class TPipe: public TPhysics {
    public:
        TPipe(cocos2d::Size windowSize);
        virtual ~TPipe() = default;
    protected:
        const float GapWidth;
        const float GapHeight;
        virtual void applyPhysics(TNode& node) override;
    };

    class TTopPipe: public TPipe {
    public:
        TTopPipe(cocos2d::Size windowSize);
    private:
        TNode InitNode(const cocos2d::Vec2& position) override final;
    };

    class TBottomPipe: public TPipe {
    public:
        TBottomPipe(cocos2d::Size windowSize);
    private:
        TNode InitNode(const cocos2d::Vec2& position) override final;
    };

    class TTarget: public TPipe {
    public:
        TTarget(cocos2d::Size windowSize);
    private:
        TNode InitNode(const cocos2d::Vec2& position) override final;
        void applyPhysics(TNode& node) override final;
    };
}
