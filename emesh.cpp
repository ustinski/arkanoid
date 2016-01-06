#include "emesh.h"
#include "gl.h"
#include "gameobjects.h"

#include <math.h>

EMesh::EMesh(const QString &texture, double x, double y)
{ init(texture, x, y); }

EMesh::EMesh(const QString &texture, const QVector2D &position)
{ init(texture, position.x(), position.y()); }

EMesh::EMesh(double x, double y) { _position = {x, y}; }

EMesh::EMesh(QOpenGLTexture *texture, const QVector2D &position)
{ init(texture, position.x(), position.y()); }

EMesh::EMesh(const QString &texture)
{
    QImage image(":/textures/" + texture + ".png");
    _texture = GameObjects::loadImage(image);
    initVertices();
}

void EMesh::init(QOpenGLTexture *texture, double x, double y)
{
    _texture = texture;
    _position = {x, y};
    initVertices();
}

void EMesh::init(const QString &texture, double x, double y)
{
    QImage image(":/textures/" + texture + ".png");
    init(GameObjects::loadImage(image), x, y);
}

void EMesh::initVertices()
{
    const double hw = _texture->width() / 2;
    const double hh = _texture->height() / 2;
    vertices.resize(4);
    vertices[0] = {{-hw, -hh, 0}, {0, 0}};
    vertices[1] = {{ hw, -hh, 0}, {1, 0}};
    vertices[2] = {{ hw,  hh, 0}, {1, 1}};
    vertices[3] = {{-hw,  hh, 0}, {0, 1}};

    _arrayBuf.destroy();
    _arrayBuf.create();
    _arrayBuf.bind();
    _arrayBuf.allocate(vertices.data(), vertices.size() * sizeof(VertexData));
}

void EMesh::setPosition(double x, double y) { _position = {x, y}; }

void EMesh::draw()
{
    _arrayBuf.bind();

    QOpenGLShaderProgram *program = GL::texture();
    program->bind();
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(VertexData));
    int fragmentLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(fragmentLocation);
    program->setAttributeBuffer(fragmentLocation, GL_FLOAT, sizeof(QVector3D), 2, sizeof(VertexData));

    prepareMatrix();
    program->setUniformValue("mvp_matrix", GL::projection() * model);
    program->setUniformValue("texture", 0);
    _texture->bind(0);

    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
}

void EMesh::prepareMatrix()
{
    model.setToIdentity();
    model.translate(QVector3D(_position.x(), _position.y(), 0));
    model.rotate(_angle * 180 / M_PI, 0, 0, 1);
}
