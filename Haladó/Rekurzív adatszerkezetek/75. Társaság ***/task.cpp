/*
Megoldás lényege:
A vezető (1-es tag) mindig kijelölt, egy tag üzenete pedig a főnökein keresztül felfelé halad, amíg először kijelölt emberhez nem ér.
A legnagyobb várakozási időt bináris kereséssel határozzuk meg: egy D értékhez megnézzük, legalább hány kijelölés kell ahhoz, hogy senki várakozási ideje ne haladja meg D-t.
Ezt a számot alulról felfelé haladó mohó bejárással kapjuk: minden csúcsnál nyilván van tartva, mennyi a legtávolabbi még el nem látott leszármazott távolsága.
Ha egy gyermeken át ez a távolság (az éllel együtt) már nagyobb D-nél, akkor a gyermeket kell kijelölni, mert ő lefedi az egész részfáját.
Az időigény O(N log(összeg)), mert a keresés kb. 45 lépés, és minden lépés O(N).
*/
/*
Hint 1: || Egy tag üzenete a főnökein keresztül halad, és az első kijelölt embernél áll meg. Így a várakozási idő a tag és a legközelebbi kijelölt felmenője közötti távolság. ||
Hint 2: || Keresd a legkisebb D értéket, amelyhez legfeljebb K kijelölés elég. Mivel D növelésével a kellő kijelölések száma nem nő, ez bináris kereséssel megtalálható. ||
Hint 3: || Egy adott D-nél a fát alulról felfelé dolgozd fel. Ha egy gyermek részfájában egy még el nem látott tag távolsága a szülőtől (a gyermek élével együtt) D-nél nagyobb, akkor a gyermeket kell kijelölni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<long long> w;          // w[v]: üzenet ideje v -> főnöke
vector<vector<int>> ch;       // gyermekek
vector<int> order_;           // BFS-sorrend a vezetőtől

// Hány kijelölés kell (a vezetőn kívül) D várakozási idő eléréséhez? K+1-nél korán megáll.
long long needed(long long D) {
    vector<long long> need(n + 1, 0);   // need[v]: v részfájában a legtávolabbi el nem látott tag távolsága v-től
    long long cnt = 0;
    for (int idx = n - 1; idx >= 0; --idx) {
        int v = order_[idx];
        long long best = 0;
        for (int c : ch[v]) {
            long long d = need[c] + w[c];
            if (d > D) {
                ++cnt;                  // c-t kell kijelölni: ő lefedi az egész részfáját
                if (cnt > k) return cnt;
            } else {
                best = max(best, d);
            }
        }
        need[v] = best;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    w.assign(n + 1, 0);
    ch.assign(n + 1, {});
    for (int i = 2; i <= n; ++i) {
        int p;
        long long t;
        cin >> p >> t;
        w[i] = t;
        ch[p].push_back(i);
    }

    order_.push_back(1);
    for (size_t h = 0; h < order_.size(); ++h)
        for (int c : ch[order_[h]]) order_.push_back(c);

    long long lo = 0, hi = 0;
    for (int v = 2; v <= n; ++v) hi += w[v];
    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (needed(mid) <= k) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << "\n";
    return 0;
}
