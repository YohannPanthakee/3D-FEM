#include "element.h"

//Elements::Elements(int id,
//                 int node1,
//                 int node2,
//                 const std::string& material_name)
//: id(id), node_ids({node1, node2}), material_name(material_name) {}

Elements::Elements(int id, const Nodes& node1, const Nodes& node2, const std::string& material_name)
: id(id), node_ids{node1,node2}, material_name(material_name)
    {
        // Calculating length and angle.
        // length = std::hypot(
        //     end_node.pose.x - start_node.pose.x,
        //     end_node.pose.y - start_node.pose.y,
        //     end_node.pose.z - start_node.pose.z,
        // )

        // Calculating length and angle.
        //length = std::hypot(
        //    end_node.position[0] - start_node.position[0],
        //    end_node.position[1] - start_node.position[1],
        //    end_node.position[2] - start_node.position[2],
        //)


    }