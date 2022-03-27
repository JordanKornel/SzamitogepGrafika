#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "util.h"
#include "color.h"
#include "circle.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 640

#define MAX_CIRCLE_COUNT 10

int main(int argc, char** args) {
    int error_code;
    bool need_run = true;
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    int i;
    bool isDraw;

    bool isCircle = false;
    bool isEdit = false;

    // Circle Settings
    Circle newCircle;
    Circle circles[MAX_CIRCLE_COUNT];
    int circleCount = 0;
    int circleIndex = 0;


    // Random
    srand(time(NULL));

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0) {
        printf("[Error] SDL initialization error: %s\n", SDL_GetError());
        return error_code;
    }

    // Window
    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    // Render
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    while (need_run) {
        // Event
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    if (event.button.type == SDL_KEYDOWN) {
                        if (event.key.keysym.sym == SDLK_ESCAPE) {
                            need_run = false;
                        }
                    }
                    break;
                case SDL_QUIT:
                    need_run = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_RIGHT) {
                        if (event.button.state == SDL_PRESSED) {
                            printf("Mouse Position: [X: %d, Y: %d]\n", event.button.x, event.button.y);
                        }
                    } else if (event.button.button == SDL_BUTTON_LEFT) {
                        if (isEdit) {
                            isEdit = false;

                            if (isInSlotCircle(circles[i].x, circles[i].y, circles[i].radius, event.button.x, event.button.y)) {
                                circles[i].edit = false;

                                circles[i].x = event.button.x - circles[i].ex;
                                circles[i].y = event.button.y - circles[i].ey;
                            }
                        } else if (!isEdit) {
                            for (i = 0; i < circleCount; i++) {
                                if (isInSlotCircle(circles[i].x, circles[i].y, circles[i].radius, event.button.x, event.button.y)) {
                                    isEdit = true;

                                    circles[i].edit = true;

                                    circles[i].ex = (event.button.x - circles[i].x);
                                    circles[i].ey = (event.button.y - circles[i].y);
                                
                                }
                            }
                            if (!isEdit) {
                                if (event.button.state == SDL_PRESSED) {
                                    newCircle.x = event.button.x;
                                    newCircle.y = event.button.y;
                                    newCircle.radius = randomInteger(30, 100);
                                    randomColor(&newCircle.color);

                                    isDraw = true;
                                }
                            }
                        }
                    }
                    break;
                case SDL_MOUSEMOTION:
                    for (i = 0; i < circleCount; i++) {
                        if (!isEdit) {
                            if (isInSlotCircle(circles[i].x, circles[i].y, circles[i].radius, event.button.x, event.button.y)) {
                                circles[i].select = true;
                            } else {
                                circles[i].select = false;
                            }
                        } else {
                            if (circles[i].edit) {
                                circles[i].x = event.button.x - circles[i].ex;
                                circles[i].y = event.button.y - circles[i].ey;
                            }
                        }
                    }
                    break;
            }
        }

        /* Draw */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        if (isDraw) {
            if (circleIndex >= MAX_CIRCLE_COUNT) {
                circleIndex = 0;
            }

            circles[circleIndex].x = newCircle.x;
            circles[circleIndex].y = newCircle.y;
            circles[circleIndex].radius = newCircle.radius;
            setColor(&circles[circleIndex].color, newCircle.color.r, newCircle.color.g, newCircle.color.b, newCircle.color.a);

            if (circleCount != MAX_CIRCLE_COUNT) {
                circleCount++;
            }

            circleIndex++;
            isDraw = false;
        }

        for (i = 0; i < circleCount; i++) {
            SDL_SetRenderDrawColor(renderer, circles[i].color.r, circles[i].color.g, circles[i].color.b, circles[i].color.a);
            SDL_RenderDrawCircle(renderer, circles[i].x, circles[i].y, circles[i].radius);

            if (circles[i].select) {
                SDL_RenderDrawLine(renderer, circles[i].x, circles[i].y-10, circles[i].x, circles[i].y+10);
                SDL_RenderDrawLine(renderer, circles[i].x-10, circles[i].y, circles[i].x+10, circles[i].y);
            }
        }

        // Render
        SDL_RenderPresent(renderer);
    }
    
    // Prog Exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}