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
        virtual void ApplyPhysics(TNode &node) override;
    };

    class TTopPipe final: public TPipe {
    public:
        TTopPipe(cocos2d::Size windowSize);
    private:
        TNode InitNode(const cocos2d::Vec2& position) override final;
    };

    class TBottomPipe final: public TPipe {
    public:
        TBottomPipe(cocos2d::Size windowSize);
    private:
        TNode InitNode(const cocos2d::Vec2& position) override final;
    };

    class TTarget final: public TPipe {
    public:
        TTarget(cocos2d::Size windowSize);
    private:
        TNode InitNode(const cocos2d::Vec2& position) override final;
        void ApplyPhysics(TNode& node) override final;
    };
}
