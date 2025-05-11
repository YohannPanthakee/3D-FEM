#include "material.h"

Materials::Materials(const std::string name, 
                double youngs_modulus, 
                double cross_section_area)
                
:name(name), youngs_modulus(youngs_modulus), cross_section_area(cross_section_area) {}

Properties Materials::getMaterial(){
    return Properties{youngs_modulus, cross_section_area, name};
}
