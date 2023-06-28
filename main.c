#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "rects.c"


int main(void) {
    SDL_Window *win = NULL;
    SDL_Renderer *rnd = NULL;
    SDL_DisplayMode *dm = NULL; 
    SDL_Event ev;
    uint32_t num_of_rects = 3;
    uint8_t cl[3] = {0,0,0};
    bool _loop = true;
    int resX, resY;

    win = SDL_CreateWindow("LSQ DEV BASIC!", 2, 2,
    800, 600, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if(!win) {
        printf("errr : 2 ;; win = SDL_CreateWindow(...);\n if can here is more err -> %s \n",
        SDL_GetError()); return 2;
    } rnd = SDL_CreateRenderer(win, 0, SDL_RENDERER_ACCELERATED);
    if(!rnd) {
        printf("errr : 3 \nrnd = SDL_CreateRenderer(win, 0, SDL_RENDERER_ACCELERATED);\n if can here is more err -> %s \n",
        SDL_GetError()); return 2;
    }

    SDL_GetWindowSize(win, (int*) &resX, (int*) &resY);

    obj *rects = NULL;
    rects = (obj*) malloc(sizeof(obj) * 10);
    obj_gen(rects, num_of_rects, resX, resY);

    while (_loop) {
        while (SDL_PollEvent(&ev)) {
            if(ev.type == SDL_QUIT) _loop == false;
            if(ev.type == SDL_KEYDOWN) {
                if(ev.key.keysym.sym == SDLK_ESCAPE) _loop = false;
                if(ev.key.keysym.sym == SDLK_r) obj_gen(rects, num_of_rects, resX, resY);
                if(ev.key.keysym.sym == SDLK_w) num_of_rects += 1;
                if(ev.key.keysym.sym == SDLK_s && num_of_rects > 0) num_of_rects -= 1;
            }
        }
        obj_update(rects, num_of_rects, resX, resY);

        SDL_RenderClear(rnd);
        obj_draw(rnd, rects, num_of_rects);
        SDL_SetRenderDrawColor(rnd, cl[0], cl[1], cl[2], 255);
        SDL_RenderPresent(rnd);
    }
    

    free(dm);

    SDL_DestroyRenderer(rnd);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}