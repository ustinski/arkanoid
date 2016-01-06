#include "gameobjects.h"
#include "background.h"
#include "box.h"
#include "ball.h"
#include "deck.h"
#include "window.h"
#include "arkanoid.h"

namespace GameObjects
{
    const int lines = 5;
    const int columns = 13;

    vector <QOpenGLTexture*> _boxTextures;
    QOpenGLTexture *boxShadow;
    Box* boxes[lines][columns];
    Ball *ball;
    Deck *deck;

    vector <Mesh*> objectList;

    Background *_background;


    void initBoxTextures();
    void pushBT(const QString &texture);
    QOpenGLTexture *loadTexture(const QString &texture);
    void initObjects();

    bool noBoxesLeft();
    void updateObjects();
}

void GameObjects::init()
{
    initBoxTextures();
    initObjects();
}

void GameObjects::initBoxTextures()
{
    pushBT("blue");
    pushBT("green");
    pushBT("yellow");
    pushBT("violet");
    pushBT("orange");
    boxShadow = loadTexture("boxShadow");
}

void GameObjects::pushBT(const QString &texture)
{ _boxTextures.push_back(loadTexture(texture)); }

QOpenGLTexture *GameObjects::loadTexture(const QString &texture)
{ return loadImage(QImage(":/textures/" + texture + ".png")); }

void GameObjects::initObjects()
{
    _background = new Background();

    for(int i = 0; i < lines; i++) for(int j = 0; j < columns; j++)
        boxes[i][j] = new Box(-Window::width() / 2 + Box::width() * j + Box::width() / 2, Window::height() / 2 - Box::height() * i - Box::height() / 2, boxShadow);
    ball = new Ball();
    deck = new Deck(ball);

    for(int i = 0; i < lines; i++) for(int j = 0; j < columns; j++)
        objectList.push_back(boxes[i][j]);
    objectList.push_back(ball);
    objectList.push_back(deck);
}

void GameObjects::draw()
{
    _background->draw();

    for(int i = 0; i < objectList.size(); i++) objectList[i]->draw(Mesh::SHADOW);
    for(int i = 0; i < objectList.size(); i++) objectList[i]->draw(Mesh::BODY);
}

void GameObjects::update()
{
    if(noBoxesLeft()) Arkanoid::startNewGame();
    else updateObjects();
}

bool GameObjects::noBoxesLeft()
{
    if(Arkanoid::newGame()) return false;

    int i, j;
    for(i = 0; i < lines; i++) {
        for(j = 0; j < columns; j++) if(boxes[i][j]->exists()) break;
        if(j < columns) break;
    }
    return (i == lines && j == columns);
}

void GameObjects::updateObjects()
{
    for(int i = 0; i < lines; i++) for(int j = 0; j < columns; j++)
        boxes[i][j]->update();
    ball->update();
    deck->update();
}


QOpenGLTexture *GameObjects::boxTexture()
{ return _boxTextures[rand() % _boxTextures.size()]; }

void GameObjects::detachBallFromDeck()
{ deck->detachBall(); }

void GameObjects::resetBoxes()
{
    for(int i = 0; i < lines; i++) for(int j = 0; j < columns; j++)
        boxes[i][j]->reset();
}

void GameObjects::reset()
{
    ball->reset();
    deck->attachBall();
}

QOpenGLTexture *GameObjects::loadImage(const QImage &image)
{
    QOpenGLTexture *t = new QOpenGLTexture(image.mirrored());
    t->setMinificationFilter(QOpenGLTexture::Nearest);
    t->setMagnificationFilter(QOpenGLTexture::Linear);
    t->setWrapMode(QOpenGLTexture::Repeat);
    return t;
}
