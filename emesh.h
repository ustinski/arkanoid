#ifndef EMESH_H
#define EMESH_H

#include <QVector2D>
#include <QVector3D>
#include <QMatrix4x4>

#include "gl.h"

#include <vector>

using namespace std;

struct VertexData
{
    QVector3D position;
    QVector2D uv;
};

class GLWidget;

class EMesh
{
public:
    EMesh(const QString &texture, double x, double y);
    EMesh(const QString &texture, const QVector2D &position);
    EMesh(double x, double y);
    EMesh(QOpenGLTexture *texture, const QVector2D &position);
    EMesh(const QString &texture);
    //EMesh() {}



/*    EMesh(QOpenGLTexture *texture, double x, double y, int width, int height)
    { init(texture, x, y, width, height); }*/

    void init(QOpenGLTexture *texture, double x, double y);
    void init(const QString &texture, double x, double y);

    QOpenGLBuffer *arrayBuf() { return &_arrayBuf; }
    void setPosition(const QPoint position)
    { _position = QVector2D(position); }

    virtual void move(const QVector2D &dr) { _position += dr; }
    void setPosition(double x, double y);
    const QVector2D &position() { return _position; }
    void setAngle(double angle) { _angle = angle; }
    virtual void draw();

protected:
    QMatrix4x4 model;

    QOpenGLTexture *_texture;
    QVector2D _position;
    double _angle = 0;

    QOpenGLBuffer _arrayBuf;


    void initVertices();
    virtual void prepareMatrix();

private:
    vector <VertexData> vertices;
};

#endif // EMESH_H
