/*
Megoldás lényege:
Minden évben egy még szabad ország akkor foglalható el, ha agresszív szomszédai mind
ugyanahhoz az agresszív országhoz (gyökérhez) tartoznak; ekkor az elfoglalás annak a
tulajdonába kerül. Ha két különböző agresszív ország szomszédja, nem dől el, kié legyen,
ezért örökre szabad marad: a különböző tulajdonosú agresszív szomszédok száma később sem
csökken. Ezért évenként szélességi bejárást végzünk: az előző évben agresszívvá vált
országok szomszédait vizsgáljuk, és minden érintett országnál figyeljük, hogy egyezik-e
a tulajdonos. Mivel minden szomszédsági él legfeljebb egyszer kerül feldolgozásra, az
időigény O(N + az összes szomszédsági él).
*/
/*
Hint 1: || Csak azokat az országokat kell vizsgálni, amelyeknek az előző évben agresszívvá vált szomszédjuk van; az évek szerint haladva ez szélességi bejárásra hasonlít. ||
Hint 2: || Egy szabad ország csak akkor foglalható el, ha az agresszív szomszédai mind ugyanahhoz az országhoz tartoznak. Ha két különböző tulajdonos szomszédja, az örökre szabad marad. ||
Hint 3: || Minden országnak tárolj tulajdonost: egy elfoglalt ország tulajdonosa az a gyökér agresszív ország, amelytől elfoglalták. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, r, k;
    cin >> n >> r >> k;

    // Szomszédsági listák egy tömbben: az i-edik ország szomszédai adj[start[i] .. start[i+1]).
    vector<int> start(n + 2), adj;
    adj.reserve(static_cast<size_t>(n) * 100);
    for (int i = 1; i <= n; ++i) {
        start[i] = static_cast<int>(adj.size());
        int s;
        while (cin >> s && s != 0) adj.push_back(s);
    }
    start[n + 1] = static_cast<int>(adj.size());

    // owner: 0 = még szabad, -1 = örökre szabad maradt, különben a gyökér agresszív ország sorszáma.
    vector<int> owner(n + 1, 0), stamp(n + 1, 0), cand(n + 1, 0);
    vector<char> clash(n + 1, 0);
    vector<int> frontier;
    for (int i = 1; i <= r; ++i) {
        owner[i] = i;
        frontier.push_back(i);
    }

    for (int year = 1; year <= k && !frontier.empty(); ++year) {
        vector<int> touched;
        for (int u : frontier) {
            for (int idx = start[u]; idx < start[u + 1]; ++idx) {
                int v = adj[idx];
                if (owner[v] != 0) continue;
                if (stamp[v] != year) {
                    stamp[v] = year;
                    cand[v] = owner[u];
                    touched.push_back(v);
                } else if (cand[v] != owner[u]) {
                    clash[v] = 1;
                }
            }
        }

        vector<int> next;
        for (int v : touched) {
            if (!clash[v]) {
                owner[v] = cand[v];
                next.push_back(v);
            } else {
                owner[v] = -1;
            }
        }
        frontier.swap(next);
    }

    vector<vector<int>> conquered(r + 1);
    for (int v = r + 1; v <= n; ++v) {
        if (owner[v] > 0) conquered[owner[v]].push_back(v);
    }

    for (int i = 1; i <= r; ++i) {
        cout << conquered[i].size();
        for (int v : conquered[i]) cout << ' ' << v;
        cout << '\n';
    }
    return 0;
}
