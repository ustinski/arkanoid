#ifndef DECK_H
#define DECK_H

#include "mesh.h"

class Ball;

class Deck : public Mesh
{
public:
    Deck(Ball *ball);

    void update();

    void attachBall();
    void detachBall();

private:
    Ball *_ball;
    bool _ballAttached;


};

#endif // DECK_H
