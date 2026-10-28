/*
Megoldás lényege:
A kombinációkból trie-t építünk, majd Aho–Corasick-automatát: minden csúcsból minden gombra egyértelmű a következő csúcs, így a gombnyomások sorozata egy bolyongás az automatában. Egy csúcs pontszáma az ott záródó kombinációk száma: a csúcs saját végződéseihez hozzáadjuk a hibaláncon lévő csúcsok pontszámát, így egy belépéskor az összes ott záródó kombináció pontja egyszerre jár. A dinamikus programozás dp[v] értéke a legtöbb pont, amit az eddigi gombnyomások után a v csúcsban érhetünk el; K lépésben minden csúcsból mindhárom gombbal továbblépünk. Az állapotok száma legfeljebb 20·15+1 = 301, így az időigény O(K·301·3), kb. 10^8 egyszerű művelet, a memória O(301).
*/
/*
Hint 1: || Ne a gombnyomás-sorozatokat próbáld egyenként végigjárni, hanem azt kövesd, hogy a sorozat végén mely kombináció-előtag áll éppen „folyamatban”. Ezeket az előtagokat hogyan lehet egyetlen fába (trie) rendezni? ||
Hint 2: || Egy csúcs akkor ad pontot, ha a hozzá tartozó szöveg valamely utótagja kombináció. Az Aho–Corasick-féle hibalinkekkel minden csúcsból minden betűre meghatározható a következő csúcs, a pontszámot pedig a hibalánc mentén összegezheted. ||
Hint 3: || Dinamikus programozás a gombnyomások számára: dp[v] = legtöbb pont az eddigi gombnyomások után a v csúcsban. Egy lépésben minden csúcsból mindhárom betűvel továbblépve frissítsd a következő tömböt, és K lépés után a maximumot add vissza. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    // Trie: go[v][c] az átmenet, pont[v] az ott záródó kombinációk száma
    vector<array<int, 3>> go(1, {-1, -1, -1});
    vector<int> pont(1, 0);

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        int v = 0;
        for (char ch : s) {
            int c = ch - 'A';
            if (go[v][c] == -1) {
                go[v][c] = (int)go.size();
                go.push_back({-1, -1, -1});
                pont.push_back(0);
            }
            v = go[v][c];
        }
        pont[v]++;
    }

    // Aho–Corasick: hibalinkek és a teljes átmenettábla BFS-sel
    int m = (int)go.size();
    vector<int> fail(m, 0);
    queue<int> q;
    for (int c = 0; c < 3; ++c) {
        if (go[0][c] == -1) {
            go[0][c] = 0;
        } else {
            fail[go[0][c]] = 0;
            q.push(go[0][c]);
        }
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        pont[v] += pont[fail[v]];
        for (int c = 0; c < 3; ++c) {
            int u = go[v][c];
            if (u == -1) {
                go[v][c] = go[fail[v]][c];
            } else {
                fail[u] = go[fail[v]][c];
                q.push(u);
            }
        }
    }

    // dp[v]: legtöbb pont, amit az eddigi gombnyomások után a v csúcsban érhetünk el
    const int NEG = INT_MIN / 2;
    vector<int> dp(m, NEG), nd(m, NEG);
    dp[0] = 0;
    for (int step = 0; step < k; ++step) {
        fill(nd.begin(), nd.end(), NEG);
        for (int v = 0; v < m; ++v) {
            if (dp[v] == NEG) continue;
            for (int c = 0; c < 3; ++c) {
                int u = go[v][c];
                nd[u] = max(nd[u], dp[v] + pont[u]);
            }
        }
        swap(dp, nd);
    }

    int best = 0;
    for (int v = 0; v < m; ++v) best = max(best, dp[v]);
    cout << best << '\n';
    return 0;
}
