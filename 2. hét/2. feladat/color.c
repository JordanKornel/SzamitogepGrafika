#include "color.h"
#include "util.h"

void setColor(Color* color, int r, int g, int b, int a) {
    color->r = r;
    color->g = g;
    color->b = b;
    color->a = a;
}

void randomColor(Color* color) {
    color->r = randomInteger(0, 255);
    color->g = randomInteger(0, 255);
    color->b = randomInteger(0, 255);
    color->a = 255;
}