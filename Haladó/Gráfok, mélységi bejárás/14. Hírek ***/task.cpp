/*
Megoldás lényege:
A tanulók irányított gráfot alkotnak: i-ből él megy j-be, ha i továbbadja a hírt j-nek. Egy kiválasztott tanulóhoz a hír azokhoz jut el, akik a gráfban elérhetők belőle. Tarjan-algoritmussal megkeressük az erősen összefüggő komponenseket, a kondenzált gráf körmentes. Minden komponensnél bitsorozatban tároljuk az elérhető csúcsok halmazát, így a komponensek halmazát a célkomponensek halmazainak uniójából kapjuk. Minden csúcs elérhető valamelyik forráskomponensből, ezért elég a forráskomponensek között keresni. Egy forrás saját komponense más forrásból nem érhető el, ezért két forrás uniója a saját méreteik összege és a nem-forrás részük uniójának elemszáma. A forrásokat a nem-forrás részük szerint csoportosítjuk, és a párokat csoportok között vizsgáljuk; az időigény O(E·N/64 + S²·N/64) bitművelet, ahol S a forráskomponensek száma.
*/
/*
Hint 1: || Egy tanuló által kiválasztott hír azokhoz jut el, akik a gráfban elérhetők belőle. Az erősen összefüggő komponensek egy csomópontként kezelhetők, és elég a kondenzált gráf forrásai közül választani. ||
Hint 2: || A Tarjan-algoritmus a komponenseket olyan sorrendben adja, hogy egy komponens célkomponensei már korábban elkészülnek. Így egy komponens elérési halmaza a saját csúcsaiból és a célkomponensek halmazainak uniójából építhető. ||
Hint 3: || K = 1 esetén a legnagyobb elérési halmazú forrást keresd. K = 2 esetén két forrás uniójának elemszámát kell maximalizálni: a forrásoknak a saját komponensük nem fed át, ezért elég a többi elérhető csúcsukat nézni. Az azonos halmazú forrásokat csoportosítva és az elemszám szerint rendezve a rossz párokat korán kihagyhatod. ||
*/
#include <bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;

int n, k;
vector<vector<int>> g;
vector<int> idx_, low_, comp, stk;
vector<char> onStk;
int timer_ = 0, compCnt = 0;

void tarjan(int v) {
    idx_[v] = low_[v] = ++timer_;
    stk.push_back(v);
    onStk[v] = 1;
    for (int u : g[v]) {
        if (!idx_[u]) {
            tarjan(u);
            low_[v] = min(low_[v], low_[u]);
        } else if (onStk[u]) {
            low_[v] = min(low_[v], idx_[u]);
        }
    }
    if (low_[v] == idx_[v]) {
        while (true) {
            int w = stk.back();
            stk.pop_back();
            onStk[w] = 0;
            comp[w] = compCnt;
            if (w == v) break;
        }
        ++compCnt;
    }
}

struct Group {
    int w1 = -1, c1 = -1, w2 = -1, c2 = -1, size = 0;
};

struct Item {
    const vector<uint64_t> *X;
    int xcnt, w1, c1, w2, c2, size;
    int cnt() const { return w1 + xcnt; }
};

int main() {
    cin >> n >> k;
    g.assign(n + 1, {});
    for (int i = 1; i <= n; ++i) {
        int x;
        while (cin >> x && x != 0) g[i].push_back(x);
    }

    idx_.assign(n + 1, 0);
    low_.assign(n + 1, 0);
    comp.assign(n + 1, -1);
    onStk.assign(n + 1, 0);
    for (int v = 1; v <= n; ++v)
        if (!idx_[v]) tarjan(v);

    vector<vector<int>> members(compCnt);
    for (int v = 1; v <= n; ++v) members[comp[v]].push_back(v);

    // A Tarjan-algoritmusban egy komponens éleinek célja kisebb azonosítójú komponens,
    // ezért a komponensek növekvő sorrendben számíthatók ki.
    const int W = (n >> 6) + 1;
    vector<uint64_t> R((size_t)compCnt * W, 0);
    for (int c = 0; c < compCnt; ++c) {
        uint64_t *rc = &R[(size_t)c * W];
        for (int v : members[c]) {
            rc[v >> 6] |= 1ULL << (v & 63);
            for (int u : g[v]) {
                int d = comp[u];
                if (d == c) continue;
                const uint64_t *rd = &R[(size_t)d * W];
                for (int t = 0; t < W; ++t) rc[t] |= rd[t];
            }
        }
    }

    vector<int> rep(compCnt, INT_MAX);
    for (int v = 1; v <= n; ++v) rep[comp[v]] = min(rep[comp[v]], v);

    vector<char> hasIn(compCnt, 0);
    for (int v = 1; v <= n; ++v)
        for (int u : g[v])
            if (comp[u] != comp[v]) hasIn[comp[u]] = 1;

    // Forráskomponensek csoportosítása a nem-saját elérhető halmazuk szerint.
    map<vector<uint64_t>, Group> groups;
    for (int c = 0; c < compCnt; ++c) {
        if (hasIn[c]) continue;
        vector<uint64_t> X(&R[(size_t)c * W], &R[(size_t)c * W] + W);
        for (int v : members[c]) X[v >> 6] &= ~(1ULL << (v & 63));
        int w = (int)members[c].size();
        Group &gr = groups[X];
        gr.size++;
        if (w > gr.w1) {
            gr.w2 = gr.w1;
            gr.c2 = gr.c1;
            gr.w1 = w;
            gr.c1 = c;
        } else if (w > gr.w2) {
            gr.w2 = w;
            gr.c2 = c;
        }
    }

    vector<Item> items;
    for (auto &kv : groups) {
        int xc = 0;
        for (uint64_t x : kv.first) xc += __builtin_popcountll(x);
        const Group &gr = kv.second;
        items.push_back({&kv.first, xc, gr.w1, gr.c1, gr.w2, gr.c2, gr.size});
    }
    sort(items.begin(), items.end(), [](const Item &a, const Item &b) { return a.cnt() > b.cnt(); });

    if (k == 1) {
        cout << items[0].cnt() << "\n" << rep[items[0].c1] << "\n";
        return 0;
    }

    long long best = -1;
    int ba = -1, bb = -1;
    // Azonos halmazú forrásokból álló pár: a két legnagyobb saját komponens.
    for (const Item &it : items) {
        if (it.size < 2) continue;
        long long val = (long long)it.w1 + it.w2 + it.xcnt;
        if (val > best) {
            best = val;
            ba = it.c1;
            bb = it.c2;
        }
    }

    if (items.size() == 1 && items[0].size == 1) {
        // Egyetlen forrás van: a második tanuló tetszőleges, a két forrás uniója nem nő.
        int a = rep[items[0].c1];
        int b = (a == 1) ? 2 : 1;
        cout << items[0].cnt() << "\n" << min(a, b) << " " << max(a, b) << "\n";
        return 0;
    }

    int I = items.size();
    for (int i = 0; i + 1 < I; ++i) {
        if (items[i].cnt() + items[i + 1].cnt() <= best) break;
        const uint64_t *xa = items[i].X->data();
        for (int j = i + 1; j < I; ++j) {
            if (items[i].cnt() + items[j].cnt() <= best) break;
            const uint64_t *xb = items[j].X->data();
            long long u = 0;
            for (int t = 0; t < W; ++t) u += __builtin_popcountll(xa[t] | xb[t]);
            long long val = (long long)items[i].w1 + items[j].w1 + u;
            if (val > best) {
                best = val;
                ba = items[i].c1;
                bb = items[j].c1;
            }
        }
    }

    int a = rep[ba], b = rep[bb];
    if (a > b) swap(a, b);
    cout << best << "\n" << a << " " << b << "\n";
    return 0;
}
