#include "GameProxy.h"
#include "WorldParser.h"
#include "../game_model/Rifle.h"
#include "../../common_src/Utils.h"
#include "../game_model/Bomb.h"
#include <utility>

#include <list>
#include <map>

GameProxy::GameProxy(const std::string &yaml_path, GameConfig &config): config(config){
    WorldParser parser(yaml_path);

    parser.get_size(mapInfo.length, mapInfo.height);

    world = new World(mapInfo.length, mapInfo.height, config);

    for (auto b: parser.get_boxes()){
        world->addBox(b[0], b[1]);
    }

    for (int t: parser.get_tiles()){
        mapInfo.tiles.push_back((uint8_t) t);
    }

    mapInfo.bombSites = parser.get_sites();
    mapInfo.spawnSites = parser.get_spawn();

    for (const RectArea &r: mapInfo.bombSites){
        world->addSite(r);
    }

    world->addDrop(new Rifle(world, world->config), 5.5f, 5.5f);

    world->addDrop(new Bomb(world, world->config), mapInfo.spawnSites[0].x, mapInfo.spawnSites[0].y);
}

MapInfo GameProxy::getMapInfo(){
    return mapInfo;
}

CompleteModelInfo GameProxy::getModelInfo(){
    CompleteModelInfo info;
    std::array<float, 2> pos;
    std::vector<Player> &players = world->getPlayers();
    for (const Player &p: players){
            You you;
            you.dead = p.isDead();
            if (!you.dead){
                pos = p.getPosition();
                you.pos.x = pos[0];
                you.pos.y = pos[1];
                you.angle = p.getAngle();
                you.health = p.getHealth();
                you.weapon = p.getWeaponType();
                you.shot = p.shot;
                you.team = p.getTeam();
                you.ammo = p.getAmmo();
            }
            info.players.push_back(you);
    }

    for (Ray &ray: world->getBullets()){
        Bullet b;
        b.pos.x = ray.x;
        b.pos.y = ray.y;
        if (ray.angle < 0){
            b.angle = ray.angle + 6.2832; //Le sumo 2PI
        } else {
            b.angle = ray.angle; 
        }
        b.distance = ray.distance;
        info.bullets.push_back(b);
    }

    for (Drop *drop : world->getDrops()){
        ProtDrop d;
        d.pos.x = drop->getPosition()[0];
        d.pos.y = drop->getPosition()[1];
        d.type = drop->getWeapon()->getType();
        info.drops.push_back(d);
    }

    info.game_ended = ended();

    info.bomb = world->getBomb();

    return info;
}

void GameProxy::step(float delta){
    world->step(delta);
}

void GameProxy::createPlayer(Team team){
    if (team == TERROR){
        world->createPlayer(mapInfo.spawnSites[0], team);
    } else {
        world->createPlayer(mapInfo.spawnSites[1], team);
    }
}

void GameProxy::toggleMovement(int id, Direction direction){
    world->getPlayers()[id].toggleMovement(direction);
}

void GameProxy::setAngle(int id, float angle){
    world->getPlayers()[id].setAngle(angle);
}

void GameProxy::toggleWeapon(int id){
    world->getPlayers()[id].toggleWeapon();
}

void GameProxy::reloadWeapon(int id){
    world->getPlayers()[id].reloadWeapon();
}

void GameProxy::changeWeapon(int id, WeaponSlot slot){
    world->getPlayers()[id].changeWeapon(slot);
}

void GameProxy::dropWeapon(int id){
    world->getPlayers()[id].dropWeapon();
}


bool GameProxy::ended(){
    if (world->getTime() > config.getGame().at("roundTime") || world->bombExploded() || world->bombDefused()){
        return true;
    }

    int alive_players = 0;
    for (const Player &p: world->getPlayers()){
        if (!p.isDead()){
            alive_players++;
        }
    }

    return alive_players <= 1;
}

GameProxy::~GameProxy(){
    delete world;
}

void GameProxy::clearFrameEvents(){
    world->clearBullets();
    for (Player &p: world->getPlayers()){
        p.shot = false;
    }
}

void GameProxy::toggleDefuse(int id){
    world->getPlayers()[id].toggleDefuse();
}