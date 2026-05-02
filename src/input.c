#include "globals.h"
#include "input.h"

void ProcessEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type){
      case SDL_KEYDOWN:

        if (SDLK_ESCAPE == event.key.keysym.sym) state.quit = 1;
        if (SDLK_SPACE == event.key.keysym.sym) printf("Testing Inputs\n");
        if (SDLK_w == event.key.keysym.sym) control.move_forward = 1;
        if (SDLK_a == event.key.keysym.sym) control.move_left = 1;
        if (SDLK_s == event.key.keysym.sym) control.move_backwards = 1;
        if (SDLK_d == event.key.keysym.sym) control.move_right = 1;
        if (SDLK_RIGHT == event.key.keysym.sym) control.rotate_right = 1;
        if (SDLK_LEFT == event.key.keysym.sym) control.rotate_left = 1;
        if (SDLK_UP == event.key.keysym.sym) control.look_up = 1;
        if (SDLK_DOWN == event.key.keysym.sym) control.look_down = 1;
        
    break;
    case SDL_KEYUP:
        if (SDLK_w == event.key.keysym.sym) control.move_forward = 0;
        if (SDLK_a == event.key.keysym.sym) control.move_left = 0;
        if (SDLK_s == event.key.keysym.sym) control.move_backwards = 0;
        if (SDLK_d == event.key.keysym.sym) control.move_right = 0;
        if (SDLK_RIGHT == event.key.keysym.sym) control.rotate_right = 0;
        if (SDLK_LEFT == event.key.keysym.sym) control.rotate_left = 0;
        if (SDLK_UP == event.key.keysym.sym) control.look_up = 0;
        if (SDLK_DOWN == event.key.keysym.sym) control.look_down = 0;
    break;
    default:
        break;
    }
    
}
