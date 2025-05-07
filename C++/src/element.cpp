#include "element.h"

Elements::Elements(int id, const Nodes& start_node, const Nodes& end_node, const std::string& material_name)
: id(id), start_node(start_node),end_node(end_node), material_name(material_name)
    {
        // Calculating length and angle.
        length = std::hypot(
            start_node.pose.x - end_node.pose.x,
            start_node.pose.y - end_node.pose.y,
            start_node.pose.z - end_node.pose.z);
        
        // // Debug
        // std::cout << "Element ID: " << id ;
        // std::cout << " Element Length: " << length << std::endl;
    }


double Elements::getStartPoseX() 
{
    return start_node.pose.x;
}

double Elements::getStartPoseY() 
{
    return start_node.pose.y;
}

double Elements::getStartPoseZ() 
{
    return start_node.pose.z;
}

int Elements::getElementID() 
{
    return id;
}