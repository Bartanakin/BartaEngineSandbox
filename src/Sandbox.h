#pragma once
#include "Constants.h"
#include "Dynamics/Mass/ConstantPointMassDistributionCalculator.h"
#include "Dynamics/SoftBody/StVenantKirchhoffDynamics.h"

#include <Application.h>
#include <Predefines.h>

class Sandbox
    : public Barta::Application<Barta::DefaultCollisionLogger, Barta::CollisionEventsLogger,
                                Barta::ListManager, Barta::CollisionCoreExecutor, Barta::PredefinedUpdateStrategyManager> {
public:
  Sandbox();
  Sandbox(const Sandbox &) = delete;
  Sandbox(Sandbox &&) = delete;
  Sandbox &operator=(const Sandbox &) = delete;
  ~Sandbox() noexcept;

private:
  static std::unique_ptr<Barta::TimerInterface> gameTimer;
  Barta::Dynamics::Mass::ConstantPointMassDistributionCalculator massCalculator;
  Barta::Dynamics::SoftBody::StVenantKirchhoffDynamics softDynamics;
};
