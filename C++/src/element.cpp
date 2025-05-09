#include "element.h"

Elements::Elements(int id, Nodes start_node, Nodes end_node, Materials material)
: id(id), start_node(start_node),end_node(end_node), material(material)
    {
        delta_length deltaL;
        deltaL.x = start_node.getPoseX() - end_node.getPoseX();
        deltaL.y = start_node.getPoseY() - end_node.getPoseY();
        deltaL.z = start_node.getPoseZ() - end_node.getPoseZ();

        // Calculating length and angle.
        length = std::hypot(deltaL.x, deltaL.y, deltaL.x);
        angle = std::atan2(deltaL.y, deltaL.x);

        mat_constant = (material.getMatYMOD()/material.getMatCSA())/length;
        stress_constant = material.getMatYMOD()/length;

        delta_angle deltaA;
        deltaA.cx = (deltaL.x/length); // calculates the angle of the element in the x plane ≡ cos(theta)x
        deltaA.cy = (deltaL.x/length); // calculates the angle of the element in the y plane ≡ cos(theta)y
        deltaA.cz = (deltaL.x/length); // calculates the angle of the element in the z plane ≡ cos(theta)z

        deltaA.cxy = deltaA.cx * deltaA.cy; 
        deltaA.cxz = deltaA.cx * deltaA.cz;   
        deltaA.cyz = deltaA.cy * deltaA.cz;  

        //local_stiffness










        fill_DOF_array(start_node.getID(),end_node.getID());

        std::cout << "Array Elements ID " << id << ": ";
        for (int i = 0; i < 6; i++)
            std::cout << DOF_array[i] << " ";
        std::cout << std::endl;
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










double Elements::getStartPoseX(){
    return start_node.getPoseX();
}

double Elements::getStartPoseY(){
    return start_node.getPoseY();
}

double Elements::getStartPoseZ(){
    return start_node.getPoseZ();
}


double Elements::getEndPoseX(){
    return end_node.getPoseX();
}

double Elements::getEndPoseY(){
    return end_node.getPoseY();
}

double Elements::getEndPoseZ(){
    return end_node.getPoseZ();
}

double Elements::getElementLength(){
    return length;
}

double Elements::getElementAngle(){
    return angle;
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


