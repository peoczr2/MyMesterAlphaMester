/*
Megoldási ötlet:
A „nem szeretik egymást” kapcsolat egy páros gráfot ad, mert a feladat garantálja, hogy a diákok két
táborba szétoszthatók. Minden összefüggő komponensben tehát két színosztály adódik, és az adott komponensnél
csak azt kell eldönteni, melyik szín kerüljön az első táborba.

A komponensek színosztályainak méreteiből részösszeg-DP-t készítünk: melyik első táborbeli létszám érhető el.
Így kiválasztható az N/2-höz legközelebbi megoldás, majd visszafejtjük, hogy komponensenként melyik színosztály
került az első táborba. A végén a két névsort rendezetten írjuk ki.
*/
/*
Hint 1: || Először színezd ki a gráfot két színnel komponensenként. ||
Hint 2: || Egy komponensben csak két lehetőség van: az egyik vagy a másik színosztály kerül az első táborba. ||
Hint 3: || A végső létszámkülönbség minimalizálásához subset-sum jellegű DP-t használj a komponensméretekkel. ||
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Component {
    vector<int> part[2];
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> color(n + 1, -1);
    vector<Component> components;

    for (int start = 1; start <= n; ++start) {
        if (color[start] != -1) continue;
        queue<int> q;
        q.push(start);
        color[start] = 0;
        Component comp;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            comp.part[color[node]].push_back(node);
            for (int next : graph[node]) {
                if (color[next] == -1) {
                    color[next] = color[node] ^ 1;
                    q.push(next);
                }
            }
        }
        components.push_back(comp);
    }

    int c = static_cast<int>(components.size());
    vector<vector<char>> possible(c + 1, vector<char>(n + 1, 0));
    vector<vector<char>> choice(c + 1, vector<char>(n + 1, -1));
    possible[0][0] = 1;

    for (int i = 0; i < c; ++i) {
        int a = static_cast<int>(components[i].part[0].size());
        int b = static_cast<int>(components[i].part[1].size());
        for (int s = 0; s <= n; ++s) {
            if (!possible[i][s]) continue;
            if (!possible[i + 1][s + a]) {
                possible[i + 1][s + a] = 1;
                choice[i + 1][s + a] = 0;
            }
            if (!possible[i + 1][s + b]) {
                possible[i + 1][s + b] = 1;
                choice[i + 1][s + b] = 1;
            }
        }
    }

    int bestSize = -1;
    for (int s = 0; s <= n; ++s) {
        if (!possible[c][s]) continue;
        if (bestSize == -1 || abs(n - 2 * s) < abs(n - 2 * bestSize)) bestSize = s;
    }

    vector<int> orientation(c, 0);
    int current = bestSize;
    for (int i = c; i >= 1; --i) {
        int pick = choice[i][current];
        orientation[i - 1] = pick;
        current -= static_cast<int>(components[i - 1].part[pick].size());
    }

    vector<int> campA, campB;
    for (int i = 0; i < c; ++i) {
        int pick = orientation[i];
        for (int student : components[i].part[pick]) campA.push_back(student);
        for (int student : components[i].part[pick ^ 1]) campB.push_back(student);
    }

    sort(campA.begin(), campA.end());
    sort(campB.begin(), campB.end());

    cout << campA.size() << ' ' << campB.size() << '\n';
    for (size_t i = 0; i < campA.size(); ++i) {
        if (i > 0) cout << ' ';
        cout << campA[i];
    }
    cout << '\n';
    for (size_t i = 0; i < campB.size(); ++i) {
        if (i > 0) cout << ' ';
        cout << campB[i];
    }
    cout << '\n';
    return 0;
}