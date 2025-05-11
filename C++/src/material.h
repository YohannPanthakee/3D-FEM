#ifndef MATERIAL_H
#define MATERIAL_H


#include <iostream>

struct Properties {
    double youngs_modulus;
    double cross_section_area;
    std::string name;
};



class Materials {

        std::string name;
        double youngs_modulus;
        double cross_section_area;

public:
        Materials(const std::string name, 
            double youngs_modulus, 
            double cross_section_area);

        Properties getMaterial();
};


#endif 

