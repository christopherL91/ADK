#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char const *argv[]) {
    int v, e, m;
    cin >> v >> e >> m;

    int actors = m + 2;
    int roles = v + 2;
    int scenes = e + 2;

    cout << roles << " " << scenes << " " << actors << endl;

    // roles
    cout << 1 << " " << 1 << endl;
    cout << 1 << " " << 2 << endl;
    stringstream roleactors;
    roleactors << m;
    for(int i = 3; i < actors +1; i++) {
        roleactors << " " << i;
    }
    string actorlist = roleactors.str();
    for(int i = 3; i < roles +1; i++) {
        cout << actorlist << endl;
    }

    // scenes
    cout << 2 << " " << 1 << " " << 3 << endl;
    cout << 2 << " " << 2 << " " << 3 << endl;
    for(int i = 0; i < e; i++) {
        int x,y;
        cin >> x >> y;
        cout << 2 << " " << x + 2 << " " << y + 2 << endl;
    }

    return EXIT_SUCCESS;
}
