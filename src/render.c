#include "globals.h"
#include "render.h"

void renderScreen(u_int32_t* pixels) {
    for(int x = 0; x < SCREEN_WIDTH; x++) {
        double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;  //x-coordinate in camera surface. Values [-1,1] 

        double rayDirX = cam.dir[0] + cam.plane[0] * cameraX;   
        double rayDirY = cam.dir[1] + cam.plane[1] * cameraX;

        //which tile of the map we are in. (Values of the Map Matrix)
        int mapX = (int)cam.pos[0];
        int mapY = (int)cam.pos[1];
        
        double sideDistX; //length of ray from current position to next x 
        double sideDistY; //length of ray from current position to next y

        //length of ray from one y-side next y-side

        double deltaDistX;
        // If the ray dont move in the X axis
        if (rayDirX == 0) deltaDistX = 1e30; // The distance from one x-site to the other is infinit
        else deltaDistX = fabs(1 / rayDirX);  // otherwise is 1/rayDirX 

        //length of ray from one y-side next y-side

        double deltaDistY;
        // If the ray dont move in the Y axis
        if (rayDirY == 0) deltaDistY = 1e30; // The distance from one y-site to the other is infinit
        else deltaDistY = fabs(1 / rayDirY); // otherwise is 1/rayDirY 

        double perpWallDist;
        //what direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;

        unsigned char hit = 0; // Boolean variable to controll wall hits
        int side; // Variable to controll which side of the wall is hitting

        //calculate the initial position for DDA
        if (rayDirX < 0) {
          stepX = -1;
          sideDistX = (cam.pos[0] - mapX) * deltaDistX;
        } else {
          stepX = 1;
          sideDistX = (mapX + 1.0 - cam.pos[0]) * deltaDistX;
        }

        if (rayDirY < 0) {
          stepY = -1;
          sideDistY = (cam.pos[1] - mapY) * deltaDistY;
        } else {
          stepY = 1;
          sideDistY = (mapY + 1.0 - cam.pos[1]) * deltaDistY;
        }
        
        //DDA loop
        while (hit == 0) {

          //jump to next map square, either in x-direction, or in y-direction
          if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0; // X axis, {East, West}
          } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1; // Y axis, {North, South}
          }

          // Check the GameMap limtis
          if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT) {
              hit = 1;
                if (side == 0) mapX -= stepX;
                else mapY -= stepY;
              break;
          }

          //Check if ray has hit a wall
          if (GameMap[mapX][mapY] > 0) hit = 1;
        } 
        
        // Calculate distance projected on camera direction
        if (side == 0) perpWallDist = (sideDistX - deltaDistX); 
        else perpWallDist = (sideDistY - deltaDistY);

        // Avoid divisions by 0 when you break the GameMap limits
        // Note: This happens when you are too close to a wall and the subtraction returns 0.
        if (perpWallDist < 0.1) perpWallDist = 0.1;
        
        //Calculate height of line to draw on screen
        int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
        
        // Apply vertical pitch: shifts the horizon line up or down on screen.
        int pitchOffset = (int)cam.pitch;

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2 + pitchOffset;
        if(drawStart < 0) drawStart = 0;
        if(drawStart >= SCREEN_HEIGHT) drawStart = SCREEN_HEIGHT - 1;

        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2 + pitchOffset;
        if(drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;
        if(drawEnd < 0) drawEnd = 0;
        
        // Get Color based on the map value
        u_int32_t color = colors[GameMap[mapX][mapY]];

        // Paint the sky
        for (int i = 0; i < drawStart; ++i) {
            pixels[i * SCREEN_WIDTH + x] = 0xFFFFCC00;
        }

        // Paint the tiles
        for(int y = drawStart; y < drawEnd; y++) {
            pixels[y * SCREEN_WIDTH + x] = color;
        }

        // Paint the floor
        for (int i = drawEnd; i < SCREEN_HEIGHT; ++i) {
            pixels[i * SCREEN_WIDTH + x] = 0xFF005555;
        }
    }
}

void renderMinimap(u_int32_t* pixels) {
    
    int minimapStartX = SCREEN_WIDTH - MINIMAP_SIZE;
    
    for(int x = minimapStartX; x < SCREEN_WIDTH; ++x) {
        for (int y = 0; y < MINIMAP_SIZE; ++y) {
            
            int distPixelX = x - minimapStartX - (MINIMAP_SIZE / 2); // Helper to select the tile. Values {-Minimap_Size, Minimap_size}
            int distPixelY = y - (MINIMAP_SIZE / 2);

            // Calculate the relative position with the player
            int targetMapX = (int)(cam.pos[0] + (distPixelY / (double)MAP_ZOOM)); 
            int targetMapY = (int)(cam.pos[1] + (distPixelX / (double)MAP_ZOOM));

            // If the position is out of the bounds 
            if (targetMapX < 0 || targetMapX >= MAP_WIDTH || targetMapY < 0 || targetMapY >= MAP_HEIGHT) pixels[y * SCREEN_WIDTH + x] = 0xFF808080; // Paint gray
            else pixels[y * SCREEN_WIDTH + x] = colors[GameMap[targetMapX][targetMapY]];      
        }
    }

    int centerX = minimapStartX + (MINIMAP_SIZE / 2);
    int centerY = (MINIMAP_SIZE / 2);   

    for(int py = centerY - 2; py <= centerY + 2; py++) {
        for(int px = centerX - 2; px <= centerX + 2; px++) {
             pixels[py * SCREEN_WIDTH + px] = 0xFF0000FF; 
        }
    }
} 

void RenderToPixelBuffer(u_int32_t* pixels) {
    memset(pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(uint32_t));
    renderScreen(pixels);
    renderMinimap(pixels);
}

void RenderMinimapRays(SDL_Renderer* renderer){

    int minimapStartX = SCREEN_WIDTH - MINIMAP_SIZE;
    int centerX = minimapStartX + (MINIMAP_SIZE / 2);
    int centerY = (MINIMAP_SIZE / 2);

    SDL_Rect minimapRect;
    minimapRect.x = minimapStartX;
    minimapRect.y = 0; 
    minimapRect.w = MINIMAP_SIZE;
    minimapRect.h = MINIMAP_SIZE;

    SDL_RenderSetClipRect(renderer, &minimapRect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 100);
    
    int numRays = 100;   
    for (int i = 0; i < numRays; ++i) {

        double cameraX = 2 * i / (double)numRays - 1; 
        
        double rayDirX = cam.dir[0] + cam.plane[0] * cameraX;
        double rayDirY = cam.dir[1] + cam.plane[1] * cameraX;

        int mapX = (int)cam.pos[0];
        int mapY = (int)cam.pos[1];
        
        double sideDistX;  
        double sideDistY; 

        double deltaDistX;

        if (rayDirX == 0) deltaDistX = 1e30; 
        else deltaDistX = fabs(1 / rayDirX);

        double deltaDistY;
        if (rayDirY == 0) deltaDistY = 1e30; 
        else deltaDistY = fabs(1 / rayDirY);

        double perpWallDist;
        int stepX;
        int stepY;

        unsigned char hit = 0; 
        int side; 

        if (rayDirX < 0) {
          stepX = -1;
          sideDistX = (cam.pos[0] - mapX) * deltaDistX;
        } else {
          stepX = 1;
          sideDistX = (mapX + 1.0 - cam.pos[0]) * deltaDistX;
        }

        if (rayDirY < 0) {
          stepY = -1;
          sideDistY = (cam.pos[1] - mapY) * deltaDistY;
        } else {
          stepY = 1;
          sideDistY = (mapY + 1.0 - cam.pos[1]) * deltaDistY;
        }
        
        while (hit == 0) {

          if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0; 
          } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1; 
          }

          if (GameMap[mapX][mapY] > 0) hit = 1;
        } 

        if (side == 0) perpWallDist = (sideDistX - deltaDistX); 
        else perpWallDist = (sideDistY - deltaDistY);

        double hitX = cam.pos[0] + rayDirX * perpWallDist;
        double hitY = cam.pos[1] + rayDirY * perpWallDist;

        int endPixelX = centerX + (int)((hitY - cam.pos[1]) * MAP_ZOOM);
        int endPixelY = centerY + (int)((hitX - cam.pos[0]) * MAP_ZOOM);

        SDL_RenderDrawLine(renderer, centerX, centerY, endPixelX, endPixelY);
    }

    SDL_RenderSetClipRect(renderer, NULL);
}

void PresentPixelBuffer(u_int32_t* pixels) {
    SDL_UpdateTexture(state.texture, NULL, pixels, SCREEN_WIDTH * sizeof(uint32_t));
    SDL_RenderCopy(state.renderer, state.texture, NULL, NULL);
    RenderMinimapRays(state.renderer);
    SDL_RenderPresent(state.renderer);
}
