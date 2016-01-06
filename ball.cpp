#include "ball.h"
#include "arkanoid.h"
#include "window.h"

#include <iostream>

Ball::Ball() :
    Mesh("ball", "ballShadow"),
    line(new EMesh("ballLine")),
    radius(25)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    _body = Physics::world()->CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    {
        b2CircleShape *circleShape = new b2CircleShape;
        circleShape->m_p.Set(0, 0);
        circleShape->m_radius = radius / Physics::scale();
        fixtureDef.shape = circleShape;
    }
    fixtureDef.density = 1;
    fixtureDef.friction = 1;
    fixtureDef.restitution = 1;
    _body->CreateFixture(&fixtureDef);

    _body->SetUserData(this);
}

void Ball::draw(Element element)
{
    Mesh::draw(element);
    line->draw();
}

void Ball::update()
{
    const b2Vec2 &position = _body->GetPosition();

    setPosition(Physics::scale() * position);
    line->setAngle(_body->GetAngle());

    if(_position.y() + radius < -Window::height() / 2)
        Arkanoid::startNewGame();
}

void Ball::push(const QVector2D &dV)
{ _body->SetLinearVelocity(_body->GetLinearVelocity() + b2Vec2(dV.x(), dV.y())); }

void Ball::pushAngular(double dw)
{ _body->SetAngularVelocity(_body->GetAngularVelocity() + dw); }

void Ball::setPosition(double x, double y)
{
    Mesh::setPosition(x, y);
    line->setPosition(x, y);
}

void Ball::setPosition(const b2Vec2 &position)
{ setPosition(position.x, position.y); }

void Ball::setPhysPosition(double x, double y)
{
    setPosition(x, y);
    _body->SetTransform(1 / Physics::scale() * b2Vec2(x, y), _body->GetAngle());
}

void Ball::reset()
{
    _body->SetLinearVelocity(b2Vec2(0, 0));
    _body->SetAngularVelocity(0);
}

int Ball::getRadius() { return radius; }
