#ifndef CircleDefine
    #include <SDL2/SDL.h>
    #include <stdbool.h>
    #include <math.h>
    #include "color.h"
    #define CircleDefine

    typedef struct Circle {
        int x;
        int y;

        int ex;
        int ey;

        int radius;

        Color color;
        bool select;
        bool edit;
    } Circle;
    void makeCircle(Circle* circle, int centerX, int centerY, int radius, int r, int g, int b, int a);
    void SDL_RenderDrawCircle(SDL_Renderer* renderer, int32_t centerX, int32_t centerY, int32_t radius);
    bool isInSlotCircle(int centerX, int centerY, int r, int x, int y);
#endif