#include "window.h"

#include <QKeyEvent>

namespace Window
{
    const int _width = 1300;
    const int _height = 650;

    bool _left = false;
    bool _right = false;
}

int Window::width()
{ return _width; }

int Window::height()
{ return _height; }

void Window::arrow(int direction, Action action)
{ (direction == Qt::Key_Left ? _left : _right) = action; }

bool Window::leftArrowPressed() { return _left; }
bool Window::rightArrowPressed() { return _right; }
