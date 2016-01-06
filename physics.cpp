#include "physics.h"
#include "window.h"
#include "listener.h"
#include "box.h"

namespace Physics
{
    b2World *_world;
    Listener _listener;
    const double sc = 100;
}

void Physics::init()
{
    _world = new b2World(b2Vec2(0, -1));
    _world->SetContactListener(&_listener);


    using namespace Window;
    const int hw = 1;
    Box::create(0, height() / 2 / sc + hw, width() / 2 / sc, hw, _world);
    Box::create(-width() / 2 / sc - hw, 0, hw, height() / 2 / sc, _world);
    Box::create(width() / 2 / sc + hw, 0, hw, height() / 2 / sc, _world);
}

void Physics::update(double dt) { _world->Step(dt, 6, 2); }
b2World *Physics::world() { return _world; }
double Physics::scale() { return sc; }
