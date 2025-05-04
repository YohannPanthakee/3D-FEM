#include "element.h"

Element::Element(int id,
                 int node1,
                 int node2,
                 const std::string& material_name)
    : id(id), node_ids({node1, node2}), material_name(material_name) {}