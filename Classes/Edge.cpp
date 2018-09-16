#include "Edge.h"

using namespace cocos2d;

namespace NFlappyBird {
    TEdge::TEdge(Size windowSize)
        : TPhysics(windowSize)
    {
    }

    TNode TEdge::InitNode(const Vec2& position) {
        TNode node(Node::create(), WindowSize);

        node->setPosition({position.x, position.y});

        return node;
    }

    void TEdge::ApplyPhysics(TNode &node) {
        auto physicsBody = PhysicsBody::createEdgeBox(WindowSize);

        physicsBody->setDynamic(false);
        physicsBody->setCategoryBitmask(static_cast<int>(EPhysicsCategory::Obstacle));
        physicsBody->setContactTestBitmask(static_cast<int>(EPhysicsCategory::Bird));

        node->setPhysicsBody(physicsBody);
    }
}
