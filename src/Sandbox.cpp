#include "Sandbox.h"
#include "Collisions/CollisionDetectionStrategies/DynamicCollisionDetectionStrategy.h"
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
#include <Graphics/OpenGL_Bridge.h>
#endif

#include "Dynamics/Mass/ConstantPointMassDistributionCalculator.h"
#include "Dynamics/SoftBody/StVenantKirchhoffDynamics.h"
#include "Dynamics/Timers/BartaTimer.h"
#include "Events/Subscribers/CameraTransformationSubscriber.h"
#include <Predefines.h>

std::unique_ptr<Barta::TimerInterface> Sandbox::gameTimer =
    std::make_unique<Barta::FrameLimitTimerProxy>(
        std::make_unique<Barta::Dynamics::Timers::BartaTimer>(), 0.0f);

Sandbox::Sandbox()
    // : Application("Sandbox", std::make_unique<Barta::SFML_GraphicsBridge>(), // requires SFML
    : Application("Sandbox", std::make_unique<Barta::Graphics::OpenGL_Bridge::OpenGL_Bridge>(), // requires OpenGL
                  *Sandbox::gameTimer,
                  // std::make_unique<Barta::DynamicCollisionDetectionStrategy>(
                  //     *Sandbox::gameTimer))
                  std::make_unique<Barta::StaticCollisionDetectionStrategy>(),
            Barta::PredefinedUpdateStrategyManager(Barta::Dynamics::UpdateStrategy::ExplicitEulerStrategy(), Barta::Dynamics::UpdateStrategy::SoftBodyStrategy(
                std::make_unique<Barta::Dynamics::SoftBody::StVenantKirchhoffDynamics>(),
                std::make_unique<Barta::Dynamics::Mass::ConstantPointMassDistributionCalculator>()
            ))) {
  // json decoder configuration
  auto jsonDecoder = Barta::SceneLoader::RootJsonDecoder<
      Barta::SceneLoader::ObjectJsonDecoderManager<Barta::RigidObjectInterface, Barta::Objects::Soft::SoftObject>,
      Barta::ListManager, Barta::BartaEventLoggerInterface>(this->objectLists, *this->objectManager, *this->eventLogger);

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


    this->eventLogger->logSubscriber(std::make_unique<Barta::Events::Subscribers::CameraTransformationSubscriber>(*this->graphicsBridge));
}

Sandbox::~Sandbox() {}
