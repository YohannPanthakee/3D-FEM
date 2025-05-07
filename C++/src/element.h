#ifndef ELEMENT_H
#define ELEMENT_H

//#include <vector>
#include <array>
#include <iostream>
#include <cmath>
#include "node.h"

class Elements {
    int id;
    std::string material_name;
    double length, angle = {};
    
    Nodes start_node;
    Nodes end_node;

public:

    Elements(int id, 
            const Nodes start_node, 
            const Nodes end_node, 
            const std::string material_name);
    
    int getElementID();

    double getStartPoseX();
    double getStartPoseY();
    double getStartPoseZ();

    double getEndPoseX();
    double getEndPoseY();
    double getEndPoseZ();


    double getElementLength();
    double getElementAngle();
    std::string getElementMaterial();
    
};

#endif 