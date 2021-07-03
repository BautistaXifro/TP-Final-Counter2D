#ifndef _WORLD_PARSER_H_
#define _WORLD_PARSER_H_

#include "game_model/World.h"
#include "../common_src/MapInfo.h"
#include "yaml-cpp/yaml.h"
#include <stdint.h>
#include <string>
#include <list>

class WorldParser{
    private:
        YAML::Node mapYaml;

    public:
        explicit WorldParser(const std::string &yamlPath);
        void get_size(uint16_t &length, uint16_t &height);
        std::list<ProtBox> get_boxes();
};

#endif
