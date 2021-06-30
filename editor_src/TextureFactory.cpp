#include "TextureFactory.h"
#include "yaml-cpp/yaml.h"
#include <utility>
#include <stdio.h>

void TextureFactory::unmarshalTextures(char *yamlFile, TextureMap& map){
    YAML::Node yaml_map = YAML::LoadFile(yamlFile);

    YAML::Node yaml_keys = yaml_map["textureNumber"];
    YAML::Node yaml_paths = yaml_map["texturePaths"];

    std::vector<int> keys;
    std::vector<std::string> paths;

    for (YAML::iterator it = yaml_keys.begin(); it != yaml_keys.end(); it++) {
        keys.push_back(it->as<int>());
    }

    for (YAML::iterator it = yaml_paths.begin(); it != yaml_paths.end(); it++){
        paths.push_back(it->as<std::string>());
    }

    for (int i = 0; i < keys.size(); i++){
        map.insert(keys[i], paths[i]);
    }
}

void TextureFactory::unmarshalMap(const char *yamlFile, TextureMap& map, std::vector<std::unique_ptr<SdlTexture>>& textures, SdlRenderer& renderer){
    //Open the map
    YAML::Node yaml_map = YAML::LoadFile(yamlFile);

    //Initialize the objects
    YAML::Node textureNumbers = yaml_map["map"];
    for (YAML::iterator it = textureNumbers.begin(); it != textureNumbers.end(); it++){
        int type = it->as<int>();
        std::string path = map[type];
        textures.emplace_back(new SdlTexture(renderer, path, type));
    }
}

void TextureFactory::createMap(TextureMap& map, std::vector<std::unique_ptr<SdlTexture>>& textures, SdlRenderer& renderer){
    for (int i = 0; i < 192; i++){
        textures.emplace_back(new SdlTexture(renderer, map[0], 0));
    }
}