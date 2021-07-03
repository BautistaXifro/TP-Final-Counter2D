#include "Pistol.h"

Pistol::Pistol(Player *owner, World *world)
:Weapon(owner, world, PISTOL_DAMAGE){}


void Pistol::toggle(){
    shootBullet(0);
}

float Pistol::calculateDamage(float distance){
    //TODO: Agregar perdida de daño con distancia y varianza random.
    return damage;
}
