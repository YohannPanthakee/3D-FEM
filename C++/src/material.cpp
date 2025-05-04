#include "material.h"

Material::Material(const std::string& name, 
                double E, 
                double A)
                
    : name(name), youngs_modulus(E), cross_sectional_area(A) {}