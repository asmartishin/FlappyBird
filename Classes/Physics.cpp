#include "Physics.h"

using namespace cocos2d;

namespace NFlappyBird {
    TPhysics::TPhysics(Size windowSize)
        : WindowSize(windowSize)
    {
    }

    Node* TPhysics::Spawn(const Vec2& position) {
        auto node = InitNode(position);
        applyPhysics(node);

        return node.Get();
    }
}