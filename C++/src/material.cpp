#include "material.h"

Materials::Materials(const std::string name, 
                double youngs_modulus, 
                double cross_sectional_area)
                
:name(name), youngs_modulus(youngs_modulus), cross_sectional_area(cross_sectional_area) {}

double Materials::getMatYMOD(){
    return youngs_modulus;
}

double Materials::getMatCSA(){
    return cross_sectional_area;
}


std::string Materials::getMatName(){
    return name;
}
