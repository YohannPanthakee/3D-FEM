#include "node.h"

Node::Node(int id,
        const std::array<double, 3>& pos,
        const std::array<double, 3>& load,
        const std::array<int, 3>& constraint)
        
    : id(id), position(pos), load(load), constraint(constraint) {}