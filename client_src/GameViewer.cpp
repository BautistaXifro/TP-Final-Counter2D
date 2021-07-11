#include "GameViewer.h"
#include <cstdio>

#define WINDOW_LABEL "Counter-Strike 2D"
#define PATH_POINTER "../../common_src/img/pointer.bmp"
#define PATH_FONT "../../common_src/img/digital-7.ttf"
#define SIZE_CROSSHAIR 25
#define MARGIN 15


const struct Color HUD_COLOR = {0xAD, 0x86, 0x33};
const struct Color FONDO_ARMA = {0xFF, 0x00, 0xFF};


GameViewer::GameViewer(int window_w, int window_h, LevelInfo level): window(WINDOW_LABEL, window_w, window_h),
    renderer(&window), 
    textureManager(renderer, level.tiles),
    cam(window_w, window_h),
    level(level),
    bullet(renderer){

    SDL_ShowCursor(SDL_DISABLE);
    loadWeapons();

    WeaponType mainType = level.mainPlayer.weapon.type;
    Weapon mainWeapon(*(this->textureManager.getWeaponOnPj(mainType)), *(this->textureManager.getWeaponAnim(mainType)), level.mainPlayer.weapon.size);
    this->mainPlayer = new MainCharacter( level.mainPlayer, *(this->textureManager.getSkin(CT1)), 
                std::move(CrossHair(SIZE_CROSSHAIR, SIZE_CROSSHAIR, std::move(SdlTexture(renderer, PATH_POINTER, FONDO_ARMA.r, FONDO_ARMA.g, FONDO_ARMA.b)))),
                std::move(Stencil(this->renderer, window_w, window_h)), mainWeapon);


    for (PlayerInfo player : level.players) {
        //crear cuchillo y cargarlo al personaje
        WeaponType type = player.weapon.type;
        Weapon weapon(*(this->textureManager.getWeaponOnPj(type)), *(this->textureManager.getWeaponAnim(type)), player.weapon.size);
        this->players.push_back(Character(player, *(this->textureManager.getSkin(CT1)), weapon));
    }
}

GameViewer::~GameViewer(){
    delete this->mainPlayer;
}

void GameViewer::loadWeapons(){


}



// ESTO EN LA VERSION FINAL NO TIENE QUE IR
void GameViewer::renderPlayers(Coordenada cam) {
    for (auto it = this->players.begin(); it != this->players.end(); it++){
        if (!it->isDead()) {
            it->render(cam.x, cam.y);

            PlayerInfo player = it->getInfo();
            for (PlayerEffect effect : player.sounds) {
                this->sounds.playPlayerSound(effect);
            }
            if (player.shooting) {
                this->sounds.playWeaponSound(player.weapon.sound);
            }
        }
    }
    
}

void GameViewer::renderShots(Coordenada cam){
    for (BulletInfo bul : level.bullets) {
        this->bullet.setTrajectory(bul.pos, bul.dst);
        this->bullet.render(cam);
    }
}

void GameViewer::renderWeapons(Coordenada cam){
    for(DropInfo wp : level.drops){
        this->textureManager.getWeaponOnFloor(wp.type)->render(wp.pos.x - cam.x, wp.pos.y - cam.y, wp.size.w, wp.size.h);
    }
}

void GameViewer::renderMap(Coordenada cam){
    int max = (int)this->level.tiles.size();
    for (int i = 0; i < max; i++) {
        uint8_t tile = this->level.tiles[i].id;
        Coordenada pos = this->level.tiles[i].pos;
        Size size = this->level.tiles[i].size;
        this->textureManager.getTiles(tile)->render(pos.x-cam.x, pos.y-cam.y, size.w, size.h);
    }
}

void GameViewer::renderMainPlayer(Coordenada cam){
    this->mainPlayer->render(cam);
}


void GameViewer::renderHud(){
    char ammoText[100];
    sprintf(ammoText, "Ammo: %d", this->level.mainPlayer.ammo);
    SDL_Point dst = {this->cam.getWidth() - MARGIN, this->cam.getHeight() - MARGIN};

    SdlTexture ammo(this->renderer, PATH_FONT, 30, ammoText, HUD_COLOR.r, HUD_COLOR.g, HUD_COLOR.b );
    ammo.setAlpha(100);
    ammo.setBlendMode(SDL_BLENDMODE_BLEND);
    ammo.render(dst.x - ammo.getWidth(), dst.y - ammo.getHeight());
}

void GameViewer::render(){

    renderer.setDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
    renderer.clear();

    Coordenada cam = {this->cam.getPosX(), this->cam.getPosY()};
    
    renderMap(cam);
    renderShots(cam);
    renderPlayers(cam);
    renderWeapons(cam);
    renderMainPlayer(cam);
    //renderHud();

    renderer.updateScreen();
}



void GameViewer::update(LevelInfo level){
    this->level = level;

    WeaponType mainType = level.mainPlayer.weapon.type;

    Weapon mainWeapon(*(this->textureManager.getWeaponOnPj(mainType)), *(this->textureManager.getWeaponAnim(mainType)), level.mainPlayer.weapon.size);
    this->mainPlayer->update(level.mainPlayer, mainWeapon);

    this->level.drops.clear();
    this->level.drops.insert(this->level.drops.begin(), level.drops.begin(), level.drops.end());

    this->level.players.clear();
    this->level.players.insert(this->level.players.begin(), level.players.begin(), level.players.end());
    
    this->level.bullets.clear();
    this->level.bullets.insert(this->level.bullets.begin(), level.bullets.begin(), level.bullets.end());

    auto it = this->players.begin();
    auto end = this->players.end();
    for (PlayerInfo player : this->level.players) {
        if (!player.dead && it != end) {
            WeaponType type = player.weapon.type;
            Weapon weapon(*(this->textureManager.getWeaponOnPj(type)), *(this->textureManager.getWeaponAnim(type)), player.weapon.size);
            it->update(player, weapon);
        }
    }
    // revisar el constructor por movimiento del character

    this->cam.centerCamera(level.mainPlayer.pos);
    this->cam.keepInBounds(level.width, level.height);
    
}
void GameViewer::setCrossHair(Coordenada pos){this->mainPlayer->setCrossHair(pos);}

Coordenada GameViewer::mainPlayerRelativePos(){
    return {this->mainPlayer->getPosX() - this->cam.getPosX(),
            this->mainPlayer->getPosY() - this->cam.getPosY()};
}