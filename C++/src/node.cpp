#include "node.h"

Nodes::Nodes(int id,
        Position pose,
        Load load,
        Constraint constraint)
: id(id), pose(pose), load(load), constraint(constraint) {}

int Nodes::getID(){
    return id;
}


Position Nodes::getPose()
{
    return pose;
}

Load Nodes::getLoad()
{
    return load;
}

Constraint Nodes::getConstraint()
{
    return constraint;
}






