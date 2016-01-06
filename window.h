#ifndef WINDOW_H
#define WINDOW_H

namespace Window
{
    int width();
    int height();

    enum Action { RELEASED, PRESSED };
    void arrow(int direction, Action action);
    bool leftArrowPressed();
    bool rightArrowPressed();
}

#endif // WINDOW_H
