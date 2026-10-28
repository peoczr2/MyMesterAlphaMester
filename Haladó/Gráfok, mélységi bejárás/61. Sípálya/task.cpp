/*
Megoldás lényege:
Két pályaszakasz egy ellenőr útvonalán egymás után állhat, ha az első végpontjából el lehet jutni a második kezdőpontjába, így a pályaszakaszok részbenrendezést alkotnak. Az ellenőrök útvonalai láncok ebben a rendezésben, így a legkevesebb ellenőr száma a rendezés szélessége (Dilworth-tétel): a legnagyobb olyan pályaszakasz-halmaz mérete, amelyben semelyik két szakasz nincs egymás után. Minden pályaszakasz közepére egy új csúcsot veszünk (u -> közép -> v), így a pályaszakaszok a síkbeli st-gráf csúcsai lesznek. Ebben az elérhetőségi rend kétdimenziós: a gyermekeket balról jobbra, illetve jobbról balra bejáró mélységi bejárás fordított utómunka-sorrendje két topologikus sorrendet ad, és két csúcs akkor áll egymás után, ha mindkét sorrendben ugyanúgy áll. Így a szélesség a második sorrend szerint a legnagyobb csökkenő részsorozat hossza, amelyet O(N log N) időben számolunk.
*/
/*
Hint 1: || Két pályaszakasz egy ellenőr útvonalán akkor állhat egymás után, ha az első végpontjából el lehet jutni a második kezdőpontjába. A legkevesebb ellenőr száma ezért a legnagyobb olyan pályaszakasz-halmaz mérete, amelyben semelyik két szakasz nincs egymás után. ||
Hint 2: || Minden pályaszakaszba illessz be egy új középső csúcsot (u -> közép -> v). Így az elérhetőségi rend csúcsokon van, és a síkbeli szerkezet megmarad, ezért a két mélységi bejárásos sorrend alkalmazható. ||
Hint 3: || A balról jobbra, illetve jobbról balra bejárt mélységi bejárás utómunka-sorrendjének fordítottja két topologikus sorrend. Az első sorrend szerint haladva a második sorrend értékeinek leghosszabb csökkenő részsorozata adja a választ, amit a leghosszabb növekvő részsorozat keresésével számolhatsz a negált értékeken. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Mélységi bejárás a megadott gyermeksorrenddel (rev = true: fordított sorrendben).
// Minden csúcsnak visszaadja a helyét a bejárás fordított utómunka-sorrendjében.
vector<int> topoPos(const vector<vector<int>> &g, int root, bool rev) {
    int V = g.size();
    vector<int> state(V, 0), cur(V, 0), post;
    post.reserve(V);
    auto init = [&](int v) { cur[v] = rev ? (int)g[v].size() - 1 : 0; };
    vector<int> st{root};
    state[root] = 1;
    init(root);
    while (!st.empty()) {
        int v = st.back();
        bool more = rev ? cur[v] >= 0 : cur[v] < (int)g[v].size();
        if (more) {
            int w = g[v][cur[v]];
            cur[v] += rev ? -1 : 1;
            if (!state[w]) {
                state[w] = 1;
                init(w);
                st.push_back(w);
            }
        } else {
            post.push_back(v);
            st.pop_back();
        }
    }
    vector<int> pos(V, -1);
    int k = post.size();
    for (int i = 0; i < k; ++i) pos[post[i]] = k - 1 - i;
    return pos;
}

// A cand csúcsok szélessége: az első topologikus sorrend szerint haladva a második sorrend
// értékeinek leghosszabb csökkenő részsorozata.
int width(const vector<vector<int>> &g, const vector<int> &cand) {
    vector<int> p1 = topoPos(g, 0, false);
    vector<int> p2 = topoPos(g, 0, true);
    vector<int> c = cand;
    sort(c.begin(), c.end(), [&](int a, int b) { return p1[a] < p1[b]; });
    vector<int> tails;
    for (int v : c) {
        int b = -p2[v];
        auto it = lower_bound(tails.begin(), tails.end(), b);
        if (it == tails.end()) tails.push_back(b);
        else *it = b;
    }
    return tails.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    if (n == 1) {
        cout << 0 << '\n';
        return 0;
    }
    vector<vector<int>> orig(n);
    for (int i = 0; i < n - 1; ++i) {
        int k;
        cin >> k;
        orig[i].resize(k);
        for (int j = 0; j < k; ++j) {
            cin >> orig[i][j];
            orig[i][j]--;
        }
    }
    int m = 0;
    for (int i = 0; i < n; ++i) m += orig[i].size();

    // Minden él u -> v helyett u -> közép -> v; a középső csúcsok sorszáma n, n+1, ...
    vector<vector<int>> g(n + m);
    vector<int> cand;
    int id = n;
    for (int u = 0; u < n; ++u) {
        for (int v : orig[u]) {
            g[u].push_back(id);
            g[id].push_back(v);
            cand.push_back(id);
            ++id;
        }
    }
    cout << width(g, cand) << '\n';
    return 0;
}
