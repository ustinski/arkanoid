#include "box.h"
#include "physics.h"
#include "gameobjects.h"
#include "arkanoid.h"
#include "sdlmixer.h"

Box::Box(double x, double y, QOpenGLTexture *shadow) :
    Mesh(x, y, shadow)
{
    double s = Physics::scale();
    _body = create(x / s, y / s, width() / 2 / s, height() / 2 / s, Physics::world());
    _body->SetUserData(this);
    reset();

    initVertices();
}

b2Body *Box::create(double x, double y, double hWidth, double hHeight, b2World *world)
{
    b2BodyDef bodyDef;
    bodyDef.position.Set(x, y);

    b2PolygonShape box;
    box.SetAsBox(hWidth, hHeight);

    b2Body *body = world->CreateBody(&bodyDef);
    body->CreateFixture(&box, 0);

    return body;
}

void Box::draw(Element element) { if(_exists) Mesh::draw(element); }

void Box::update()
{
    if(!_contact) return;
    SdlMixer::pop().play();
    _exists = false;
    _body->SetActive(false);
    Arkanoid::addScore();

    _contact = false;
}

void Box::reset()
{
    _texture = GameObjects::boxTexture();
    _exists = true;
    _body->SetActive(true);
}

bool Box::exists() { return _exists; }
int Box::width() { return 100; }
int Box::height() { return 50; }
