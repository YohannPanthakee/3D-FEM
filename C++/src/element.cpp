#include "element.h"

Elements::Elements(int id, Nodes start_node, Nodes end_node, Materials material)
: id(id), start_node(start_node),end_node(end_node), material(material)
    {
        // Calculating length and angle.
        length = std::hypot(
            start_node.getPoseX() - end_node.getPoseX(),
            start_node.getPoseY() - end_node.getPoseY(),
            start_node.getPoseZ() - end_node.getPoseZ());

        angle = std::atan2(
                start_node.getPoseY() - end_node.getPoseY(),
                start_node.getPoseX() - end_node.getPoseX());
        
        mat_constant = (material.getMatYMOD()/material.getMatCSA())/length;
        stress_constant = material.getMatYMOD()/length;
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

//std::string Elements::getElementMaterial(){
//    return material.getMatName();
//};
