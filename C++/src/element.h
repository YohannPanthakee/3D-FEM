#ifndef ELEMENT_H
#define ELEMENT_H

//#include <vector>
#include <array>
#include <iostream>

class Element {
public:
    int id;
    std::array<int, 2> node_ids;
    std::string material_name;

    Element(int id, 
            int node1, 
            int node2, 
            const std::string& material_name);
};

#endif 