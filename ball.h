#ifndef BALL_H
#define BALL_H

#include "mesh.h"

class Ball : public Mesh
{
public:
    Ball();

    void draw(Element element);
    void update();
    void push(const QVector2D &dV);
    void pushAngular(double dw);
    void setPosition(double x, double y);
    void setPosition(const b2Vec2 &position);
    void setPhysPosition(double x, double y);
    void reset();
    int getRadius();

private:
    EMesh *line;

    const int radius;
};

#endif // BALL_H
