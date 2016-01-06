#include "arkanoid.h"
#include "gameobjects.h"
#include "fontrenderer.h"
#include "window.h"

#include <QString>

namespace Arkanoid
{
    int _score;
    const int scoreForOneBox = 2;
    const int oneSecond = 1;
    const int twoSeconds = 2;
    double time;
    bool _newGame;
    double _newGamePauseTime;
    int _combo;

    void updateNewGamePause(double dt);
    void updateScore(double dt);
}

void Arkanoid::init()
{
    _score = 0;
    _newGame = false;
    //pause is ended when pauseTime is more then 2 seconds
    _newGamePauseTime = twoSeconds + 0.001;
    _combo = 1;
}

void Arkanoid::draw()
{
    FontRenderer::draw("SCORE: " + QString::number(_score), -Window::width() / 2 + 100, -Window::height() / 2 + 12);
}

void Arkanoid::update(double dt)
{
    if(_newGame) updateNewGamePause(dt);
    else updateScore(dt);
}

void Arkanoid::updateNewGamePause(double dt)
{
    _newGamePauseTime += dt;
    if(pauseEnded()) {
        _newGame = false;
        GameObjects::resetBoxes();
        _score = 0;
    }
}

void Arkanoid::updateScore(double dt)
{
    time += dt;
    if(time >= oneSecond) {
        time = 0;
        _score--;
        if(_score < 0) _score = 0;
    }
}

void Arkanoid::addScore()
{ _score += scoreForOneBox * _combo++; }

void Arkanoid::startNewGame()
{
    if(_newGame) return;
    GameObjects::reset();
    _newGame = true;
    _newGamePauseTime = 0;
    _combo = 1;
}

bool Arkanoid::newGame() { return _newGame; }

bool Arkanoid::pauseEnded()
{ return _newGamePauseTime >= twoSeconds; }

void Arkanoid::cancelCombo() { _combo = 1; }
