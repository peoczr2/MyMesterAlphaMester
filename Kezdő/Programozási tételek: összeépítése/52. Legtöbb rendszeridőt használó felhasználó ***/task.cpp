/*
Megoldás lényege: minden felhasználóhoz tároljuk, hogy éppen bent van-e, és ha igen, mikor jelentkezett be.
Az első adata határozza meg a kezdeti állapotot: ha kijelentkezés, akkor a felhasználó az előző napról bent van,
így a számítás a nap 0:00 pillanatától indul. A sikertelen műveleteket (már bent lévő be, kint lévő ki) figyelmen
kívül hagyjuk, a sikeres kijelentkezésnél pedig a bent töltött perceket hozzáadjuk az összesítéshez. A nap végén
még bent lévőknél az időt a 24:00 pillanatáig számoljuk. Végül a legnagyobb összesítéssel rendelkező azonosítókat
az első műveletük sorrendjében írjuk ki. Időigény O(N log K), ahol K a felhasználók száma.
*/
/*
Hint 1: || Minden felhasználóra elég egy állapotot tárolni: bent van-e, és ha igen, mikor jelentkezett be. Az összesített idő ezekből a bejelentkezés–kijelentkezés párokból adódik. ||
Hint 2: || Ha az első adat egy kijelentkezés, a felhasználó már a nap 0:00 pillanatától bent van. Az érvénytelen műveleteket (már bent lévő be, kint lévő ki) hagyd figyelmen kívül. ||
Hint 3: || Az azonosítókhoz rendelj sorszámot az első előfordulásuk sorrendjében, így a kiírás időrendben megy. A nap végén még bent lévőknél a záró időpont 24 * 60 = 1440 perc. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    map<string, int> idx;     // azonosító -> sorszáma (az első előfordulás sorrendjében)
    vector<string> names;     // azonosítók a sorszámuk szerint
    vector<int> inside;       // 1, ha a felhasználó éppen bent van
    vector<int> since;        // a bejelentkezés időpontja percben
    vector<long long> total;  // összesített rendszeridő percben

    for (int i = 0; i < n; i++) {
        string op, user;
        int h, m;
        cin >> op >> user >> h >> m;
        int t = h * 60 + m;

        int u;
        auto it = idx.find(user);
        if (it == idx.end()) {
            u = (int)names.size();
            idx[user] = u;
            names.push_back(user);
            // kijelentkezéssel kezdődik: az előző napról még bent van, a nap 0:00-tól
            inside.push_back(op == "KI" ? 1 : 0);
            since.push_back(0);
            total.push_back(0);
        } else {
            u = it->second;
        }

        if (op == "BE" && !inside[u]) {
            inside[u] = 1;
            since[u] = t;
        } else if (op == "KI" && inside[u]) {
            total[u] += t - since[u];
            inside[u] = 0;
        }
        // a többi (sikertelen) művelet nincs hatással
    }

    // a nap végén még bent lévők a 24:00 pillanatáig dolgoznak
    for (int u = 0; u < (int)names.size(); u++) {
        if (inside[u]) total[u] += 24 * 60 - since[u];
    }

    long long best = -1;
    for (long long x : total) best = max(best, x);

    bool first = true;
    for (int u = 0; u < (int)names.size(); u++) {
        if (total[u] != best) continue;
        if (!first) cout << ' ';
        cout << names[u];
        first = false;
    }
    cout << '\n';
    return 0;
}
