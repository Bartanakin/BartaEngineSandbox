#include "Sandbox.h"

int main() {
    auto app = new Sandbox();
    app->run();
    delete app;

    return 0;
}