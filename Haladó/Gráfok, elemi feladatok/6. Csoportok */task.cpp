/*
Megoldás lényege:
Minden tanulónak van egy legszimpatikusabb tanulója: a sorában a legnagyobb szám, feltéve, hogy az pozitív.
Ha ilyen van, a tanuló és a kedvence egy csoportba kerül, így a csoportok a „kedvence” élek összefüggő
komponensei. Minden tanulónak legfeljebb egy kedvence van, ezért ezek az élek egy gráfot határoznak meg, amelynek
komponenseit unió-kereséssel (DSU) gyűjtjük össze. A tanulóknak, akiknek nincs pozitív szimpátiájuk, nincs kedvencük:
ők külön csoportot alkotnak (ha másnak nem ők a kedvence). A csoportokat a legkisebb tagjuk szerint sorba rendezve, a
tagokat növekvő sorrendben írjuk ki. A bemenet N^2 szám, ezért gyors beolvasást használunk; ez a fő költség.
*/
/*
Hint 1: || Minden tanulóhoz elég a sorában a legnagyobb számot nézni: ha az pozitív, az a tanuló kedvence. ||
Hint 2: || A kedvenc-élek komponensei a csoportok: unió-kereséssel egyesítsd a tanulót a kedvencével, majd a gyökér szerint gyűjtsd a tagokat. ||
*/
#include <bits/stdc++.h>
using namespace std;

static char ibuf[1 << 16];
size_t ilen = 0, ipos = 0;

inline int gc() {
    if (ipos == ilen) {
        ilen = fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen == 0) return -1;
    }
    return ibuf[ipos++];
}

inline int readInt() {
    int c = gc();
    while (c != '-' && (c < '0' || c > '9')) {
        if (c == -1) return 0;
        c = gc();
    }
    bool neg = false;
    if (c == '-') {
        neg = true;
        c = gc();
    }
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return neg ? -x : x;
}

vector<int> parent;

int findRoot(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

int main() {
    int n = readInt();
    parent.resize(n + 1);
    for (int i = 0; i <= n; ++i) {
        parent[i] = i;
    }

    for (int i = 1; i <= n; ++i) {
        int best = 0, bestJ = 0;  // csak pozitív szimpátia számít
        for (int j = 1; j <= n; ++j) {
            int v = readInt();
            if (j != i && v > best) {
                best = v;
                bestJ = j;
            }
        }
        if (bestJ != 0) {
            int ra = findRoot(i), rb = findRoot(bestJ);
            if (ra != rb) {
                parent[ra] = rb;
            }
        }
    }

    // csoportok: a legkisebb tag szerint sorrendben
    vector<vector<int>> groups;
    vector<int> rootGroup(n + 1, -1);
    for (int v = 1; v <= n; ++v) {
        int r = findRoot(v);
        if (rootGroup[r] == -1) {
            rootGroup[r] = static_cast<int>(groups.size());
            groups.push_back({});
        }
        groups[rootGroup[r]].push_back(v);
    }

    string out;
    out += to_string(groups.size()) + "\n";
    for (auto& g : groups) {
        for (size_t k = 0; k < g.size(); ++k) {
            if (k) out += ' ';
            out += to_string(g[k]);
        }
        out += '\n';
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}
