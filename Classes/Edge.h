#pragma once

#include "cocos2d.h"

#include "Physics.h"
#include "Const.h"

namespace NFlappyBird {
    class TEdge final: public TPhysics {
    public:
        TEdge(cocos2d::Size windowSize);
    private:
        TNode InitNode(const cocos2d::Vec2& position) override final;
        void applyPhysics(TNode &node) override final;
    };
};