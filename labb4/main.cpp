#include <iostream>
#include <array>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

bool pairCompare(
        const std::pair<int, int>& firstElem,
        const std::pair<int, int>& secondElem) {
  return firstElem.first < secondElem.first;
}

int main(int argc, char const *argv[]) {

    int n, s, k;
    int v, max_d, e;
    bool regular = true;
    max_d = 0;
    cin >> n >> s >> k;

    int d_right = 0, d_left = 0;

    vector<pair<int,int>> edges;

    int regular_d = -1;
    int val;
    int num;
    for(int i = 0; i < n; ++i) {
        cin >> num;
        if(regular) {
            if(regular_d == -1) {
                regular_d = num;
            } else if(regular_d != num) {
                regular = false;
            }
        }
        if(num > max_d) {
            max_d = num;
        }
        d_right += num;


        for(int j = 0; j < num; ++j) {
            cin >> val;
            edges.push_back(make_pair(val, i+1+k));
        }
    }

    for(int i = 0; i < s; ++i) {
        cin >> num;
        if(num > max_d) {
            max_d = num;
        }
        if(regular) {
            if(regular_d == -1) {
                regular_d = num;
            } else if(regular_d != num) {
                regular = false;
            }
        }
        d_left += num;

        for(int j = 0; j < num; ++j) {
            cin >> val;
            edges.push_back(make_pair(val+k, i+1 + k+n));
        }
    }

    e = d_left + d_right;
    v = n + s + k;
    int m = max_d + (regular ? 0 : 1);
    printf("%d\n%d\n%d\n", v,e,m);
    sort(edges.begin(), edges.end(), pairCompare);
    for(int i = 0; i < e; ++i) {
        auto edge = edges[i];
        printf("%d %d\n", edge.first, edge.second);
    }

    return EXIT_SUCCESS;
}
