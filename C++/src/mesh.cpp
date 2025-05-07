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
        Position nodePose;
        nodePose.x = nodeData["pos"][0].get<double>();
        nodePose.y = nodeData["pos"][1].get<double>();
        nodePose.z = nodeData["pos"][2].get<double>();

        std::cout << "Node ID: " << nodeData["id"];
        std::cout << " NodePose - x: " << nodePose.x;
        std::cout << " NodePose - y: " << nodePose.y;
        std::cout << std::endl;


        Nodes nnode(
            nodeData["id"],
            nodePose,
            std::array<double, 3>{nodeData["load"][0], nodeData["load"][1], nodeData["load"][2]},
            std::array<int, 3>{nodeData["constraint"][0], nodeData["constraint"][1], nodeData["constraint"][2]}
        );
        node.insert({nodeData["id"], nnode});
    }

    // Elements
    for (const auto& elemData : data["elements"]) {
        Elements eelement(
            elemData["id"],
            getNodeByID(elemData["node_ids"][0]),
            getNodeByID(elemData["node_ids"][1]),
            elemData["material_name"]
        );
        element.insert({elemData["id"], eelement});
    }


    // Materials
    for (const auto& matData : data["materials"]) {
        Materials mmaterial(
            matData["name"], 
            matData["properties"]["youngs_modulus"], 
            matData["properties"]["cross_sectional_area"]
        );
        material.insert({matData["name"], mmaterial});
    }

}

Nodes Mesh::getNodeByID(int target_node_id)
{
    return node.at(target_node_id);
}


Elements Mesh::getElementByID(int target_element_id)
{
    return element.at(target_element_id);
}
    
