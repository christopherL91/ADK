#include <iostream>
#include <fstream>
#include <string>

#include "gen_index.h"

/**
    Example usage: ./index infile
*/

int main(int argc, char const *argv[]) {
    std::ios::sync_with_stdio(false);
    if(argc != 2) {
        std::cerr << "Filename required" << std::endl;
        return EXIT_FAILURE;
    }
    // Input file name.
    std::string in_name = argv[1];
    // filehandler.
    std::ifstream in(in_name,std::ios::in);
    if(in) {
        generateIndex(in);
    }else {
        std::cerr << "File does not exist" << std::endl;
        return EXIT_FAILURE;
    }
    in.close();
    return EXIT_SUCCESS;
}
