#include <fstream>
#include <iostream>
#include "mesh.h"

using json = nlohmann::json;

void Mesh::loadFromJson(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    json data;
    file >> data;
    
    // Nodes
    for (const auto& nodeData : data["nodes"]) {
        Node node(
            nodeData["id"],
            std::array<double, 3>{nodeData["pos"][0], nodeData["pos"][1], nodeData["pos"][2]},
            std::array<double, 3>{nodeData["load"][0], nodeData["load"][1], nodeData["load"][2]},
            std::array<int, 3>{nodeData["constraint"][0], nodeData["constraint"][1], nodeData["constraint"][2]}
        );
        nodes.insert({nodeData["id"], node});
    }

    // Elements
    for (const auto& elem : data["elements"]) {
        Element element(
            elem["id"], 
            elem["node_ids"][0], 
            elem["node_ids"][1],
            elem["material_name"]
        );
        elements.insert({elem["id"], element});
    }


    // Materials
    for (const auto& mat : data["materials"]) {
        Material material(
            mat["name"], 
            mat["properties"]["youngs_modulus"], 
            mat["properties"]["cross_sectional_area"]
        );
        materials.insert({mat["name"], material});
    }

}
    
