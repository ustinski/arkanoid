#ifndef MESH_H
#define MESH_H

#include "emesh.h"
#include "physics.h"

class Mesh : public EMesh
{
public:
    //Mesh() {}
    //
    Mesh(double x, double y, QOpenGLTexture *shadow);
    Mesh(double x, double y, const QString &texture, const QString &shadow);
    Mesh(const QString &texture, const QString &shadow);

    enum Element { BODY, SHADOW };
    virtual void draw(Element element);
    //virtual void update() = 0;
    void setPosition(double x, double y);
    //void setPosition(const b2Vec2 &position);
    void endContact();

protected:
    b2Body *_body;
    bool _contact;

private:
    EMesh *_shadow;

    QVector2D shadowPosition();
};

#endif // MESH_H
