#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "emesh.h"

class Background : public EMesh
{
public:
    Background() : EMesh("background", 0, 0) {}
    void draw();
};

#endif // BACKGROUND_H
