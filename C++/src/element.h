#ifndef ELEMENT_H
#define ELEMENT_H

#include <array>
#include <iostream>
#include <cmath>
#include "node.h"
#include "material.h"

class Elements {
    
    int id;
    double length, angle = {};
    
    Nodes start_node;
    Nodes end_node;
    Materials material;

    double mat_constant = {};// material constatant of the element
    double stress_constant = {}; // stress material constatant of the element

public:

    Elements(int id, 
            const Nodes start_node, 
            const Nodes end_node, 
            const Materials material);
    
    int getElementID();

    double getStartPoseX();
    double getStartPoseY();
    double getStartPoseZ();

    double getEndPoseX();
    double getEndPoseY();
    double getEndPoseZ();

    double getElementLength();
    double getElementAngle();

    double getMatConstant();
    double getMatStressConstant();

    //std::string getElementMaterial();
    
};

#endif 