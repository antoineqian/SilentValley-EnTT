#include "systems/Engine.hpp"
int main()
{
    auto engine = Engine::create();
    engine->activate();
    return 0;
}
