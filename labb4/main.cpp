#include <iostream>
#include <array>
#include <vector>
#include <utility>

using namespace std;

int main(int argc, char const *argv[]) {
	
	int n, s, k;
	int v, max_d, e;
	max_d = 0;
	cin >> n >> s >> k;

	int d_right = 0, d_left = 0;

	vector<pair<int,int>> edges;

	int val;
	int num;
	for(int i = 0; i < n; ++i) {
		cin >> num;
		if(num > max_d) {
			max_d = num;
		}
		d_right += num;


		for(int j = 0; j < num; ++j) {
			cin >> val;
			edges.push_back(make_pair(i+1, val+n));
		}
	}

	for(int i = 0; i < s; ++i) {
		cin >> num;
		if(num > max_d) {
			max_d = num;
		}

		d_left += num;

		for(int j = 0; j < num; ++j) {
			cin >> val;
			edges.push_back(make_pair(i+1+n+k, val));
		}
	}

	e = d_left + d_right;
	v = n + s + k;
	int m = max_d + 1;
	printf("%d\n%d\n%d\n", v,e,m);
	for(auto e: edges) {
		cout << e.first << " " << e.second << endl;
	}

	return EXIT_SUCCESS;
}