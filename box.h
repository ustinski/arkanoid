#ifndef BOX_H
#define BOX_H

#include "mesh.h"

class Box : public Mesh
{
public:
    Box(double x, double y, QOpenGLTexture *shadow);

    static b2Body *create(double x, double y, double hWidth, double hHeight, b2World *world);

    void draw(Element element);
    void update();
    void reset();

    bool exists();
    static int width();
    static int height();

private:
    bool _exists;
};

#endif // BOX_H
