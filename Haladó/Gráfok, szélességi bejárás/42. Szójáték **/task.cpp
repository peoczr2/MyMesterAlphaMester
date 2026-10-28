/*
Megoldás lényege:
A szótár szavai csúcsok, és egy w szóból egy v szóba akkor vezet él, ha v a szabály egy lépésével előállítható w-ből.
Az A szabály szerint csak azonos hosszú szavak lehetnek szomszédok, és pontosan egy betűben térhetnek el;
a B szabály ezen felül megengedi, hogy a w szó végére egy betűt írjunk, ezért ilyen él csak a hosszabb szó felé
mutat. A P-ből indított szélességi bejárás adja a Q-ig vezető legkisebb lépésszámot, az elért szavak száma pedig
a P-ből előállítható szavak száma (P-t is beleszámítva a feladat példája szerint). Az időigény O(N^2 * L),
ahol L a szavak hossza.
*/
/*
Hint 1: || Csúcsok legyenek a szótár különböző szavai; a w szóból a v szóba akkor vezessen él, ha a szabály egy lépésben átalakítja. Azonos hosszban pontosan egy betű térhet el, B szabálynál a v a w végére írt betűvel is létrejöhet. ||
Hint 2: || A P-ből indított szélességi bejárás a Q-ig vezető legrövidebb lépésszámot adja, az elért csúcsok száma pedig a második sor. Figyelj a duplikált szavakra, és a betűket UTF-8 esetén karakterenként hasonlítsd. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Egy szó betűinek listája (a többbájtos UTF-8 betűk egyben maradnak)
vector<string> letters(const string &s) {
    vector<string> res;
    for (size_t i = 0; i < s.size();) {
        unsigned char c = s[i];
        size_t len = 1;
        if (c >= 0xF0) len = 4;
        else if (c >= 0xE0) len = 3;
        else if (c >= 0xC0) len = 2;
        res.push_back(s.substr(i, len));
        i += len;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    set<string> uniq;
    for (int i = 0; i < n; i++) {
        string w;
        cin >> w;
        uniq.insert(w);
    }

    char rule;
    string p, q;
    cin >> rule >> p >> q;

    vector<string> words(uniq.begin(), uniq.end());  // rendezett, így lower_bound-dal kereshető
    int m = words.size();
    vector<vector<string>> L(m);
    for (int i = 0; i < m; i++) L[i] = letters(words[i]);

    auto findId = [&](const string &w) -> int {
        auto it = lower_bound(words.begin(), words.end(), w);
        if (it != words.end() && *it == w) return it - words.begin();
        return -1;
    };

    // Élek: egy szabályalkalmazással elérhető szavak
    vector<vector<int>> g(m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (i == j) continue;
            const vector<string> &a = L[i], &b = L[j];
            if (a.size() == b.size()) {
                int diff = 0;
                for (size_t k = 0; k < a.size() && diff <= 1; k++) {
                    if (a[k] != b[k]) diff++;
                }
                if (diff == 1) g[i].push_back(j);
            } else if (rule == 'B' && b.size() == a.size() + 1 && equal(a.begin(), a.end(), b.begin())) {
                g[i].push_back(j);
            }
        }
    }

    int s = findId(p), t = findId(q);
    if (s < 0 || t < 0) {
        cout << -1 << '\n' << 0 << '\n';
        return 0;
    }

    vector<int> dist(m, -1);
    queue<int> qu;
    dist[s] = 0;
    qu.push(s);
    int reach = 0;
    while (!qu.empty()) {
        int u = qu.front();
        qu.pop();
        reach++;
        for (int v : g[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                qu.push(v);
            }
        }
    }

    cout << dist[t] << '\n' << reach << '\n';
    return 0;
}
