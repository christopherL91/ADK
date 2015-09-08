#include <iostream>
#include <fstream>
#include <algorithm> // ::tolower
#include <string>
#include <sstream>
#include <ctime>
#include <vector>
#include <map>
#include <set>
#include <glob.h>
#include <cstdlib>
#include <cstring>
#include <regex>
#include <cmath>
#include <chrono>

const char *COLOR_NC="\e[0m";
const char *COLOR_WHITE="\e[1;37m";
const char *COLOR_BLACK="\e[0;30m";
const char *COLOR_BLUE="\e[0;34m";
const char *COLOR_LIGHT_BLUE="\e[1;34m";
const char *COLOR_GREEN="\e[0;32m";
const char *COLOR_LIGHT_GREEN="\e[1;32m";
const char *COLOR_CYAN="\e[0;36m";
const char *COLOR_LIGHT_CYAN="\e[1;36m";
const char *COLOR_RED="\e[0;31m";
const char *COLOR_LIGHT_RED="\e[1;31m";
const char *COLOR_PURPLE="\e[0;35m";
const char *COLOR_LIGHT_PURPLE="\e[1;35m";
const char *COLOR_BROWN="\e[0;33m";
const char *COLOR_YELLOW="\e[1;33m";
const char *COLOR_GRAY="\e[0;30m";
const char *COLOR_LIGHT_GRAY="\e[0;37m";

inline std::vector<std::string> glob(const std::string& pat){
    using namespace std;
    glob_t glob_result;
    glob(pat.c_str(),GLOB_TILDE,NULL,&glob_result);
    vector<string> ret;
    for(unsigned int i=0;i<glob_result.gl_pathc;++i){
        ret.push_back(string(glob_result.gl_pathv[i]));
    }
    globfree(&glob_result);
    return ret;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

std::string base_name(std::string const & path) {
  return path.substr(path.find_last_of("/\\") + 1);
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

int main(int argc, char const *argv[]) {
    std::ios::sync_with_stdio(false);
    if(argc != 3) {
        std::cerr << "Filename required" << std::endl;
        return EXIT_FAILURE;
    }
    std::string dictionary_name = argv[1];
    std::ifstream dictionary(dictionary_name,std::ios::in);

    std::string file_glob = argv[2];
    auto filenames = glob(file_glob);
    int numfiles = filenames.size();
    std::string word;

    while (std::cout << COLOR_LIGHT_GREEN << "Search for a word> " << COLOR_NC,std::getline(std::cin, word)) {
        if(word == "") {
            continue;
        }
        auto start = std::chrono::steady_clock::now();
        std::chrono::steady_clock::time_point end;

        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        int filenum = hashString(word, 4) % numfiles;
        char filename[1024];
        snprintf(filename, sizeof(filename), "/var/tmp/%3d.idx", filenum);
        std::ifstream index(filename);
        if(!index) {
            std::cerr << "Could not open file" << std::endl;
            dictionary.close();
            return EXIT_FAILURE;
        }
        std::string line;
        std::string result;
        std::string search = word+" ";
        bool found = false;
        while (std::getline(index, line)) {
            if(line.find(search) == 0) {
                //Found!
                found = true;
                int start = search.size();
                std::string poss = line.substr(start);
                auto positions_str = split(poss, ' ');
                //Convert to ints
                std::set<int> positions;
                for(std::string pos : positions_str) {
                    int p = atoi(pos.c_str());
                    positions.insert(p);
                }
                int numresults = positions.size();
                bool printresults = true;
                end = std::chrono::steady_clock::now();
                if(numresults > 25) {
                    std::cout << COLOR_LIGHT_RED
                        << numresults
                        << " results found. Do you want to output them? [Y/n] "
                        << COLOR_NC;
                    std::string answer;
                    std::regex ido ("y(es)?", std::regex_constants::icase);
                    std::getline( std::cin, answer );

                    if(!answer.empty() && !regex_match(answer, ido)) {
                        printresults = false;
                    }
                }
                if(printresults) {
                    const int length = 30+word.size()+30;
                    // allocate memory:
                    char buffer[length];
                    for(int pos : positions) {
                        //Before
                        int before = pos-30;
                        dictionary.seekg(std::max(before,0));
                        dictionary.read(buffer,length);
                        // Remove all newline
                        std::string output(buffer, 0, dictionary.gcount());
                        if(output.find("\n") != -1 ) {
                            output.replace(output.find("\n"), 1, " ");
                        }
                        std::cout << output << std::endl;
                    }
                }
                std::cout << std::endl << COLOR_LIGHT_BLUE << "Number of instances found: "
                    << COLOR_RED << numresults << COLOR_NC << std::endl;
                break;
            }
        }
        if(!found) {
            std::cerr << "Word not found!" << std::endl;
        }
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
        double ms = elapsed/1000000.0;
        std::cout << COLOR_LIGHT_BLUE << "Time to perform search: "
            << COLOR_RED << ms << "ms" << COLOR_NC << std::endl;
        // Restore index to beginning of file
        index.clear();
        index.seekg(0, std::ios::beg);
    }
    return EXIT_SUCCESS;
}
