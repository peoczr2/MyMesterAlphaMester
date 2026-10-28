/*
Megoldás lényege:
A bejárás mélységi bejárás, amely a termek ajtóit a szomszédsági listában megadott, óramutató járásával ellentétes sorrendben veszi sorra. Ha a látogató a szülő teremből érkezik, a szülő ajtajától kezdve körbe haladunk, és a még nem látott szomszédba lépünk. Minden ilyen belépésnél a jobb oldali falon a belépő és a kilépő ajtó közötti szakasz kerül sorra, így minden falszakaszt pontosan egyszer látnak. Visszatéréskor a szülő terem sorszámát írjuk ki. Az 1. teremben a 0. ajtótól indulunk. A kimenet 2N-1 szám, a futásidő O(N + M).
*/
/*
Hint 1: || A bejárás mélységi bejárás, de a szomszédokat nem a sorszám szerint, hanem a falon körbe haladva kell végignézni. A szülő után következő ajtóval kezdj. ||
Hint 2: || Egy szomszédba akkor lépj be, ha még nem jártál ott; a már bejárt ajtókon nem mész át. Minden lépés kiírja a terem sorszámát, ahová érkezel, így a visszatérés is kiíródik. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<char> visited;
vector<int> route;

void explore(int v, int parent) {
    int d = adj[v].size();
    int start = 0;
    if (parent != -1) {
        int pos = find(adj[v].begin(), adj[v].end(), parent) - adj[v].begin();
        start = (pos + 1) % d;
    }
    for (int k = 0; k < d; ++k) {
        int w = adj[v][(start + k) % d];
        if (w == parent || visited[w]) continue;
        visited[w] = 1;
        route.push_back(w);
        explore(w, v);
        route.push_back(v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    getline(cin, line);
    int n = stoi(line);
    adj.assign(n + 1, {});
    for (int i = 1; i <= n; ++i) {
        if (!getline(cin, line)) break;
        istringstream in(line);
        int x;
        while (in >> x) adj[i].push_back(x);
    }

    visited.assign(n + 1, 0);
    visited[1] = 1;
    route.push_back(1);
    explore(1, -1);

    for (size_t i = 0; i < route.size(); ++i) cout << route[i] << (i + 1 < route.size() ? ' ' : '\n');
    return 0;
}
