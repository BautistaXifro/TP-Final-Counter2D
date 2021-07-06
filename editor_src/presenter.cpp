#include "presenter.h"
#include "TextureFactory.h"
#include <fstream>
#include <stdio.h>
const int TILE_WIDTH = 80;
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

Presenter::Presenter(std::map<std::string, std::shared_ptr<Draggable>>& bombSites, std::map<std::string, std::shared_ptr<Draggable>>& spawnSites, 
int screenW, int screenH) : camera(screenW, screenH){
    this->bombSites = bombSites;
    this->spawnSites = spawnSites;
}

void Presenter::renderBombSites(){
    std::map<std::string, std::shared_ptr<Draggable>>::iterator iterator = this->bombSites.begin();
    while (iterator != this->bombSites.end()){
        iterator->second->setBlendMode(SDL_BLENDMODE_BLEND);
        iterator->second->setAlpha(100);
        iterator->second->render(this->camera.getRect());
        ++iterator;
    }
}

void Presenter::renderSpawnSites(){
    std::map<std::string, std::shared_ptr<Draggable>>::iterator iterator = this->spawnSites.begin();
    while (iterator != this->spawnSites.end()){
        iterator->second->setBlendMode(SDL_BLENDMODE_BLEND);
        iterator->second->setAlpha(100);
        iterator->second->render(this->camera.getRect());
        ++iterator;
    }
}

void Presenter::handleBombSitesEvent(SDL_Event* event){
    std::map<std::string, std::shared_ptr<Draggable>>::iterator iterator = this->bombSites.begin();
    while (iterator != this->bombSites.end()){
        iterator->second->handleEvent(event, this->camera.getRect());
        ++iterator;
    }
}
void Presenter::handleSpawnSitesEvent(SDL_Event* event){
    std::map<std::string, std::shared_ptr<Draggable>>::iterator iterator = this->spawnSites.begin();
    while (iterator != this->spawnSites.end()){
        iterator->second->handleEvent(event, this->camera.getRect());
        ++iterator;
    }
}

void Presenter::centerCamera(){
    this->camera.centerCameraOnMouse(TILE_WIDTH, LEVEL_WIDTH, LEVEL_HEIGHT);
}

void Presenter::fillSize(std::vector<SDL_Rect>& vector){
    vector = {bombSites["A"]->getBox(), bombSites["B"]->getBox(), spawnSites["T"]->getBox(),
     spawnSites["CT"]->getBox()};
}

void Presenter::changeSizeOfSites(std::vector<int>& vector){
    this->bombSites["A"]->setWidthAndHeight(vector[0], vector[1]);
    this->bombSites["B"]->setWidthAndHeight(vector[2], vector[3]);
    this->spawnSites["T"]->setWidthAndHeight(vector[4], vector[5]);
    this->spawnSites["CT"]->setWidthAndHeight(vector[6], vector[7]);
}

SDL_Rect Presenter::getCameraBox(){
    return this->camera.getRect();
}