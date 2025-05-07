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

        Load nodeLoad;
        nodeLoad.x = nodeData["load"][0].get<double>();
        nodeLoad.y = nodeData["load"][1].get<double>();
        nodeLoad.z = nodeData["load"][2].get<double>();

        Constraint nodeConstraint;
        nodeConstraint.x = nodeData["constraint"][0].get<int>();
        nodeConstraint.y = nodeData["constraint"][1].get<int>();
        nodeConstraint.z = nodeData["constraint"][2].get<int>();

        Nodes nnode(
            nodeData["id"],
            nodePose,
            nodeLoad,
            nodeConstraint
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
    
