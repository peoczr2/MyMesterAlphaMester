/*
Megoldás lényege:
A rendezés után minden helyhez tartozik egy célváros, így egy láda akkor van jó helyen, ha a városa megegyezik a helye célvárosával. Minden rosszul álló i. ládához egy élt húzunk a helye célvárosának csúcsától a saját városának csúcsától mutató irányba. Minden csúcsra a be- és kifok egyenlő, ezért minden összefüggő komponensben van zárt Euler-séta, amely a ládákat egy körbe rendezi. Egy k hosszú körben a ládákat az üres 0-s hely segítségével k+1 mozgatással forgatjuk a helyükre. A komponensenként egy kör miatt a minimális mozgatásszám a rosszul álló ládák száma plusz a komponensek száma. Az időigény O(N+V).
*/
/*
Hint 1: || A rendezett sorban minden helyhez egy célváros tartozik. Egy láda akkor jó helyen áll, ha a városa megegyezik annak a helynek a célvárosával. Csak a rossz helyen álló ládákat kell mozgatni. ||
Hint 2: || Építs irányított multigráfot a városokon: a rossz helyen lévő i. láda legyen a helye célvárosából a saját városába mutató él. Minden csúcsra a be- és kifok egyenlő, így minden összefüggő komponensben Euler-kör van, és a körbe rendezett ládák egyszerre egy körként mozgathatók. ||
Hint 3: || Egy k hosszú körben: először az első láda az üres 0-s helyre megy, aztán a körben a ládák sorban a helyükre kerülnek (az utolsónak a 0-ból kell a helyére lépnie). Ez k+1 mozgatás, így az összes mozgatás a rossz helyen lévő ládák száma plusz a komponensek száma. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, v;
    cin >> n >> v;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; ++i) cin >> s[i];
    for (int i = 1; i <= n; ++i) v = max(v, s[i]);

    // a rendezett sorban a helyek célvárosai
    vector<int> sorted_(s.begin() + 1, s.end());
    sort(sorted_.begin(), sorted_.end());
    vector<int> t(n + 1);
    for (int i = 1; i <= n; ++i) t[i] = sorted_[i - 1];

    // élek: a rossz helyen lévő i. láda t[i] -> s[i] (a helye célvárosától a saját városába)
    vector<vector<int>> out(v + 1);
    for (int i = 1; i <= n; ++i)
        if (s[i] != t[i]) out[t[i]].push_back(i);

    vector<size_t> ptr(v + 1, 0);
    vector<pair<int, int>> moves;  // i j: az i. helyen lévő láda a j. helyre megy

    for (int start = 1; start <= v; ++start) {
        if (ptr[start] >= out[start].size()) continue;

        // Hierholzer: Euler-kör az élek (helyek) sorozatában
        vector<int> circuit;
        vector<pair<int, int>> st;  // (csúcs, az ide vezető él vagy -1)
        st.push_back({start, -1});
        while (!st.empty()) {
            int u = st.back().first;
            if (ptr[u] < out[u].size()) {
                int e = out[u][ptr[u]++];
                st.push_back({s[e], e});
            } else {
                if (st.back().second != -1) circuit.push_back(st.back().second);
                st.pop_back();
            }
        }
        reverse(circuit.begin(), circuit.end());

        // a kör: p[j] láda a p[j+1] helyre megy, az üres 0-s hellyel
        int k = circuit.size();
        moves.push_back({circuit[0], 0});
        for (int j = k - 1; j >= 1; --j) moves.push_back({circuit[j], circuit[(j + 1) % k]});
        moves.push_back({0, circuit[1 % k]});
    }

    cout << moves.size() << "\n";
    for (auto &mv : moves) cout << mv.first << ' ' << mv.second << "\n";
    return 0;
}
