#ifndef GLOBALS_H
#define GLOBALS_H

#define _GNU_SOURCE
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

#define MAP_WIDTH 48
#define MAP_HEIGHT 48

#define MOV_SPEED 5.0
#define ROT_SPEED 5.0
#define PITCH_SPEED 1000.0      
#define MAX_PITCH (SCREEN_HEIGHT / 2)   

#define MINIMAP_SIZE 200
#define MAP_ZOOM 12

struct GameState {
    unsigned char quit; 

    SDL_Window* win;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
};

struct GameFlags {
    unsigned char move_left;
    unsigned char move_right;
    unsigned char move_forward;
    unsigned char move_backwards;

    unsigned char rotate_left;
    unsigned char rotate_right;

    unsigned char look_up;
    unsigned char look_down;
};

struct Camera {
    double pos[2];  // Position of the camera
    double dir[2];  // Direction where the camera is looking
    double plane[2]; // The camera 2D surface where the rays are casted.
    double pitch;   // Vertical look offset in pixels (horizon shift)
};

extern struct GameState state;
extern struct GameFlags control;
extern struct Camera cam;

extern const u_int32_t colors[6];
extern int GameMap[MAP_WIDTH][MAP_HEIGHT];

double get_time();

#endif
