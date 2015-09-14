#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

struct edge {
    edge() {}
    edge(int capacity, int flow, int s, int t) {
        this-> capacity = capacity;
        this-> flow = flow;
        this-> s = s;
        this-> t = t;
        this->reverse = new edge();
    }
    int capacity = 0;
    int flow = 0;
    int s = 0;
    int t = 0;
    struct edge *reverse;
};

int calculate_flow(array<vector<edge*>, 4001> graph, int s, int t, int num_nodes) {
    int flow = 0;
    queue<int> q;
    q.push(s);
    while(true) {
        array<edge*,4001> pred;
        while(!q.empty()) {
            int current = q.front();q.pop();
            for(edge *e : graph[current]) {
                if(pred[e -> t] == nullptr && e -> t != s && e -> capacity > e -> flow) {
                    pred[e -> t] = e;
                    cout << "about to add" << endl;
                    q.push(e -> t);
                }
            }
        }
        if(pred[t] == nullptr) {
            cout << "stopping search" << endl;
            break;
        }
        int df = INT_MAX;
        for(edge *e = pred[t]; e != nullptr; e = pred[e -> s]) {
            df = min(df, (e -> capacity) - (e -> flow));
        }
        for(edge *e = pred[t]; e != nullptr; e = pred[e -> s]) {
            e -> flow = e->flow + df;
            e -> reverse -> flow = e-> reverse -> flow - df;
        }
        flow = flow + df;
        cout << "flow :" << flow << endl;
    }
    return flow;
}

int main(int argc, char const *argv[]) {
    int num_nodes,num_edges,s,t;
    array<vector<edge*>, 4001> graph;
    fill(graph.begin(), graph.end(), vector<edge*>());

    cin >> num_nodes;
    cin >> s >> t;
    cin >> num_edges;

    int u,v,c;
    while(cin >> u >> v >> c) {
        edge *e = new edge(c,0,u,v);
        graph[u].push_back(e);
    }
    int max_flow = calculate_flow(graph,s,t,num_nodes);
    cout << "Maximal flow " << max_flow << endl;
}
