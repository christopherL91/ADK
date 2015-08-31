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
	while (std::getline(std::cin, word)) {
		clock_t begin = clock();

		std::transform(word.begin(), word.end(), word.begin(), ::tolower);
		// filehandler.
		char first = word[0];
		char c = getFileName(first);
		std::string file_name = "";
		for(auto glob_filename : files) {
			if(glob_filename[0] == c) {
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
				int start = search.size();
				std::string poss = line.substr(start);
				auto positions_str = split(poss, ' ');
				//Convert to ints
				std::set<int> positions;
				for(std::string pos : positions_str) {
					int p = atoi(pos.c_str());
					positions.insert(p);
				}
				const int length = 30;
				// allocate memory:
				char * buffer = new char [length];
				for(int pos : positions) {
					//Before
					int before = pos-30;
					dictionary.seekg(std::max(before,0));		
				    dictionary.read (buffer,length);
				    strncpy(buffer, buffer, dictionary.gcount());
				    std::cout << buffer << " ";
				    //After
				    int after = pos+word.size();
					dictionary.seekg(after);
					dictionary.read (buffer,length);
					strncpy(buffer, buffer, dictionary.gcount());
					std::cout << buffer << std::endl;
				}
				delete[] buffer;
				found = true;
				break;
			}
		}
		if(!found) {
			std::cerr << "Word not found!" << std::endl;
		}
		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		std::cout << elapsed_secs << "s" << std::endl;
		in.close();
	}
	dictionary.close();
	return EXIT_SUCCESS;
}
