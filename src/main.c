#include "globals.h"
#include "input.h"
#include "player.h"
#include "render.h"

// Time variables for fps control
double curr_time = 0;      
double prev_time = 0;

int main(int argc, char* argv[]) {
    
    cam.pos[0] = 12; cam.pos[1] = 12;
    cam.dir[0] = 0; cam.dir[1] = 1;
    cam.plane[0] = 0.66; cam.plane[1] = 0;
    cam.pitch = 0;

    SDL_Init(SDL_INIT_EVERYTHING);

    state.win = SDL_CreateWindow("Raycaster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    state.renderer = SDL_CreateRenderer(state.win, -1, 0);

    state.texture = SDL_CreateTexture(state.renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

    u_int32_t pixels[SCREEN_WIDTH * SCREEN_HEIGHT];

    int frame_count = 0;
    double frame_count_sec = 0;
    prev_time = get_time();
    while (state.quit == 0) {
        curr_time = get_time();
        double dt = (double)(curr_time - prev_time);
        prev_time = curr_time;

        ProcessEvents();
        TickGame(dt);
        RenderToPixelBuffer(pixels);
        PresentPixelBuffer(pixels);

        frame_count++;
        frame_count_sec += dt;
        if (frame_count_sec > 1.0) {
            char buffer[64];
            sprintf(buffer, "Game running at %d FPS\n",frame_count);   
            write(1,buffer,strlen(buffer));
            frame_count = 0;
            frame_count_sec = 0; 
        }
    }
}
