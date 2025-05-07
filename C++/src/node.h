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

        double getLoadX();
        double getLoadY();
        double getLoadZ();

        double getPoseX();
        double getPoseY();
        double getPoseZ();

        int getConstraintX();
        int getConstraintY();
        int getConstraintZ();
    
        int getID();
    };
#endif

