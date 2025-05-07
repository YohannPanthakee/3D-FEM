#ifndef MATERIAL_H
#define MATERIAL_H


#include <iostream>

class Materials {

        std::string name;
        double youngs_modulus;
        double cross_sectional_area;

public:
        Materials(const std::string name, 
            double youngs_modulus, 
            double cross_sectional_area);

        double getMatYMOD();
        double getMatCSA();
        std::string getMatName();
};


#endif 