#include "mesh.h"

Mesh::Mesh(double x, double y, QOpenGLTexture *shadow) :
    EMesh(x, y)
{
    _shadow = new EMesh(shadow, shadowPosition());
    _contact = false;
}

Mesh::Mesh(double x, double y, const QString &texture, const QString &shadow) :
    EMesh(texture, x, y)
{
    _shadow = new EMesh(shadow, shadowPosition());
    _contact = false;
}

Mesh::Mesh(const QString &texture, const QString &shadow) :
    EMesh(texture)
{
    _shadow = new EMesh(shadow, shadowPosition());
    _contact = false;
}

void Mesh::draw(Element element)
{
    if(element == BODY) EMesh::draw();
    if(element == SHADOW) _shadow->draw();
}

void Mesh::setPosition(double x, double y)
{
    EMesh::setPosition(x, y);
    _shadow->setPosition(x + 5, y - 5);
}

void Mesh::endContact() { _contact = true; }

QVector2D Mesh::shadowPosition() { return _position + QVector2D(5, -5); }
