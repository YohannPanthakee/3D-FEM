#include <stdlib.h>
#include <iostream>
#include "src/mesh.h"
#include <Eigen/Dense>
#include "src/utils/logger.h"

//#include <matplotlibcpp.h>
//namespace plt = matplotlibcpp;


int main() {
    // Declare Class
    Mesh mesh;
    
    //Logger::getInstance().setLogFile("app.log");
    //Logger::getInstance().log(LogLevel::INFO, "Application started");
    //Logger::getInstance().log(LogLevel::DEBUG, "Debugging step...");
    //Logger::getInstance().log(LogLevel::ERROR, "Something went wrong!");
 
    std::string f = "/home/yohann/projects/3D-FEM/C++/tests/Data.json";
    
    mesh.loadFromJson(f);

    std::string material_name = "Steel";  // Example name of material
    int elemID = 1;  // Example element ID
    int nodeID = 1;  // Example Node ID

    Materials mat = mesh.material.at(material_name);
    auto property = mat.getMaterial();
    std::cout << "Material Name: " << property.name << std::endl;
    std::cout << "Young's Modulus: " << property.youngs_modulus << std::endl;
    std::cout << "Cross-sectional Area: " << property.cross_section_area << std::endl;

    Elements ele = mesh.element.at(elemID);
    std::cout << "Element Id: " << ele.getElementID() << std::endl;
    //std::cout << " Element Start Node Pos x: " << ele.getStartPoseX() << std::endl;
    //std::cout << " Element Start Node Pos y: " << ele.getStartPoseY() << std::endl;
    //std::cout << " Element Start Node Pos z: " << ele.getStartPoseZ() << std::endl;
    //std::cout << " Element End Node Pos x: " << ele.getEndPoseX() << std::endl;
    //std::cout << " Element End Node Pos y: " << ele.getEndPoseY() << std::endl;
    //std::cout << " Element End Node Pos z: " << ele.getEndPoseZ() << std::endl;
    //std::cout << " length: " << ele.getElementLength() << std::endl;
    //std::cout << " Angle: " << ele.getElementAngle() << std::endl;
    std::cout << " material Constant: " << ele.getMatConstant() << std::endl;
    std::cout << " material Stress Constant: " << ele.getMatStressConstant() << std::endl;

    
    
    Nodes node = mesh.node.at(nodeID); // Calling Node based on ID
    auto load = node.getLoad(); // Acessing Load Struct
    auto constraint = node.getConstraint(); // Acessing Constraint Struct

    std::cout << "Node Id: " << node.getID() << std::endl;
    std::cout << " Node Load X: " << load.x << std::endl;
    std::cout << " Node Load Y: " << load.y << std::endl;
    std::cout << " Node Load Z: " << load.z << std::endl;
    std::cout << " Node Constraint X: " << constraint.x << std::endl;
    std::cout << " Node Constraint Y: " << constraint.y << std::endl;
    std::cout << " Node Constraint Z: " << constraint.z << std::endl;

}   



