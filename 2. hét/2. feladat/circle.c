#include "circle.h"

void makeCircle(Circle* circle, int centerX, int centerY, int radius, int r, int g, int b, int a) {
    circle->x = centerX;
    circle->y = centerY;
    circle->radius = radius;

    setColor(&circle->color, r, g, b, a);
    
    circle->select = false;
    circle->edit = false;
}

void SDL_RenderDrawCircle(SDL_Renderer* renderer, int32_t centerX, int32_t centerY, int32_t radius) {
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;

    int32_t tx = 1;
    int32_t ty = 1;

    int32_t error = (tx - diameter);

    while (x >= y) {
        SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);

        if (error <= 0) {
            y++;
            error += ty;
            ty += 2;
        }

        if (error > 0) {
            x--;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

bool isInSlotCircle(int centerX, int centerY, int r, int x, int y) {
    if (abs(centerX - x) <= r && abs(centerY - y) <= r) {
        return true;
    }
    return false;
}