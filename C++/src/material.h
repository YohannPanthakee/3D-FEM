#ifndef MATERIAL_H
#define MATERIAL_H


#include <iostream>

class Material {
    public:
        std::string name;
        double youngs_modulus;
        double cross_sectional_area;

        Material(const std::string& name, 
            double E, 
            double A);
};


#endif 