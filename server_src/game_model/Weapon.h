#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "World.h"
#include "Player.h"
#include "../../common_src/WeaponType.h"
#include "GameConfig.h"
#include <map>
#include <string>

class Player;
class World;

class Weapon{
    protected:
        Player *owner;
        World *world;
        WeaponType type;
        std::map<std::string, float> config;

        virtual float calculateDamage(float distance);
    public:
        Weapon(World *world, GameConfig &config, WeaponType type);
        void changeOwner(Player *newOwner);
        World *getWorld();
        WeaponType getType();
        virtual void toggle();
        void shootBullet();
        virtual ~Weapon() = default;
};

#endif
