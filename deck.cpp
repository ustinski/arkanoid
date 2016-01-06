#include "deck.h"
#include "physics.h"
#include "arkanoid.h"
#include "window.h"
#include "ball.h"
#include "sdlmixer.h"

#include <qmath.h>

#include <iostream>

const int width = 200;
const int height = 50;
const int radius = 175;
const int offset = 10;

Deck::Deck(Ball *ball) :
//Mesh center is in the middle of picture, physical body center is in center of circle
Mesh(0, -Window::height() / 2 + height / 2 + offset, "deck", "deckShadow"),
_ball(ball),
_ballAttached(true)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0, (-Window::height() / 2 + height + offset - radius + 40) / Physics::scale());
    _body = Physics::world()->CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    {
        b2PolygonShape &shape = *new b2PolygonShape;
        //b2BolygonShape should have only 8 vertices
        const int totalVertices = 8;
        b2Vec2 vertices[totalVertices];
        //angle of circle sector with radius 175 and width 200
        double totalAngle = 1.2165;
        //first 7 are on arc, 8th is in center of circle, shape is something like that:
        //     ___
        //    /   \
        //    \   /
        //     \ /
        //      V
        //
        const int arcVertices = totalVertices - 1;
        for (int i = 0; i < arcVertices; i++) {
            double a = totalAngle / 2 - totalAngle * i / (arcVertices - 1);
            vertices[i] = 1 / Physics::scale() * radius * b2Vec2(sin(a), cos(a));
        }
        vertices[7].Set(0, 0);
        shape.Set(vertices, totalVertices);

        fixtureDef.shape = &shape;
    }
    fixtureDef.density = 0.3;
    fixtureDef.friction = 1;
    fixtureDef.restitution = 1;
    _body->CreateFixture(&fixtureDef);

    _body->SetUserData(this);
}

void Deck::update()
{
    const b2Vec2 &p = _body->GetPosition();
    setPosition(p.x * Physics::scale(), -Window::height() / 2 + height / 2 + offset);

    bool l = Window::leftArrowPressed();
    bool r = Window::rightArrowPressed();
    double speed = (l == r ? 0 : (l ? -15 : 15));

    _body->SetLinearVelocity(b2Vec2(speed, 0));
    _body->SetAngularVelocity(0);
    _body->SetTransform(b2Vec2(p.x, (-Window::height() / 2 + height / 2 + offset - radius + 40) / Physics::scale()), 0);

    if (_ballAttached) {
        //+1 is here to prevent collision
        const int hHeight = Window::height() / 2;
        _ball->setPhysPosition(_position.x(), -hHeight + height + offset + _ball->getRadius() + 1);
        return;
    }

    if (!_contact) return;
    SdlMixer::shoot().play();

    Arkanoid::cancelCombo();

    _contact = false;
}

void Deck::attachBall() { _ballAttached = true; }

void Deck::detachBall()
{
    if (!_ballAttached) return;
    _ballAttached = false;
    //ball is pushed in random direction (from -60 to 60 degrees) with speed 100
    const int maxAngle = 60;
    const int speedAbs = 10;

    double angle = (rand() % (2 * maxAngle) - maxAngle) * 3.14 / 180;
    _ball->push(speedAbs * QVector2D(sin(angle), cos(angle)));
}
