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

// Very important to include this file! There are template specialisation definitions.
#include <Predefines.h>

std::unique_ptr<Barta::TimerInterface> Sandbox::gameTimer =
    std::make_unique<Barta::FrameLimitTimerProxy>(
        std::make_unique<Barta::SFML_Timer>(), 0.0f);

Sandbox::Sandbox()
    : Application(
          "Sandbox", std::make_unique<Barta::SFML_GraphicsBridge>(),
          *Sandbox::gameTimer, nullptr,
          std::make_unique<Barta::DynamicCollisionDetectionStrategy>(
              *Sandbox::gameTimer))
// std::make_unique<Barta::StaticCollisionDetectionStrategy>())
{
  this->dynamicsUpdateStrategy =
      std::make_unique<Barta::ConstVelocityDynamicsUpdateStrategy<
          Barta::DynamicsAwareInterface::DynamicsAwareList>>(
          this->objectManager->getDynamicsList());
  auto repository =
      Barta::RigidObjectRepository(this->objectLists, *this->objectManager);

  auto ball1 = repository.addNewCircle(20.f, {255, 0, 255, 255});
  ball1->move({320.f, 400.f});
  ball1->getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT].velocity = {
      0.f, -60.f};

  //    auto ball2 = repository.addNewCircle(20.f, {255, 255, 0, 255});
  //    ball2->move({360.f, 150.f});
  //    ball2->getDynamicsDTO().velocity = {50.f, 60.f};
  //
  // auto ball3 = repository.addNewCircle(40.f, {0, 255, 255, 255});
  // ball3->move({370.f, 450.f});
  // ball3->getDynamicsDTO().velocity = {-40.f, 60.f};
  //
  //    auto block1 = repository.addNewAABB({80.f, 80.f}, {255, 0, 0, 255});
  //    block1->move({310.f, 310.f});

  auto boundColor = Barta::Color(50, 191, 66, 255);
  auto leftBound = repository.addNewAABB({50.f, 650.f}, boundColor);
  leftBound->move({0.f, 0.f});
  auto topBound = repository.addNewAABB({650.f, 50.f}, boundColor);
  topBound->move({50.f, 0.f});
  auto rightBound = repository.addNewAABB({50.f, 650.f}, boundColor);
  rightBound->move({650.f, 50.f});
  auto bottomBound = repository.addNewAABB({650.f, 50.f}, boundColor);
  bottomBound->move({0.f, 650.f});

  //    auto circle1 = new Barta::SimpleObject(
  //        Barta::SFML_GraphicsBridge::createNewTransformableInstance()
  //    );
  //    this->objectManager->addNewObject(circle1);
  auto merger = Barta::SpriteMerger();
  merger.addCircleSprite(Barta::CircleSprite(
      Barta::Circle(40.f, Barta::Vector2f(40.f, 40.f)), {255, 255, 0, 255}));
  auto circle1 = new Barta::RigidObject(
      {Barta::SFML_GraphicsBridge::createNewTransformableInstance(),
       merger.merge(false), 4},
      std::unique_ptr<Barta::HitboxInterface>(
          new Barta::CircleHitbox({40.f, {40.f, 40.f}})),
      {{0., 0.}, false, 1.f});
  circle1->move({60.f, 60.f});

  merger.addCircleSprite(Barta::CircleSprite(
      Barta::Circle(40.f, Barta::Vector2f(40.f, 40.f)), {255, 255, 0, 255}));

  auto circle2 = new Barta::RigidObject(
      {Barta::SFML_GraphicsBridge::createNewTransformableInstance(),
       merger.merge(false), 4},
      std::unique_ptr<Barta::HitboxInterface>(
          new Barta::CircleHitbox({40.f, {40.f, 40.f}})),
      {{0., 0.}, false, 1.f});
  circle2->move({140.f, 60.f});

  auto circles = new Barta::RigidCompositeObject(
      Barta::SFML_GraphicsBridge::createNewTransformableInstance(),
      {{0., 80.}, false, 1.f}, {circle1, circle2});

  this->objectLists.addObject(circles);
  this->objectManager->addGraphicsObject(circles);
  this->objectManager->addDynamicsObject(circles);
  this->objectManager->addNewObject(circles);

  this->collisionEventsLogger.logSubscriber(
      std::make_unique<Barta::StaticCollisionResponseSubscriberType<
          Barta::RigidObjectInterface, Barta::RigidObjectInterface>>());

  // float c = 0; // 1.7f;
  // auto v1 = Barta::Vector2f(50., 10.);
  // auto yellow = Barta::Color(255, 255, 0);
  // float angle = M_PI / 6.f;
  // merger.addTriangle(
  //     Barta::TriangleSprite({{},
  //                            Barta::Vector2f(100.f, 50.f).rotated(angle),
  //                            Barta::Vector2f(100.f, 0.f).rotated(angle)},
  //                           yellow, yellow, yellow));
  // merger.addTriangle(
  //     Barta::TriangleSprite({{},
  //                            Barta::Vector2f(0.f, 50.f).rotated(angle),
  //                            Barta::Vector2f(100.f, 50.f).rotated(angle)},
  //                           yellow, yellow, yellow));
  // auto rect1 = new Barta::RigidObject(
  //     {Barta::SFML_GraphicsBridge::createNewTransformableInstance(),
  //      merger.merge(false), 4},
  //     std::unique_ptr<Barta::HitboxInterface>(
  //         new Barta::OBB_Hitbox({{}, {100.f, 50.f}, angle})),
  //     {v1, false, 1.f});
  // rect1->move(Barta::Vector2f(100.f, 100.f) + c * v1);
  //
  // this->objectLists.addObject(rect1);
  // this->objectManager->addGraphicsObject(
  //     static_cast<Barta::GraphicsDataAwareInterface *>(rect1));
  // this->objectManager->addDynamicsObject(
  //     static_cast<Barta::DynamicsAwareInterface *>(rect1));
  // this->objectManager->addNewObject(
  //     static_cast<Barta::BartaObjectInterface *>(rect1));

  //   auto v2 = Barta::Vector2f(-30., -20.);
  // auto blue = Barta::Color(0, 0, 255);
  // float angle2 = 2 * M_PI / 5.f;
  // merger.addTriangle(
  //     Barta::TriangleSprite({{},
  //                            Barta::Vector2f(60.f, 70.f).rotated(angle2),
  //                            Barta::Vector2f(60.f, 0.f).rotated(angle2)},
  //                           blue, blue, blue));
  // merger.addTriangle(
  //     Barta::TriangleSprite({{},
  //                            Barta::Vector2f(0.f, 70.f).rotated(angle2),
  //                            Barta::Vector2f(60.f, 70.f).rotated(angle2)},
  //                           blue, blue, blue));
  // auto rect2 = new Barta::RigidObject(
  //     {Barta::SFML_GraphicsBridge::createNewTransformableInstance(),
  //      merger.merge(false), 4},
  //     std::unique_ptr<Barta::HitboxInterface>(
  //         new Barta::OBB_Hitbox({{}, {60.f, 70.f}, angle2})),
  //     {v2, false, 1.f});
  // rect2->move(Barta::Vector2f(380.f, 200.f) + c * v2);
  //
  // this->objectLists.addObject(rect2);
  // this->objectManager->addGraphicsObject(
  //     static_cast<Barta::GraphicsDataAwareInterface *>(rect2));
  // this->objectManager->addDynamicsObject(
  //     static_cast<Barta::DynamicsAwareInterface *>(rect2));
  // this->objectManager->addNewObject(
  //     static_cast<Barta::BartaObjectInterface *>(rect2));

  this->collisionEventsLogger.logSubscriber(std::make_shared<TestSubscriber>());
  this->collisionEventsLogger.logSubscriber(
      std::make_unique<Barta::StaticCollisionResponseSubscriberType<
          Barta::RigidObjectInterface, Barta::RigidObjectInterface>>());
}

Sandbox::~Sandbox() {}
