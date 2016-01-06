#ifndef ARKANOID_H
#define ARKANOID_H


namespace Arkanoid
{
    void init();
    void draw();
    void update(double dt);

    void addScore();
    void startNewGame();
    bool newGame();
    bool pauseEnded();

    void cancelCombo();
}

#endif // ARKANOID_H
