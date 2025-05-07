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
    
    const Nodes start_node;
    const Nodes end_node;

public:

    Elements(int id, 
            const Nodes& start_node, 
            const Nodes& end_node, 
            const std::string& material_name);
    
    double getStartPoseX();
    double getStartPoseY();
    double getStartPoseZ();

    int getElementID();
};

#endif 