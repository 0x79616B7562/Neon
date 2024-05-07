#include "read_file.h"

std::string read_file(std::string file_path) {
    std::ifstream file(file_path);

    if (file.fail()) {
        std::ios_base::iostate state = file.rdstate();

        if (state & std::ios_base::eofbit) {
            std::cout << "End of file reached." << std::endl;
        }
        if (state & std::ios_base::failbit) {
            std::cout << "Non-fatal I/O error occurred." << std::endl;
        }
        if (state & std::ios_base::badbit) {
            std::cout << "Fatal I/O error occurred." << std::endl;
        }

        std::perror("Error: ");
        std::cerr << "File Path: " << file_path << std::endl;

        exit(1);
    }

    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    file.close();

    return str;
}
