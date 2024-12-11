#include <fstream>
#include <sstream>
#include "headers/labelsprocess.hpp"

std::unordered_map<std::string, std::string> Labels::labels(std::string filename) {
    std::unordered_map<std::string, std::string> labels;
    std::ifstream file(filename);

    std::string line;
    std::string label{};
    std::string bodyString{};
    while (std::getline(file, line)) {

        // Find labels and add it to map
        if (line.ends_with(':')) {
            if (!label.empty() && !bodyString.empty()) {
                labels[label] = bodyString;
                label.clear();
                bodyString.clear();
            }
            label += line;
            continue;

        }

        bodyString += line;
        bodyString.push_back('\n');
    }
    if (!label.empty() && !bodyString.empty()) {
        labels[label] = bodyString;
        label.clear();
        bodyString.clear();
    }
    return labels;

}
