#ifndef __LEVEL_INFO_H__
#define __LEVEL_INFO_H__

#include <list>
#include <vector>
#include "../../common_src/ModelInfo.h"
#include "SoundEffects.h"

struct Color {
    uint8_t r,g,b;
};

struct Coordinate {
    int x;
    int y;
};

struct Size {
    int w; 
    int h;
};

struct BoxInfo {
    Coordinate pos;
    Size size;
};

struct DropInfo {
    Coordinate pos;
    Size size;
    WeaponType type;
};

struct WeaponInfo {
    Coordinate pos;
    Size size;
    Coordinate posAnim;
    WeaponType type;
    WeaponEffect sound;
};

struct PlayerInfo {
    Coordinate pos;
    Size size;
    float degrees;
    bool shooting;
    bool dead;
    WeaponInfo weapon;
    std::list<PlayerEffect> sounds;
};

struct MainPlayerInfo: public PlayerInfo {
    float health;
    int ammo;
};

struct BulletInfo {
    Coordinate pos;
    Coordinate dst;
};

struct TileInfo {
    uint8_t id;
    Coordinate pos;
    Size size;
};

struct LevelInfo{
    Size size;
    
    std::vector<TileInfo> tiles;
    std::list<BoxInfo> bombSites;
    std::list<BoxInfo> spawnSites;

    MainPlayerInfo mainPlayer;
    std::list<DropInfo> drops;
    std::list<PlayerInfo> players;
    std::list<BulletInfo> bullets;
};

#endif