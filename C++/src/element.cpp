#include "element.h"


Elements::Elements(int id, Nodes start_node, Nodes end_node, Materials material)
: id(id), start_node(start_node),end_node(end_node), material(material)
    {
        Delta delta;
        Position start_pos = start_node.getPose();
        Position end_pos = end_node.getPose();
        Properties properties = material.getMaterial();

        delta.length.x = start_pos.x - end_pos.x;
        delta.length.y = start_pos.y - end_pos.y;
        delta.length.z = start_pos.z - end_pos.z;

        // Calculating length and angle.
        delta.elementLength = std::hypot(delta.length.x, delta.length.y, delta.length.z);
        delta.elementAngle = std::atan2(delta.length.y, delta.length.x);
    
        mat_constant = (properties.youngs_modulus/properties.cross_section_area)/ delta.elementLength;
        stress_constant = properties.youngs_modulus/ delta.elementLength;

        delta.angle.cx = (delta.length.x/ delta.elementLength);
        delta.angle.cy = (delta.length.y/ delta.elementLength);
        delta.angle.cz = (delta.length.z/ delta.elementLength);

        delta.angle.cxy = delta.angle.cx * delta.angle.cy; 
        delta.angle.cxz = delta.angle.cx * delta.angle.cz;   
        delta.angle.cyz = delta.angle.cy * delta.angle.cz;  

        fill_local_stiffness(delta, mat_constant);

        fill_DOF_array(start_node.getID(),end_node.getID());
    }




 

   
void Elements::fill_DOF_array(int node_id_1, int node_id_2) {
    for (size_t i = 0; i < 6; ++i) {
        if (i < 3){
            DOF_array[i] = static_cast<int>( (node_id_1-1)*3 + (i % 3) + 1);
        }
        else{
            DOF_array[i] = static_cast<int>( (node_id_2-1)*3 + (i % 3) + 1);
        }
    }
}


void Elements::fill_local_stiffness(Delta delta, double mat_constant) {

    matrix(0,0) =  std::pow(delta.angle.cx,2);
    matrix(1,0) =  delta.angle.cxy; 
    matrix(2,0) =  delta.angle.cxz; 
    matrix(3,0) = -std::pow(delta.angle.cx,2); 
    matrix(4,0) = -delta.angle.cxy; 
    matrix(5,0) = -delta.angle.cxz; 

    matrix(0,1) =  delta.angle.cxy;
    matrix(1,1) =  std::pow(delta.angle.cy,2);
    matrix(2,1) =  delta.angle.cyz;
    matrix(3,1) = -delta.angle.cxy;
    matrix(4,1) = -std::pow(delta.angle.cy,2); 
    matrix(5,1) = -delta.angle.cyz;

    matrix(0,2) =  delta.angle.cxz;
    matrix(1,2) =  delta.angle.cyz;
    matrix(2,2) =  std::pow(delta.angle.cz,2);
    matrix(3,2) = -delta.angle.cxz;
    matrix(4,2) = -delta.angle.cyz;
    matrix(5,2) = -std::pow(delta.angle.cz,2); 

    matrix(0,3) = -std::pow(delta.angle.cx,2);
    matrix(1,3) = -delta.angle.cxy; 
    matrix(2,3) = -delta.angle.cxz;
    matrix(3,3) =  std::pow(delta.angle.cx,2); 
    matrix(4,3) =  delta.angle.cxy; 
    matrix(5,3) =  delta.angle.cxz; 

    matrix(0,4) = -delta.angle.cxy;
    matrix(1,4) = -std::pow(delta.angle.cy,2); 
    matrix(2,4) = -delta.angle.cyz; 
    matrix(3,4) =  delta.angle.cxy; 
    matrix(4,4) =  std::pow(delta.angle.cy,2); 
    matrix(5,4) =  delta.angle.cyz; 

    matrix(0,5) = -delta.angle.cxz;
    matrix(1,5) = -delta.angle.cyz;
    matrix(2,5) = -std::pow(delta.angle.cz,2); 
    matrix(3,5) =  delta.angle.cxz; 
    matrix(4,5) =  delta.angle.cyz; 
    matrix(5,5) =  std::pow(delta.angle.cz,2);
    
    matrix = matrix * mat_constant;

    // Print with format
    //Eigen::IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");
    //std::cout << "Formatted matrix:\n" << matrix.format(CleanFmt) << std::endl;
}

int Elements::getElementID(){
    return id;
}

double Elements::getMatConstant(){
    return mat_constant;
}

double Elements::getMatStressConstant(){
    return stress_constant;
}


