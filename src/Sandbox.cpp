#include "Sandbox.h"
#include "Collisions/CollisionDetectionStrategies/DynamicCollisionDetectionStrategy.h"
#include "Dynamics/ConstVelocityDynamicsUpdateStrategy.h"
#include "Graphics/SFML_GraphicsBridge.h"
#include "Hitbox/OBB_Hitbox.h"
#include "Subscribers/TestSubscriber.h"

#include <Collisions/CollisionDetectionStrategies/StaticCollisionDetectionStrategy.h>
#include <Collisions/CollisionLogger.h>
#include <Dynamics/Timers/FrameLimitTimerProxy.h>
#include <Dynamics/Timers/SFML_Timer.h>
#include <Events/Subscribers/CollisionResponseSubscriber.h>
#include <Graphics/SpriteBuilder/SpriteMerger.h>
#include <Hitbox/CircleHitbox.h>
#include <Objects/Rigid/RigidCompositeObject.h>
#include <Objects/Rigid/RigidObject.h>
#include <Objects/Rigid/RigidObjectRepository.h>
#include <Objects/SimpleObject.h>

// Very important to include this file! There are template specialisation
// definitions.
#include <Predefines.h>

std::unique_ptr<Barta::TimerInterface> Sandbox::gameTimer =
    std::make_unique<Barta::FrameLimitTimerProxy>(
        std::make_unique<Barta::SFML_Timer>(), 0.0f);

Sandbox::Sandbox()
    : Application("Sandbox", std::make_unique<Barta::SFML_GraphicsBridge>(),
                  *Sandbox::gameTimer, nullptr,
                  // std::make_unique<Barta::DynamicCollisionDetectionStrategy>(
                  //     *Sandbox::gameTimer))
std::make_unique<Barta::StaticCollisionDetectionStrategy>())
{
  this->dynamicsUpdateStrategy =
      std::make_unique<Barta::ConstVelocityDynamicsUpdateStrategy<
          Barta::DynamicsAwareInterface::DynamicsAwareList>>(
          this->objectManager->getDynamicsList());
  auto repository =
      Barta::RigidObjectRepository(this->objectLists, *this->objectManager);

  // auto ball1 = repository.addNewCircle(20.f, {255, 0, 255, 255});
  // ball1->move({320.f, 100.f});
  auto box1 = repository.addNewOBB({100.f, 40.}, -M_PI / 6., {255, 100, 0, 255});
  box1->move({400.f,  260.f});
  // box1->getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT].velocity = {
  //     0.f, 60.f};
  auto box = repository.addNewOBB({100.f, 40.}, M_PI / 6., {255, 255, 0, 255});
  box->move({350.f, 250.f});
  // box->getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT].velocity = {
  //     0.f, -60.f};

  // auto boundColor = Barta::Color(50, 191, 66, 255);
  // auto leftBound = repository.addNewAABB({50.f, 650.f}, boundColor);
  // leftBound->move({0.f, 0.f});
  // auto topBound = repository.addNewAABB({650.f, 50.f}, boundColor);
  // topBound->move({50.f, 0.f});
  // auto rightBound = repository.addNewAABB({50.f, 650.f}, boundColor);
  // rightBound->move({650.f, 50.f});
  // auto bottomBound = repository.addNewAABB({650.f, 50.f}, boundColor);
  // bottomBound->move({0.f, 650.f});

  this->collisionEventsLogger.logSubscriber(std::make_shared<TestSubscriber>());
  this->collisionEventsLogger.logSubscriber(
      std::make_unique<Barta::StaticCollisionResponseSubscriberType<
          Barta::RigidObjectInterface, Barta::RigidObjectInterface>>());
}

Sandbox::~Sandbox() {}
