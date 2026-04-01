/*
A pincefúrás során a rendszer állapota lépésről lépésre változik, ezért minden döntést az aktuális helyzetből kell levezetni. A megoldás kulcsa annak követése, meddig juthatunk el az adott állapotból a következő szabály szerint.
*/
/*
Hint 1: || A fúrást lépésenként vagy szakaszonként érdemes követni, mert a döntés mindig a jelenlegi állapottól függ. ||
Hint 2: || Ha több lehetőség van, a következő elérhető mélység vagy pozíció határozza meg a továbblépést. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct State {
    int x, y, dir;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    set<pair<int,int>> used;
    set<pair<pair<int,int>, pair<int,int>>> edges;
    int x = 0, y = 0, dir = 0;
    used.insert({0, 0});
    vector<State> st;

    auto step = [&](int &x, int &y, int dir) {
        if (dir == 0) ++x;
        else if (dir == 1) ++y;
        else if (dir == 2) --x;
        else --y;
    };

    for (int i = 0; i < (int)s.size(); ++i) {
        char c = s[i];
        if (c == '(') {
            st.push_back({x, y, dir});
            continue;
        }
        if (c == ')') {
            auto z = st.back(); st.pop_back();
            x = z.x; y = z.y; dir = z.dir;
            continue;
        }
        if (c == 'J') dir = (dir + 3) % 4;
        else if (c == 'B') dir = (dir + 1) % 4;
        else if (c == 'E') {
            int nx = x, ny = y;
            step(nx, ny, dir);
            pair<pair<int,int>, pair<int,int>> e = {min(make_pair(x, y), make_pair(nx, ny)), max(make_pair(x, y), make_pair(nx, ny))};
            if (used.count({nx, ny}) || edges.count(e)) {
                cout << i + 1 << '\n';
                return 0;
            }
            used.insert({nx, ny});
            edges.insert(e);
            x = nx; y = ny;
        }
    }
    cout << 0 << '\n';
    return 0;
}