#include "Sandbox.h"
#include "Collisions/CollisionDetectionStrategies/DynamicCollisionDetectionStrategy.h"
#include "Dynamics/ConstVelocityDynamicsUpdateStrategy.h"
#if USE_SFML
#include "Graphics/SFML_GraphicsBridge.h"
#endif

#include "Hitbox/OBB_Hitbox.h"
#include "Subscribers/TestSubscriber.h"

#include "SceneLoader/ObjectJsonDecoder.h"
#include "SceneLoader/ObjectJsonDecoderManager.h"
#include "SceneLoader/RootJsonDecoder.h"
#include <Collisions/CollisionDetectionStrategies/StaticCollisionDetectionStrategy.h>
#include <Collisions/CollisionLogger.h>
#include <Dynamics/Timers/FrameLimitTimerProxy.h>
#include <Events/Subscribers/CollisionResponseSubscriber.h>
#include <Graphics/SpriteBuilder/SpriteMerger.h>
#include <Hitbox/CircleHitbox.h>
#include <Objects/Rigid/RigidCompositeObject.h>
#include <Objects/Rigid/RigidObject.h>
#include <Objects/SimpleObject.h>

// Very important to include this file! There are template specialisation
// definitions.
#include "Events/Subscribers/CollisionBrakeSubscriber.h"
#if USE_OPEN_GL
#include "Graphics/OpenGL_Bridge.h"
#endif

#include "Dynamics/Timers/BartaTimer.h"

#include <Predefines.h>

std::unique_ptr<Barta::TimerInterface> Sandbox::gameTimer =
    std::make_unique<Barta::FrameLimitTimerProxy>(
        std::make_unique<Barta::Dynamics::Timers::BartaTimer>(), 0.0f);

Sandbox::Sandbox()
    : Application("Sandbox", std::make_unique<Barta::SFML_GraphicsBridge>(), // requires SFML
    // : Application("Sandbox", std::make_unique<Barta::Graphics::OpenGL_Bridge::OpenGL_Bridge>(), // requires OpenGL
                  *Sandbox::gameTimer, nullptr,
                  // std::make_unique<Barta::DynamicCollisionDetectionStrategy>(
                  //     *Sandbox::gameTimer))
                  std::make_unique<Barta::StaticCollisionDetectionStrategy>()) {
  this->dynamicsUpdateStrategy =
      std::make_unique<Barta::ConstVelocityDynamicsUpdateStrategy<
          Barta::DynamicsAwareInterface::DynamicsAwareList>>(
          this->objectManager->getDynamicsList());
  // json decoder configuration
  auto jsonDecoder = Barta::SceneLoader::RootJsonDecoder<
      Barta::SceneLoader::ObjectJsonDecoderManager<Barta::RigidObjectInterface>,
      Barta::ListManager>(this->objectLists, *this->objectManager);

  // scene file
  std::fstream sceneFile("scenes/scene.json");
  jsonDecoder.decode(json::parse(sceneFile));

  this->collisionEventsLogger.logSubscriber(std::make_shared<TestSubscriber>());
  // collisions
  this->collisionEventsLogger.logSubscriber(
      std::make_unique<Barta::CollisionBrakeSubscriber<
          Barta::RigidObjectInterface, Barta::RigidObjectInterface>>());
  this->collisionEventsLogger.logSubscriber(
      std::make_unique<Barta::StaticCollisionResponseSubscriberType<
          Barta::RigidObjectInterface, Barta::RigidObjectInterface>>());
}

Sandbox::~Sandbox() {}
