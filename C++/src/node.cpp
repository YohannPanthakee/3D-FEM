#include "node.h"

Nodes::Nodes(int id,
        const std::array<double, 3>& pose,
        const std::array<double, 3>& load,
        const std::array<int, 3>& constraint)
: id(id), pose(pose), load(load), constraint(constraint) {}