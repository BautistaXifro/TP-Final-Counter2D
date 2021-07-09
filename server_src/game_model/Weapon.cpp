#include "Weapon.h"
#include <cstdlib>

Weapon::Weapon(World *world, GameConfig &config, WeaponType type):owner(nullptr), world(world), type(type), config(config.getWeapon(type)), bullets(0){}


void Weapon::changeOwner(Player *newOwner){
    owner = newOwner;
}

World *Weapon::getWorld(){
    return world;
}

void Weapon::shootBullet(){
    Ray ray;

    //Le agrego un desvio a la bala
    float r = ((float) rand()) / (float) RAND_MAX;
    float spread = (2*r-1)*(config.at("spread"));
    std::array<float, 2> pos = owner->getPosition();
    ray.x = pos[0];
    ray.y = pos[1];
    ray.angle = owner->getAngle() + spread;
    Hittable *hit = nullptr;

    if (world->rayCast(ray, hit)){
        float actual_damage = calculateDamage(ray.distance);
        hit->recvDamage(actual_damage);
        world->addBullet(ray);
    }
}

WeaponType Weapon::getType(){
    return type;
}

void Weapon::toggle(){
    if (bullets > 0){
        shootBullet();
        bullets--;
    }
}

float Weapon::calculateDamage(float distance){
    //Calculo el daño entre el min y max
    float r = ((float) rand()) / (float) RAND_MAX;
    float damage = config.at("minDamage") + (r * (config.at("maxDamage") - config.at("minDamage")));
    //El daño disminuye con la distancia
    damage *= 1/(distance*config.at("falloff")+1);

    return damage;
}

void Weapon::reload(){
    bullets = config.at("capacity");
}
