#include <iostream>
#include <sstream>

int num_u,num_v;

int read_biparte() {
    std::stringstream output;
    int total_vertices,total_edges;
    int to,from, default_cost = 1;
    std::cin >> num_u >> num_v;
    std::cin >> total_edges;
    total_vertices = num_u + num_v + 2; // inlude all vertices + s and t
    output << total_vertices << std::endl << 1 << " " << total_vertices << std::endl;
    output << total_edges + num_u + num_v << std::endl;
    for (int i = 0; i < num_u; ++i) {
        output << 1 << " " << i+2 << " " <<  default_cost << std::endl;
    }

    for(int i = 0; i < total_edges; ++i) {
        std::cin >> from >> to;
        output << from + 1 << " " << to + 1 << " " << default_cost << std::endl;
    }

    for (int i = 0; i < num_v; ++i) {
        output << i+num_u+2 << " " << total_vertices << " " <<  default_cost << std::endl;
    }
    std::cout << output.str();
    return EXIT_SUCCESS;
}

int write_matching() {
    int num_edges, num_verts;
    std::stringstream output;
    std::cin >> num_verts;
    std::cin.ignore(256,'\n');
    std::cin.ignore(256,'\n');

    std::cin >> num_edges;
    for(int i = 0; i< num_u; ++i) {
        std::cin.ignore(256,'\n');
    }
    std::cin.ignore(256,'\n');
    int lines_to_read = num_verts - num_v - num_u;
    int from, to, c;
    output << num_u << " " << num_v << std::endl;
    for(int i = 0; i < lines_to_read; ++i) {
        std::cin >> from >> to >> c;
        output << (from - 1) << " " << (to-1) << std::endl;
    }
    std::cout << output.str();
    return EXIT_SUCCESS;
}
