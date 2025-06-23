#pragma once
#include <Objects/CollisionSubscribers/RigidObjectCollisionSubscriber.h>

class TestSubscriber: public Barta::Subscribers::RigidObjectRigidObject {
public:
    bool handle(Barta::Events::RigidObjectRigidObject &event) override;

    bool isToBeDeleted() const noexcept override;

private:
    
};
