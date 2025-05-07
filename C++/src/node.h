#ifndef NODE_H
#define NODE_H


#include <array>

struct Position {
    double x;
    double y;
    double z;
};

class Nodes {
    public:
        int id;
        // Position pose;
        std::array<double, 3> pose;
        std::array<double, 3> load;
        std::array<int, 3> constraint;

        Nodes(int id, 
            const std::array<double, 3>& pose,
            const std::array<double, 3>& load,
            const std::array<int, 3>& constraint);
        
        //Node(int id, Position pos, const std::array<double, 3>& load, const std::array<int, 3>& constraint);
    };
#endif

