#ifndef SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#endif

typedef struct obj {
    SDL_FRect rect;
    uint8_t color[3];
    uint8_t dir;
    float vel;
} obj;


void obj_update(obj *rects, uint32_t num_of_rects, int resX, int resY) {
    uint8_t rnd;

    for(uint32_t cout = 0; cout < num_of_rects; cout++) {
        if(rects[cout].dir == 0) rects[cout].rect.y -= (float) 0.1f * rects[cout].vel; //up
        if(rects[cout].dir == 1) rects[cout].rect.y += (float) 0.1f * rects[cout].vel; //down
        if(rects[cout].dir == 2) rects[cout].rect.x -= (float) 0.1f * rects[cout].vel; //left
        if(rects[cout].dir == 3) rects[cout].rect.x += (float) 0.1f * rects[cout].vel; //right

        if(rects[cout].dir == 4) {
            rects[cout].rect.y -= (float) 0.05f * rects[cout].vel; //up left
            rects[cout].rect.x -= (float) 0.05f * rects[cout].vel; //left
        } if(rects[cout].dir == 5) {
            rects[cout].rect.y -= (float) 0.05f * rects[cout].vel; //up right
            rects[cout].rect.x += (float) 0.05f * rects[cout].vel; //right
        } if(rects[cout].dir == 6) {
            rects[cout].rect.y += (float) 0.05f * rects[cout].vel; //down right
            rects[cout].rect.x += (float) 0.05f * rects[cout].vel; //right
        } if(rects[cout].dir == 7) {
            rects[cout].rect.y += (float) 0.05f * rects[cout].vel; //down left
            rects[cout].rect.x -= (float) 0.05f * rects[cout].vel; //left
        }

        /*
        for(uint32_t cout2 = 0; cout2 < num_of_rects; cout2++) {
            if(rects[cout].rect.x + rects[cout].rect.w >= rects[cout2].rect.x) {
                rects[cout].dir = 2;
                rects[cout2].dir = 3;
            } 

            if(rects[cout2].rect.x + rects[cout2].rect.w >= rects[cout].rect.x) {
                rects[cout].dir = 3;
                rects[cout2].dir = 2;
            } 
        }
        */

        if(rects[cout].rect.x < 0) {
            rnd = rand() % 2;
            if(rnd == 2) rects[cout].dir = (uint8_t) 3;
            else if(rnd == 1) rects[cout].dir = (uint8_t) 5;
            else rects[cout].dir = (uint8_t) 6;}

        if(rects[cout].rect.y < 0) {
            rnd = rand() % 2;
            if(rnd == 2) rects[cout].dir = (uint8_t) 1;
            else if(rnd == 1) rects[cout].dir = (uint8_t) 6;
            else rects[cout].dir = (uint8_t) 6;}

        if(rects[cout].rect.x + rects[cout].rect.w > resX) {
            rnd = rand() % 2;
            if(rnd == 2) rects[cout].dir = (uint8_t) 2;
            else if(rnd == 1) rects[cout].dir = (uint8_t) 4;
            else rects[cout].dir = (uint8_t) 7;}

        if(rects[cout].rect.y + rects[cout].rect.h > resY) {
            rnd = rand() % 2;
            if(rnd == 2) rects[cout].dir = (uint8_t) 0;
            else if(rnd == 1) rects[cout].dir = (uint8_t) 4;
            else rects[cout].dir = (uint8_t) 5;
            }
    }
}

void obj_draw(SDL_Renderer *rnd, obj *rects, uint32_t num_of_rects) {
    for(uint32_t cout = 0; cout < num_of_rects; cout++) {
        SDL_SetRenderDrawColor(rnd,
        rects[cout].color[0],
        rects[cout].color[1],
        rects[cout].color[2], 255);
        
        if(cout != num_of_rects) {
            SDL_RenderDrawLineF(rnd,
            rects[cout].rect.x + (rects[cout].rect.w / 2),
            rects[cout].rect.y + (rects[cout].rect.h / 2),
            rects[cout + 1].rect.x + (rects[cout + 1].rect.w / 2),
            rects[cout + 1].rect.y + (rects[cout + 1].rect.h / 2));
        }
        SDL_RenderFillRectF(rnd, &rects[cout].rect);
    }
}

void obj_gen(obj *rects, uint32_t num_of_rects, int resX, int resY) {
    rects = (obj*) realloc(rects ,sizeof(obj) * num_of_rects);

    for(uint32_t cout = 0; cout < num_of_rects; cout++) {
        rects[cout].color[0] = (uint8_t) rand() % 255;
        rects[cout].color[1] = (uint8_t) rand() % 255;
        rects[cout].color[2] = (uint8_t) rand() % 255;

        rects[cout].dir = (uint8_t) rand() % 7;
        rects[cout].vel = (float) (rand() % 6 + 1) * 1.0f;

        rects[cout].rect.h = (float) ((rand() % 50) + 30) * 1.0f;
        rects[cout].rect.w = (float) ((rand() % 50) + 30) * 1.0f;
        rects[cout].rect.x = (float) ((rand() % resX) * 1.0f);
        rects[cout].rect.y = (float) ((rand() % resY) * 1.0f);

        if(rects[cout].rect.x + rects[cout].rect.w > resX) rects[cout].rect.x = 100;
        if(rects[cout].rect.y + rects[cout].rect.h > resY) rects[cout].rect.y = 100;
        if(rects[cout].rect.x < 0) rects[cout].rect.x = 100;
        if(rects[cout].rect.y < 0) rects[cout].rect.y = 100;

        printf("%f %f\n", rects[cout].rect.x,rects[cout].rect.y);
    }
}