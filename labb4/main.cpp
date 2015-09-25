#include <cstdio>

using namespace std;

int main(int argc, char const *argv[]) {
	
	int v,e,m;

	scanf("%d\n%d\n%d\n", &v,&e,&m);

	int from,to;
	for (int i = 0; i < e; ++i) {
		scanf("%d %d\n", &from,&to);
	}
	return EXIT_SUCCESS;
}