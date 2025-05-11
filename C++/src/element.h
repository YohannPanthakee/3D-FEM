#ifndef ELEMENT_H
#define ELEMENT_H

#include <array>
#include <iostream>
#include <cmath>
#include "node.h"
#include "material.h"


#include <Eigen/Dense>

struct Delta {

    struct Angle {
        double cx;
        double cy;
        double cz;

        double cxy;
        double cxz;
        double cyz;

    };

    struct Length {
        double x;
        double y;
        double z;
        
    };

    double elementLength;
    double elementAngle;

    // Member variables for Delta
    Angle angle;
    Length length;
};

class Elements {
    
    int id;

    Nodes start_node;
    Nodes end_node;
    Materials material;

    double mat_constant = {};// material constatant of the element
    double stress_constant = {}; // stress material constatant of the element

    std::array<int,6> DOF_array = {};

    Eigen::Matrix<double, 6, 6> matrix;

public:

    Elements(int id, 
            const Nodes start_node, 
            const Nodes end_node, 
            const Materials material);
    
    int getElementID();

    double getElementLength();
    double getElementAngle();

    double getMatConstant();
    double getMatStressConstant();

    void fill_DOF_array(int node_id_1, int node_id_2);
    
    void fill_local_stiffness(Delta delta, double mat_constant);

    
    
};

#endif 