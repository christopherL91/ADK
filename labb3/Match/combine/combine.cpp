#include <iostream>
#include <sstream>
#include <queue>
#include <array>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int num_u,num_v;
#define MAX_NODES 20003

struct edge {
    edge(int capacity, int s, int t) {
        this-> capacity = capacity;
        this-> flow = 0;
        this-> s = s;
        this-> t = t;
    }
    int capacity;
    int flow;
    int s;
    int t;
    struct edge *reverse;
};

void clear(queue<int> &q ) {
    queue<int> empty;
    swap(q, empty );
}

void add_edge(int u, int v, array<vector<edge*>, MAX_NODES> &graph) {
    int default_cost = 1;
    edge *e = new edge(default_cost,u,v);
    edge *rev = new edge(0,v,u);
    e -> reverse = rev;
    rev -> reverse = e;
    graph[u].push_back(e);
    graph[v].push_back(rev);
}

void read_biparte(int total_vertices, int total_edges, int num_u, int num_v, int s, int t, array<vector<edge*>, MAX_NODES> &graph) {
    for(int i = 0; i < num_u; ++i) {
        add_edge(s,i+2, graph);
    }
    int from,to;
    for(int i = 0; i < total_edges; ++i) {
        std::cin >> from >> to;
        add_edge(from +1, to +1, graph);
    }
    for(int i = 0; i < num_v; ++i) {
        add_edge(num_u+i+2,t, graph);
    }
}

int calculate_flow(array<vector<edge*>, MAX_NODES> &graph, int s, int t, int num_nodes) {
    int flow = 0;
    queue<int> q;
    while(true) {
        q.push(s);
        edge *pred[MAX_NODES] = {nullptr};
        while(!q.empty()) {
            int current = q.front(); q.pop();
            for(edge *e : graph[current]) {
                if(e == nullptr) {
                    continue;
                }
                edge edg = *e;
                if(pred[edg.t] == nullptr && edg.t != s && edg.capacity > edg.flow) {
                    pred[edg.t] = e;
                    q.push(edg.t);
                }
            }
        }
        if(pred[t] == nullptr) {
            clear(q);
            break;
        }
        int df = INT_MAX;
        for(int node = t; node != s; node = pred[node] -> s) {
            df = min(df, (pred[node] -> capacity) - (pred[node] -> flow));
        }
        for(int node = t; node != s; node = pred[node] -> s) {
            pred[node] -> flow += df;
            pred[node] -> reverse -> flow -= df;
        }
        flow += df;
        clear(q);
    }
    return flow;
}

int main(int argc, char const *argv[]) {
    std::ios::sync_with_stdio(false);
    array<vector<edge*>, MAX_NODES> graph;
    fill(graph.begin(), graph.end(), vector<edge*>(5));

    int total_vertices,total_edges;
    std::cin >> num_u >> num_v;
    std::cin >> total_edges;
    total_vertices = num_u + num_v + 2; // inlude all vertices + s and t
    int s = 1;
    int t = total_vertices;

    // Read graph from stdin.
    read_biparte(total_vertices, total_edges, num_u, num_v, s, t, graph);
    total_edges += num_u + num_v;
    calculate_flow(graph,s,t,total_edges);

    cout << num_u << " " << num_v << endl;

    stringstream output;
    int num_lines = 0;
    for(int i = 0; i < total_vertices; ++i) {
        auto list = graph[i+1];
        if(i+1 == s) {
            continue;
        }
        for(edge *e: list) {
            if(e != nullptr && e->flow > 0) {
                if(e -> t == t) {
                    goto after;
                }
                ++num_lines;
                output << (e -> s - 1) << " " << (e -> t - 1) << endl;
            }
            delete e;
        }
    }
after:
    cout << num_lines << endl;
    cout << output.str();
    return EXIT_SUCCESS;
}
