#ifndef MESH_H
#define MESH_H

#include <nlohmann/json.hpp>
#include <unordered_map>

#include "node.h"
#include "element.h"
#include "material.h"


class Mesh {
    public:
        std::unordered_map<int, Node> nodes;
        std::unordered_map<int, Element> elements;
        std::unordered_map<std::string, Material> materials;

        void loadFromJson(const std::string& filename);
    };

#endif


