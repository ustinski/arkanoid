#include "glwidget.h"
#include "window.h"
#include "gl.h"
#include "physics.h"
#include "gameobjects.h"
#include "arkanoid.h"
#include "fontrenderer.h"
#include "sdlmixer.h"

#include <QBasicTimer>
#include <QKeyEvent>

GLWidget::GLWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{
    setFixedSize(Window::width(), Window::height());
    setMouseTracking(true);
    QCursor cursor;
    cursor.setPos(Window::width() / 2, Window::height() / 2);
    setCursor(cursor);
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    GL::init(this);
    Arkanoid::init();
    Physics::init();
    GameObjects::init();
    FontRenderer::init();
    SdlMixer::init(this);

    (new QBasicTimer)->start(0, this);
    timer.start();
}

void GLWidget::resizeGL(int w, int h)
{
    GL::resize(w, h);
    glViewport(0, 0, w, h);
}

void GLWidget::paintGL()
{
    GameObjects::draw();
    Arkanoid::draw();
}

void GLWidget::timerEvent(QTimerEvent *event)
{
    double dt = timer.elapsed() / double(1000);
    timer.restart();

    Arkanoid::update(dt);
    Physics::update(dt);
    GameObjects::update();

    update();
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    if(!Arkanoid::pauseEnded()) return;
    int key = event->key();
    if(key == Qt::Key_Space) GameObjects::detachBallFromDeck();
    if(key == Qt::Key_Left || key == Qt::Key_Right)
        Window::arrow(key, Window::PRESSED);
}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
    if(!Arkanoid::pauseEnded() && !Arkanoid::newGame()) return;
    int key = event->key();
    if(key == Qt::Key_Left || key == Qt::Key_Right)
        Window::arrow(key, Window::RELEASED);
}
