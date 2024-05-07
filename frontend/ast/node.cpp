#include "node.h"

void Node::dump(const int indent) const {
    std::cout << ColorGray << std::string(indent * 4, '-') << BoldFont << ColorCyan << id << " " << ColorReset;

    if (data.size() > 0) {
        std::cout << "[";
    
        for (int i = 0; i < data.size(); i++) { 
            data[i].dump(indent);

            if (i < data.size() - 1)
                std::cout << ", ";
        }

        std::cout << "]";
    }

    std::cout << std::endl;

    for (Node child : nodes) {
        child.dump(indent + 1);
    }
}

std::optional<std::tuple<Data, std::optional<std::tuple<int, int>>>> Node::get_data_by_id(DataId id) const {
    for (auto d : data)
        if (d.id == id)
            return {{d, d.position}};

    return {};
}
