#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

// for convenience
using json = nlohmann::json;



class JsonLoader {
    public:
        static json load_json_file(const std::string& filepath) {
            std::ifstream file(filepath);
            if (!file.is_open()) {
                throw std::runtime_error("Could not open file: " + filepath);
            };
            json data;
            file >> data; // This reads the file content and parses it as JSON

            //std::cout <<  "hello" << std::endl;
            return data;
        }
    };
    