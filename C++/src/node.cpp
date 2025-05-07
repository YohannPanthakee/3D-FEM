#include "node.h"

Nodes::Nodes(int id,
        Position pose,
        Load load,
        Constraint constraint)
: id(id), pose(pose), load(load), constraint(constraint) {}

int Nodes::getID(){
    return id;
}


double Nodes::getLoadX() 
{
    return load.x;
}

double Nodes::getLoadY() 
{
    return load.y;
}

double Nodes::getLoadZ() 
{
    return load.z;
}




double Nodes::getPoseX() 
{
    return pose.x;
}

double Nodes::getPoseY() 
{
    return pose.y;
}

double Nodes::getPoseZ() 
{
    return pose.z;
}



int Nodes::getConstraintX() 
{
    return constraint.x;
}

int Nodes::getConstraintY() 
{
    return constraint.y;
}

int Nodes::getConstraintZ() 
{
    return constraint.z;
}




