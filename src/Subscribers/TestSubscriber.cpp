//
// Created by bartanakin on 10/27/24.
//

#include "TestSubscriber.h"
bool TestSubscriber::handle(Barta::Events::RigidObjectRigidObject &event) {
    std::cout << "Collision !" << std::endl;

    return true;
}

bool TestSubscriber::isToBeDeleted() const noexcept { return true; }