#include <iostream> // I/O
#include <map> // std::map
#include <unordered_map> // std::map
#include <set>
#include <vector> // std::vector
#include <algorithm> // ::tolower
#include <fstream> // file streams
#include <sstream> // string stream
#include <memory> // shared pointers.
#include <cmath>
#include <cstdlib>

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

unsigned int hashString(std::string word, int len) {
    int hash = 0;
    const char *str = word.c_str();
    unsigned char c;
    int base = 29;
    int power = pow(base, len);
    for(int i = 0; i < len && (c = *(str++)); i++) {
        int val = c - 'a';
        if(c > 'z') {
            switch (c) {
                case 229:
                    val = 26;
                break;
                case 228:
                    val = 27;
                break;
                case 246:
                    val = 28;
                break;
                default:
                val = 27;
            }
        }
        hash += val * power;
        power /= base;
    }
    return hash;
}

void generateIndex(std::istream &in) {
    std::string word; int offset;
    std::map<std::string,std::vector<int>> words;
    //Create range-index
    const int numfiles = 1000;
    std::stringstream hashes[numfiles];
    while (in >> word >> offset) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        words[word].push_back(offset);
    }

    int lines = 0;
    for (auto outerIter = words.begin(); outerIter != words.end(); ++outerIter) {
        std::string word = outerIter->first;
        unsigned int hash = hashString(word, 4);
        unsigned int filenum = hash % numfiles;
        std::stringstream &hashfile = hashes[filenum];
        hashfile << word;
        lines++;
        for (auto innerIter = outerIter->second.begin(); innerIter != outerIter->second.end(); ++innerIter) {
            int position = *innerIter;
            hashfile << " " << position;
        }
        hashfile << std::endl;
    }

    char filename[1024];
    for(int i = 0; i < numfiles; ++i) {
        std::stringstream &hashfile = hashes[i];
        snprintf(filename, sizeof(filename), "/var/tmp/%3d.idx", i);
        std::ofstream out = std::ofstream(filename);
        out << hashfile.str();
        out.flush();
    }
}
