/*
Megoldás lényege: visszalépéses keresés az érkezési sorrendben. Minden résztvevőnek a legkisebb
sorszámú olyan buszt keressük, ahol van hely és nincs vele nem kívánt utas. Az üres buszok
egymással felcserélhetők, ezért elágazáskor elég az első üres buszt kipróbálni; így a legkisebb
sorszámú megoldás jön ki. Sok ágon ugyanaz az állapot ismétlődik, ezért a sikertelen állapotokat
(buszonkénti létszám és a még szükséges korábbi utasok buszai) eltároljuk, és nem járjuk be újra.
Így N ≤ 20 és M ≤ 5 esetén is az időlimiten belül marad a futás.
*/
/*
Hint 1: || Az érkezési sorrendben haladva minden résztvevőnél csak azt kell ellenőrizni, hogy a már ott ülő korábbi érkezők közül ül-e rá nem kívánt utas az adott buszra. ||
Hint 2: || Ha valakinek egyetlen buszra sem tud beülni, lépj vissza az előző résztvevő buszválasztásához, és próbáld ki a következő buszt. ||
Hint 3: || Egy állapotot az határoz meg, hogy melyik buszon hányan vannak, és hogy a még jövőben számító korábbi utasok melyik buszon ülnek. Ezt az állapotot tárold el, és ha újra előjön, rögtön térj vissza. ||
*/

#include <bits/stdc++.h>
using namespace std;

// Az állapot kódja 128 bites szám: a lépés sorszáma, majd buszonként (létszám, maszk).
typedef unsigned __int128 Allapot;

struct AllapotHash {
    size_t operator()(Allapot x) const {
        unsigned long long lo = (unsigned long long)x, hi = (unsigned long long)(x >> 64);
        return (size_t)((lo * 0x9E3779B97F4A7C15ULL) ^ (hi * 0xC2B2AE3D27D4EB4FULL));
    }
};

int n, m, h;
vector<vector<int>> tilt;
vector<int> hely, darab, utolso, maszk;
vector<pair<int,int>> rendezett;
unordered_set<Allapot, AllapotHash> bukott;

bool dfs(int i) {
    if (i == n) return true;

    // utolso[x]: az utolsó résztvevő, akinek x a nem kívánt társa; ha ez >= i, x még fontos
    fill(maszk.begin(), maszk.end(), 0);
    for (int x = 0; x < i; ++x) if (utolso[x] >= i) maszk[hely[x] - 1] |= 1 << x;
    for (int b = 0; b < m; ++b) rendezett[b] = {darab[b], maszk[b]};
    sort(rendezett.begin(), rendezett.begin() + m);
    Allapot kulcs = i;
    for (int b = 0; b < m; ++b)
        kulcs = (kulcs << 24) | ((Allapot)rendezett[b].first << 20) | (Allapot)rendezett[b].second;
    if (bukott.count(kulcs)) return false;

    bool ures = false;
    for (int p = 0; p < m; ++p) {
        if (darab[p] >= h) continue;
        if (darab[p] == 0) {
            if (ures) continue;
            ures = true;
        }
        bool ok = true;
        for (int x : tilt[i]) if (x < i && hely[x] == p + 1) { ok = false; break; }
        if (!ok) continue;
        hely[i] = p + 1;
        ++darab[p];
        if (dfs(i + 1)) return true;
        --darab[p];
        hely[i] = 0;
    }
    if (bukott.size() < 100000) bukott.insert(kulcs);
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> h;
    tilt.assign(n, {});
    utolso.assign(n, -1);
    for (int i = 1; i < n; ++i) {
        int x;
        while (cin >> x && x != 0) {
            tilt[i].push_back(x - 1);
            utolso[x - 1] = max(utolso[x - 1], i);
        }
    }
    hely.assign(n, 0);
    darab.assign(m, 0);
    maszk.assign(m, 0);
    rendezett.assign(m, {0, 0});
    if (!dfs(0)) {
        cout << 0 << '\n';
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << hely[i];
    }
    cout << '\n';
    return 0;
}
