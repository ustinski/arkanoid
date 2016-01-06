#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

class QOpenGLTexture;
class QImage;

namespace GameObjects
{
    void init();
    void draw();
    void update();

    QOpenGLTexture *boxTexture();
    void detachBallFromDeck();
    void resetBoxes();
    void reset();

    QOpenGLTexture *loadImage(const QImage &image);
}

#endif // GAMEOBJECTS_H
