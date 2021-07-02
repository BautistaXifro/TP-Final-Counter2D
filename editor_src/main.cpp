#include <SDL2/SDL.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "../common_src/Sdl/sdl_texture.h"
#include "../common_src/Sdl/sdl_window.h"
#include "../common_src/Sdl/sdl_renderer.h"
#include "../client_src/Character/camera.h"
#include "../common_src/Sdl/draggable.h"
#include "editor.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The frame rate
const int FRAMES_PER_SECOND = 20;

//The dimensions of the level
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;


//Tile constants
const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;
const int TOTAL_TILES = 192;
const int TOTAL_TILE_SPRITES = 12;

void setCamera(SDL_Rect& camera);

int main(int argc, char* args[]){

    SdlWindow window("Editor", 640, 480);
    SdlRenderer renderer(&window);
	
    Editor editor("../../common_src/maps/map.yaml", renderer);

    Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT);

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event event;
    
    //While application is running
    while (!quit){
        //Handle events on queue
        camera.centerCameraOnMouse(TILE_WIDTH, LEVEL_WIDTH, LEVEL_HEIGHT);
        while (SDL_PollEvent(&event) != 0){
            //User requests quit
            if (event.type == SDL_QUIT){
                quit = true;
            }else if (event.type == SDL_MOUSEBUTTONDOWN){
                //On left mouse click
                if (event.button.button == SDL_BUTTON_RIGHT){
                    editor.put_tile(camera.getRect(), renderer);
                }
            }else if (event.type == SDL_KEYDOWN){

                if (event.key.keysym.sym == SDLK_1){
                    editor.presentBombSites();
                }
                
                else if (event.key.keysym.sym == SDLK_2){
                    editor.presentSpawnSites();
                }
                
                else if(event.key.keysym.sym == SDLK_ESCAPE){
                    editor.initMenue();
                }

            }else if (event.type == SDL_KEYUP){
                if (event.key.keysym.sym == SDLK_1){
                    editor.stopPresentingBombSites();
                }else if (event.key.keysym.sym == SDLK_2){
                    editor.stopPresentingSpawnSites();
                }
            }
            editor.handleEvents(&event, camera.getRect());
            window.setTitle("Level Designer. Current Tile: " + editor.getTitle());
        }

        renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
        renderer.clear();
        camera.centerCameraOnMouse(TILE_WIDTH, LEVEL_WIDTH, LEVEL_HEIGHT);

        editor.render(camera.getRect());

        renderer.updateScreen();
    }
    editor.saveMap();
    return 0;
}