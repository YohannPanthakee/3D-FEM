#ifndef MESH_H
#define MESH_H

#include <nlohmann/json.hpp>
#include <unordered_map>

#include "node.h"
#include "element.h"
#include "material.h"


class Mesh {
    public:
        std::unordered_map<int, Nodes> node;
        std::unordered_map<int, Elements> element;
        std::unordered_map<std::string, Materials> material;

        void loadFromJson(const std::string& filename);
        Nodes getNodeByID(int target_node_id);
        Elements getElementByID(int target_element_id);
        Materials getMaterialByName(std::string target_material_name);


    };

#endif


