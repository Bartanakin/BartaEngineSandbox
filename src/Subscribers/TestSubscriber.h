//
// Created by bartanakin on 10/27/24.
//

#pragma once
#include <Objects/Rigid/RigidObjectCollisionSubscriber.h>

class TestSubscriber: public Barta::Subscribers::RigidObjectRigidObject {
public:
    bool handle(Barta::Events::RigidObjectRigidObject &event) override;

    bool isToBeDeleted() const noexcept override;

private:
    
};
