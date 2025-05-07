#include <stdlib.h>
#include <iostream>
#include "src/mesh.h"

#include <Eigen/Dense>
//#include <matplotlibcpp.h>
//namespace plt = matplotlibcpp;


int main() {
    // Declare Class
    Mesh mesh;
 
    std::string f = "/home/yohann/projects/3D-FEM/C++/tests/Data.json";
    
    mesh.loadFromJson(f);

    std::string material_name = "Aluminium";  // Example name of material
    int elemID = 1;  // Example element ID
    int nodeID = 1;  // Example Node ID

    Materials mat = mesh.material.at(material_name);
    std::cout << "Material Name: " << mat.getMatName() << std::endl;
    std::cout << "Young's Modulus: " << mat.getMatYMOD() << std::endl;
    std::cout << "Cross-sectional Area: " << mat.getMatCSA() << std::endl;

    Elements ele = mesh.element.at(elemID);
    std::cout << "Element Id: " << ele.getElementID() << std::endl;
    std::cout << " Element Start Node Pos x: " << ele.getStartPoseX() << std::endl;
    std::cout << " Element Start Node Pos y: " << ele.getStartPoseY() << std::endl;
    std::cout << " Element Start Node Pos z: " << ele.getStartPoseZ() << std::endl;
    std::cout << " Element End Node Pos x: " << ele.getEndPoseX() << std::endl;
    std::cout << " Element End Node Pos y: " << ele.getEndPoseY() << std::endl;
    std::cout << " Element End Node Pos z: " << ele.getEndPoseZ() << std::endl;
    std::cout << " length: " << ele.getElementLength() << std::endl;
    std::cout << " Angle: " << ele.getElementAngle() << std::endl;
    std::cout << " material Constant: " << ele.getMatConstant() << std::endl;
    std::cout << " material Stress Constant: " << ele.getMatStressConstant() << std::endl;

    Nodes node = mesh.node.at(nodeID);
    std::cout << "Node Id: " << node.getID() << std::endl;
    std::cout << " Node Load X: " << node.getLoadX() << std::endl;
    std::cout << " Node Load Y: " << node.getLoadY() << std::endl;
    std::cout << " Node Load Z: " << node.getLoadZ() << std::endl;
    std::cout << " Node Constraint X: " << node.getConstraintX() << std::endl;
    std::cout << " Node Constraint Y: " << node.getConstraintY() << std::endl;
    std::cout << " Node Constraint Z: " << node.getConstraintZ() << std::endl;

}   



