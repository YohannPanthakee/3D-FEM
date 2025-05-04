#ifndef NODE_H
#define NODE_H


#include <array>

class Node {
    public:
        int id;
        std::array<double, 3> position;
        std::array<double, 3> load;
        std::array<int, 3> constraint;

        Node(int id, 
            const std::array<double, 3>& pos,
            const std::array<double, 3>& load,
            const std::array<int, 3>& constraint);
    };

#endif

