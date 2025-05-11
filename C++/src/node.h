#ifndef NODE_H
#define NODE_H

#include <array>

struct Position {
    double x;
    double y;
    double z;
};

struct Load {
    double x;
    double y;
    double z;
};

struct Constraint {
    double x;
    double y;
    double z;
};


class Nodes {
    
        int id;
        Position pose;
        Load load;
        Constraint constraint;
    
public:
        Nodes(int id, Position pose, Load load, Constraint constraint);


        Position getPose();
        Load getLoad();
        Constraint getConstraint();
    
        int getID();
    };
#endif

