/*
Megoldás lényege:
Most az elágazási pontokat kell lefedni, és egy ellenőr útvonala láncot alkot az elérhetőségi rendben: két pont egy úton akkor áll egymás után, ha az egyikből el lehet jutni a másikba. Így a legkevesebb ellenőr száma az elérhetőségi rend szélessége (Dilworth-tétel), vagyis a legnagyobb olyan csúcshalmaz mérete, amelyben semelyik két csúcs között nincs út. A sík st-gráf elérhetőségi rendje kétdimenziós: a gyermekeket balról jobbra, illetve jobbról balra bejáró mélységi bejárás fordított utómunka-sorrendje két topologikus sorrendet ad, és két csúcs akkor áll egymás után, ha mindkét sorrendben ugyanúgy áll. Így a szélesség a második sorrend szerint a legnagyobb csökkenő részsorozat hossza, amelyet O(N log N) időben számolunk.
*/
/*
Hint 1: || Egy ellenőr útja olyan kereszteződéseket érint, amelyek között mindenhol van út. Ezért a legkevesebb ellenőr száma a legnagyobb olyan kereszteződés-halmaz mérete, amelyben semelyik két csúcs között nincs út. ||
Hint 2: || A sík gráf elérhetőségi rendje két topologikus sorrenddel írható le: a gyermekeket balról jobbra, illetve jobbról balra bejáró mélységi bejárás utómunka-sorrendjének fordítottjával. Két csúcs akkor áll elérhetőségi kapcsolatban, ha mindkét sorrendben ugyanúgy állnak. ||
Hint 3: || Az első sorrend szerint haladva a második sorrend értékeinek leghosszabb csökkenő részsorozata adja a választ. Ezt a leghosszabb növekvő részsorozat keresésének mintájára, alsó korlát kereséssel számold ki a negált értékeken. ||
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
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int k;
        cin >> k;
        g[i].resize(k);
        for (int j = 0; j < k; ++j) {
            cin >> g[i][j];
            g[i][j]--;
        }
    }
    vector<int> cand(n);
    iota(cand.begin(), cand.end(), 0);
    cout << width(g, cand) << '\n';
    return 0;
}
