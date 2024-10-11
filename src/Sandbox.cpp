#include <Collisions/CollisionLogger.h>
#include "Sandbox.h"
#include "Dynamics/ConstVelocityDynamicsUpdateStrategy.h"
#include "Collisions/CollisionDetectionStrategies/DynamicCollisionDetectionStrategy.h"
#include "Geometrics/Math/BartaMathLibrary.h"
#include "Graphics/SFML_GraphicsBridge.h"
#include <Objects/Rigid/RigidObjectRepository.h>
#include <Objects/Rigid/RigidCompositeObject.h>
#include <Dynamics/Timers/FrameLimitTimerProxy.h>
#include <Dynamics/Timers/SFML_Timer.h>
#include <Graphics/SpriteBuilder/SpriteMerger.h>
#include <Objects/SimpleObject.h>
#include <Hitbox/CircleHitbox.h>

std::unique_ptr<Barta::TimerInterface> Sandbox::gameTimer = std::make_unique<Barta::FrameLimitTimerProxy>(
    std::make_unique<Barta::SFML_Timer>(),
    0.0f
);

Sandbox::Sandbox()
	: Application(
        "Sandbox",
		std::make_unique<Barta::SFML_GraphicsBridge>(),
        *Sandbox::gameTimer,
		std::make_unique<Barta::ConstVelocityDynamicsUpdateStrategy>(),
		std::make_unique<Barta::DynamicCollisionDetectionStrategy>(
            std::make_unique<Barta::BartaMathLibrary>(),
            *Sandbox::gameTimer
        )
	)
{
    auto repository = Barta::RigidObjectRepository(
        this->objectLists,
        *this->objectManager
    );

    auto ball1 = repository.addNewCircle(20.f, {255, 0, 255, 255});
    ball1->move({120.f, 400.f});
    ball1->getDynamicsDTO().velocity = {0.f, -60.f};

//    auto ball2 = repository.addNewCircle(20.f, {255, 255, 0, 255});
//    ball2->move({360.f, 150.f});
//    ball2->getDynamicsDTO().velocity = {50.f, 60.f};
//
//    auto ball3 = repository.addNewCircle(40.f, {0, 255, 255, 255});
//    ball3->move({370.f, 450.f});
//    ball3->getDynamicsDTO().velocity = {-40.f, 60.f};
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
        Barta::Circle(
            40.f,
            Barta::Vector2f(40.f, 40.f)
        ),
        {255, 255, 0, 255}
    ));
    auto circle1 = new Barta::RigidObject(
        {
            Barta::SFML_GraphicsBridge::createNewTransformableInstance(),
            merger.merge(false),
            4
        },
        std::unique_ptr<Barta::HitboxInterface>(new Barta::CircleHitbox({40.f, {40.f, 40.f}})),
        {{0., 0.}, false, 1.f}
    );
    circle1->move({60.f, 60.f});

    merger.addCircleSprite(Barta::CircleSprite(
        Barta::Circle(
            40.f,
            Barta::Vector2f(40.f, 40.f)
        ),
        {255, 255, 0, 255}
    ));

    auto circle2 = new Barta::RigidObject(
        {
            Barta::SFML_GraphicsBridge::createNewTransformableInstance(),
            merger.merge(false),
            4
        },
        std::unique_ptr<Barta::HitboxInterface>(new Barta::CircleHitbox({40.f, {40.f, 40.f}})),
        {{0., 0.}, false, 1.f}
    );
    circle2->move({140.f, 60.f});

    auto circles = new Barta::RigidCompositeObject(
        Barta::SFML_GraphicsBridge::createNewTransformableInstance(),
        {{0., 80.}, false, 1.f},
        {circle1, circle2}
    );

    this->objectLists.addObject(circles);
    this->objectManager->addGraphicsObject(static_cast<Barta::GraphicsDataAwareInterface*>(circles));
    this->objectManager->addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(circles));
    this->objectManager->addNewObject(static_cast<Barta::BartaObjectInterface*>(circles));
}

Sandbox::~Sandbox() {}
