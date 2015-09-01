#include <iostream> // I/O
#include <map> // std::map
#include <vector> // std::vector
#include <algorithm> // ::tolower
#include <fstream> // file streams
#include <sstream> // string stream
#include <memory> // shared pointers.

/**
    This function will generate an index for the given input.
*/
const unsigned char letters[] = {'a', 'e','h','l','o','s','t', '\0'};
int getFileForChar(unsigned char c) {
    int i = 0;
    while(letters[i] != '\0') {
        if(letters[i] > c) {
            return i-1;
        }
        i++;
    }
    return i-1;
}

void generateIndex(std::istream &in) {
    std::string word; int offset;
    std::map<std::string,std::vector<int>> words;
    //Create range-index
    std::vector<std::shared_ptr<std::ostream>> files;
    for(int i = 0; i < 7; i++) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer), "/var/tmp/%c.idx",letters[i]);
        files.push_back(std::make_shared<std::ofstream>(buffer));
    }

    while (in >> word >> offset) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        words[word].push_back(offset);
    }

    for (auto outerIter = words.begin(); outerIter != words.end(); ++outerIter) {
        std::string word = outerIter->first;
        unsigned char first = word[0];
        std::ostream &out = *files[getFileForChar(first)];
        std::stringstream indices;
        for (auto innerIter = outerIter->second.begin(); innerIter != outerIter->second.end(); ++innerIter) {
            indices << " " << *innerIter;
        }
        out << word << indices.str() << std::endl;
    }
}
