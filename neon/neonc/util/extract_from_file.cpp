#include "extract_from_file.h"

const std::string extract_from_file(const std::string file_path, int line) {
    std::ifstream f = std::ifstream(file_path);

    int i = 0;
    for (std::string __line; std::getline(f, __line);) {
        if (i == line - 1)
            return __line;
        i++;
    }

    return "";
}
