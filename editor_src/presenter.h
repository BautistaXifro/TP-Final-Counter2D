#ifndef __PRESENTER_H__
#define __PRESENTER_H__
#include <SDL2/SDL.h>
#include <memory>
#include <map>
#include <vector>
#include "../client_src/Character/camera.h"
#include "MenueManager.h"
class Presenter{
    private:
        MenueManager& menueManager;

        Camera camera;
    public:
        Presenter(MenueManager& menueManager, int screenW, int screenH);
        virtual void render() = 0;
        virtual void handleEvents(SDL_Event* event, SdlRenderer& renderer) = 0;
        virtual std::string getTitle() = 0;
        virtual void aceptChanges(){};
        virtual bool finish() = 0;

        void renderTextures();
        void renderBombSites();
        void renderSpawnSites();
        void renderMapTextures();
        void centerCamera();
        void handleBombSitesEvent(SDL_Event* event);
        void handleSpawnSitesEvent(SDL_Event* event);
        void handleSelectTexture(SDL_Event* event);
        void fillSize(std::vector<SDL_Rect>& vector);
        void changeSizeOfSites(std::vector<float>& vector);
        void changeTexture();
        void createMap();
        void editMap(const std::string& mapID);
        void needToSave();
        void saveMap();

        SDL_Rect getCameraBox();
        int getMapWidth();
        int getMapHeight();
        int getTextureMapSize();
        int getTexturesSize();
        int getTileSize();
        int getScreenWidth();
        int getScreenHeight();
};
#endif
