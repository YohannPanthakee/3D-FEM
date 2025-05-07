#ifndef MATERIAL_H
#define MATERIAL_H


#include <iostream>

class Materials {
    public:
        std::string name;
        double youngs_modulus;
        double cross_sectional_area;

        Materials(const std::string& name, 
            double E, 
            double A);
};


#endif 