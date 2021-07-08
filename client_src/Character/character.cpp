#include "character.h"
#include "../Events/gameMath.h"
#include <utility>


#define PHASE_SHIFT 90
const SDL_Rect SRC_KNIFE = { 0, 0, 32, 32};
const SDL_Rect SRC_BIG_GUN = { 0, 64, 32, 32};
const SDL_Rect SRC_DEFUSER = { 32, 32, 32, 32};
const SDL_Rect SRC_PISTOL = {32, 32, 32, 32};

Character::Character(PlayerInfo player, SdlTexture& texture, Weapon weapon):
    player(player), texture(texture), weapon(std::move(weapon)){}


SDL_Rect Character::getSourceTexture(){
    if (this->player.weapon.type == KNIFE) {
        return SRC_KNIFE;
    } else if (this->player.weapon.type == RIFLE || this->player.weapon.type == SHOTGUN || this->player.weapon.type == SNIPER) {
        return SRC_BIG_GUN;
    } else if (this->player.weapon.type == DEFUSER) {
        return SRC_DEFUSER;
    } else if (this->player.weapon.type == PISTOL) {
        return SRC_PISTOL;
    }
}

void Character::render(int camX, int camY){
    SDL_Rect dst = {this->player.pos.x - camX - this->player.size.w/2, this->player.pos.y - camY - this->player.size.h/2, this->player.size.w, this->player.size.h};
    SDL_Rect src = getSourceTexture();

    this->weapon.render(this->player.degrees, this->player.shooting, this->player.pos);
    this->texture.render(dst.x, dst.y, dst.w, dst.h, &src, this->player.degrees + PHASE_SHIFT);
}


void Character::update(PlayerInfo info, Weapon weapon){
    if (info.dead) return;
    this->player.dead = info.dead;

    this->weapon = std::move(weapon);

    this->player.degrees = info.degrees;
    this->player.weapon = info.weapon;
    this->player.pos.x = info.pos.x;
    this->player.pos.y = info.pos.y;
    this->player.size.w = info.size.w;
    this->player.size.h = info.size.h;
    this->weapon.update(info.weapon);
}


bool Character::isDead(){return this->player.dead;}
int Character::getPosY(){return this->player.pos.y;}
int Character::getPosX(){return this->player.pos.x;}
SDL_Rect Character::getRect(){return {this->player.pos.x, this->player.pos.x, this->player.size.w, this->player.size.h};}
float Character::getDegrees(){return this->player.degrees;}

Character& Character::operator=(Character&& other){
    this->texture = other.texture;
    this->player = other.player;
    this->weapon = std::move(other.weapon);
    return *this;
}

Character::Character(Character&& other):texture(other.texture), weapon(std::move(other.weapon)){
    this->player = other.player;
}
