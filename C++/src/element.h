#ifndef ELEMENT_H
#define ELEMENT_H

//#include <vector>
#include <array>
#include <iostream>
#include <cmath>
#include "node.h"

class Elements {
public:
    int id;
    //std::array<int, 2> node_ids;
    std::string material_name;
    double length, angle = {};

    std::array<Nodes, 2> node_ids;


    Elements(int id, 
            int node1, 
            int node2, 
            const std::string& material_name);
    

    Elements(int id, 
            const Nodes& node1, 
            const Nodes& node2, 
            const std::string& material_name);
};

#endif 