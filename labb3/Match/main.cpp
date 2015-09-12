#include <iostream>

#include "biparte.h"

int main(int argc, char const *argv[]) {
    std::ios::sync_with_stdio(false);
    int res = read_biparte();
    if (res != 0) {
        return EXIT_FAILURE;
    }
	return write_matching();
}
