/*
Megoldás lényege:
A barátok azonos, az ellenségek különböző csapatba kerülnek, ezért ez egy kétszínezési probléma.
Súlyozott unió-keresést (DSU) használunk: minden tanulóhoz a gyökerétől vett paritást tárolunk, ahol a 0 azonos, az 1 ellentétes csapatot jelent.
Egy barátsági pár 0, egy ellenségi pár 1 paritású összefüggést ad; ha egy új él ellentmond a már meglévőknek, nincs megoldás és -1 a kimenet.
Az éleket nem tároljuk (akár 4 millió sor is lehet, a memória 32 MB), hanem minden sor beolvasása után azonnal összevonjuk a halmazokat.
A végén minden tanuló csapata a gyökéréhez képesti paritása; ha az 1-es tanuló a másik csapatba került, az összes csapatot megfordítjuk, így az első sorban mindig az 1-es tanuló csapata áll.
Az időigény közel lineáris: O((N + M + K) · α(N)).
*/
/*
Hint 1: || Barátok azonos, ellenségek különböző csapatba kerülnek: ez egy kétszínezési feladat, ahol minden kapcsolat egy azonos vagy különböző csapatra vonatkozó előírás. ||
Hint 2: || Tartsd nyilván minden tanulóról, hogy a gyökerétől számítva melyik csapatban van (paritás), és új kapcsolatnál ellenőrizd, hogy egyezik-e a már meglévő előírásokkal. ||
Hint 3: || Az élek száma nagy, a memórialimit szigorú: ne tárold az éleket, minden sort beolvasás után azonnal dolgozz fel. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> par, rel_, sz_;

// Gyökér keresése; közben rel_[x] a gyökértől vett paritást adja.
int findRoot(int x) {
    if (par[x] == x) return x;
    int p = par[x];
    int r = findRoot(p);
    rel_[x] ^= rel_[p];
    par[x] = r;
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    par.resize(n + 1);
    iota(par.begin(), par.end(), 0);
    rel_.assign(n + 1, 0);
    sz_.assign(n + 1, 1);

    bool ok = true;
    // d = 0: barátok (azonos csapat), d = 1: ellenségek (különböző csapat)
    auto unite = [&](int a, int b, int d) {
        int ra = findRoot(a);
        int rb = findRoot(b);
        int pa = rel_[a];
        int pb = rel_[b];
        if (ra == rb) {
            if ((pa ^ pb) != d) ok = false;
            return;
        }
        if (sz_[ra] < sz_[rb]) swap(ra, rb);
        par[rb] = ra;
        rel_[rb] = pa ^ pb ^ d;
        sz_[ra] += sz_[rb];
    };

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        unite(a, b, 0);
    }
    for (int i = 0; i < k; ++i) {
        int a, b;
        cin >> a >> b;
        unite(a, b, 1);
    }

    if (!ok) {
        cout << -1 << '\n';
        return 0;
    }

    vector<int> team(n + 1, 0);
    for (int v = 1; v <= n; ++v) {
        findRoot(v);
        team[v] = rel_[v];
    }
    if (team[1] == 1) {
        for (int v = 1; v <= n; ++v) team[v] ^= 1;
    }

    for (int c = 0; c < 2; ++c) {
        bool first = true;
        for (int v = 1; v <= n; ++v) {
            if (team[v] != c) continue;
            if (!first) cout << ' ';
            cout << v;
            first = false;
        }
        cout << '\n';
    }
    return 0;
}
