#include "globals.h"
#include "player.h"

void TickGame(double dt) {

    double moveStep = MOV_SPEED * dt;
    double rotStep = ROT_SPEED * dt;
    double pitchStep = PITCH_SPEED * dt;

    if (control.move_forward) {
        int nextMapX = (int)(cam.pos[0] + moveStep*cam.dir[0]);
        int nextMapY = (int)(cam.pos[1] + moveStep*cam.dir[1]);
        if (nextMapX < MAP_WIDTH && nextMapX >= 0 && GameMap[nextMapX][(int)cam.pos[1]] == 0) cam.pos[0] += moveStep*cam.dir[0];
        if (nextMapY < MAP_HEIGHT && nextMapY >= 0 && GameMap[(int)cam.pos[0]][nextMapY] == 0) cam.pos[1] += moveStep*cam.dir[1];
    }
    if (control.move_backwards) {
        int nextMapX = (int)(cam.pos[0] - moveStep*cam.dir[0]);
        int nextMapY = (int)(cam.pos[1] - moveStep*cam.dir[1]);
        if (nextMapX < MAP_WIDTH && nextMapX >= 0 && GameMap[nextMapX][(int)cam.pos[1]] == 0) cam.pos[0] -= moveStep*cam.dir[0];
        if (nextMapY < MAP_HEIGHT && nextMapY >= 0 && GameMap[(int)cam.pos[0]][nextMapY] == 0) cam.pos[1] -= moveStep*cam.dir[1];
    }
    if (control.move_left) {
        int nextMapX = (int)(cam.pos[0] - moveStep*cam.dir[1]);
        int nextMapY = (int)(cam.pos[1] + moveStep*cam.dir[0]);
        if (nextMapX < MAP_WIDTH && nextMapX >= 0 && GameMap[nextMapX][(int)cam.pos[1]] == 0) cam.pos[0] -= moveStep * cam.dir[1];
        if (nextMapY < MAP_HEIGHT && nextMapY >= 0 && GameMap[(int)cam.pos[0]][nextMapY] == 0) cam.pos[1] += moveStep * cam.dir[0];
    }
    if (control.move_right) {
        int nextMapX = (int)(cam.pos[0] + moveStep*cam.dir[1]);
        int nextMapY = (int)(cam.pos[1] - moveStep*cam.dir[0]);
        if (nextMapX < MAP_WIDTH && nextMapX >= 0 && GameMap[nextMapX][(int)cam.pos[1]] == 0) cam.pos[0] += moveStep * cam.dir[1];
        if (nextMapY < MAP_HEIGHT && nextMapY >= 0 && GameMap[(int)cam.pos[0]][nextMapY] == 0) cam.pos[1] -= moveStep * cam.dir[0];
    }

    if (control.rotate_right) {
        double oldDirX = cam.dir[0];
        cam.dir[0] = cam.dir[0] * cos(-rotStep) - cam.dir[1] * sin(-rotStep);
        cam.dir[1] = oldDirX * sin(-rotStep) + cam.dir[1] * cos(-rotStep);

        double oldPlaneX = cam.plane[0];
        cam.plane[0] = cam.plane[0] * cos(-rotStep) - cam.plane[1] * sin(-rotStep);
        cam.plane[1] = oldPlaneX * sin(-rotStep) + cam.plane[1] * cos(-rotStep);
    }

    if (control.rotate_left) {
        double oldDirX = cam.dir[0];
        cam.dir[0] = cam.dir[0] * cos(rotStep) -  cam.dir[1] * sin(rotStep);
        cam.dir[1] = oldDirX * sin(rotStep) + cam.dir[1] * cos(rotStep);

        double oldPlaneX = cam.plane[0];
        cam.plane[0] = cam.plane[0] * cos(rotStep) - cam.plane[1] * sin(rotStep);
        cam.plane[1] = oldPlaneX * sin(rotStep) + cam.plane[1] * cos(rotStep);
    }

    if (control.look_up)   cam.pitch += pitchStep;
    if (control.look_down) cam.pitch -= pitchStep;

    if (cam.pitch >  MAX_PITCH) cam.pitch =  MAX_PITCH;
    if (cam.pitch < -MAX_PITCH) cam.pitch = -MAX_PITCH;
}
