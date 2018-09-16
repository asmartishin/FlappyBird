#pragma once

#include <memory>

#include "cocos2d.h"

#include "Const.h"

namespace NFlappyBird {
    enum class EPhysicsCategory {
        None = 0,
        Bird = (1 << 0),
        Obstacle = (1 << 1),
        Target = (1 << 2),
        All =  EPhysicsCategory::Obstacle | EPhysicsCategory::Target
    };

    struct TNode{
        cocos2d::Node* NodePtr;
        const cocos2d::Size Size_;

        TNode(cocos2d::Node* node, cocos2d::Size size)
            : NodePtr(node)
            , Size_(size)
        {
        }

        const cocos2d::Size Size() const noexcept {
            return Size_;
        }

        cocos2d::Node* Get() const {
            return NodePtr;
        }

        cocos2d::Node* operator->() const {
            return NodePtr;
        }
    };

    class IPhysics {
    public:
        virtual ~IPhysics() = default;
        virtual cocos2d::Node* Spawn(const cocos2d::Vec2& position) = 0;
    protected:
        virtual TNode InitNode(const cocos2d::Vec2& position) = 0;
        virtual void applyPhysics(TNode& node) = 0;
    };

    class TPhysics: public IPhysics {
    public:
        TPhysics(cocos2d::Size windowSize);
        virtual ~TPhysics() = default;
        cocos2d::Node* Spawn(const cocos2d::Vec2& position);
    protected:
        cocos2d::Size WindowSize;
    };
}
