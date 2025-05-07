#include <stdlib.h>
#include <iostream>
#include "src/mesh.h"

//#include <Eigen/Dense>
//#include <matplotlibcpp.h>
//namespace plt = matplotlibcpp;


int main() {
    // Declare Class
    Mesh mesh;
 
    std::string f = "/home/yohann/projects/3D-FEM/C++/tests/Data.json";
    
    mesh.loadFromJson(f);

    //std::cout << "Loaded: " << mesh.node.size() << " Mesh nodes\n";
    //std::cout << "Loaded: " << mesh.element.size() << " Elements \n";


    std::string material_name = "Aluminium";  // Example name of material
    int elemID = 1;  // Example element ID
    int nodeID = 1;  // Example Node ID

    const Materials& mat = mesh.material.at(material_name);
    std::cout << "Material Name: " << mat.name << std::endl;
    std::cout << "Young's Modulus: " << mat.youngs_modulus << std::endl;
    std::cout << "Cross-sectional Area: " << mat.cross_sectional_area << std::endl;

    const Elements& ele = mesh.element.at(elemID);
    //std::cout << "id: " << ele.id << std::endl;
    //std::cout << "node_ids: " << ele.node_ids[0] << std::endl;
    //std::cout << "length: " << ele.length << std::endl;
    //std::cout << "Angle: " << ele.angle << std::endl;
    //std::cout << "material_name: " << ele.material_name << std::endl;

    //const Nodes& node = mesh.node.at(nodeID);
    //std::cout << "id: " << node.id << std::endl;

}   



