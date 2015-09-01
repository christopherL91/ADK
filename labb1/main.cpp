#include <iostream>
#include <fstream>
#include <algorithm> // ::tolower
#include <string>
#include <sstream>
#include <ctime>
#include <vector>
#include <set>
#include <glob.h>
#include <cstdlib>
#include <cstring>
#include <regex>


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

const unsigned char letters[] = {'a', 'e','h','l','o','s','t'};

const char getFileName(unsigned char first) {
    int i;
    for(i = 0; first >= letters[i] && i < 7; ++i) {}
    return letters[i-1];
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
    auto files = glob(file_glob);
    std::string word;
    while (std::cout << COLOR_LIGHT_GREEN << "Search for a word> " << COLOR_NC,std::getline(std::cin, word)) {
        if(word == "") {
            continue;
        }
        clock_t begin = clock();

        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        // filehandler.
        char first = word[0];
        char c = getFileName(first);
        std::string file_name = "";
        for(auto glob_filename : files) {
            if(base_name(glob_filename)[0] == c) {
                file_name = glob_filename;
                break;
            }
        }
        if(file_name == "") {
            std::cerr << "Index file not found!" << std::endl;
            dictionary.close();
            return EXIT_FAILURE;
        }

        std::ifstream in(file_name,std::ios::in);
        if(!in) {
            std::cerr << "Could not open file" << std::endl;
            dictionary.close();
            return EXIT_FAILURE;
        }
        std::string line;
        std::string result;
        std::string search = word+" ";
        bool found = false;
        while (std::getline(in, line)) {
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
                if(numresults > 25) {
                    std::cout << "More than 25 results found. Do you want to output them? [Y/n] ";
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
                        strncpy(buffer, buffer, dictionary.gcount());
                        // Remove all newlines
                        *std::remove(buffer, buffer+dictionary.gcount(), '\n') = ' ';
                        *std::remove(buffer, buffer+dictionary.gcount(), '\r') = '\0';
                        std::cout << buffer << std::endl;
                    }
                }
                break;
            }
        }
        if(!found) {
            std::cerr << "Word not found!" << std::endl;
        }
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        std::cout << std::endl << COLOR_LIGHT_BLUE << "Time to perform search: " << COLOR_YELLOW << elapsed_secs << "s" << COLOR_NC << std::endl;
        in.close();
    }
    dictionary.close();
    return EXIT_SUCCESS;
}
