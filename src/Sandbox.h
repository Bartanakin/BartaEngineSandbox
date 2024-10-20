#pragma once
#include "Constants.h"
#include <Application.h>
#include <Predefines.h>

class Sandbox
    : public Barta::Application<Barta::DefaultCollisionLogger, Barta::CollisionEventsLogger,
                                Barta::ListManager, Barta::CollisionCoreExecutor> {
public:
  Sandbox();
  Sandbox(const Sandbox &) = delete;
  Sandbox(Sandbox &&) = delete;
  Sandbox &operator=(const Sandbox &) = delete;
  ~Sandbox() noexcept;

private:
  static std::unique_ptr<Barta::TimerInterface> gameTimer;
};
