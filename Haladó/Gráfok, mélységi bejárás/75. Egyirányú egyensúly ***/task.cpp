/*
Megoldás lényege:
Egy város terhelése a kimenő és a bejövő élek számának abszolút különbsége, és ennek paritása megegyezik a város fokszámának paritásával. Ezért minden páratlan fokú város terhelése legalább 1, így az összterhelés alsó korlátja a páratlan fokú városok száma. Ezt az alsó korlátot el is érjük: egy fiktív csúcsot kötünk minden páratlan fokú városhoz, így minden fok páros lesz. Ekkor minden csúcsból indulva addig lépünk a még nem használt éleken, amíg lehet, és az éleket abba az irányba irányítjuk, amerre bejártuk. Minden ilyen bejárás zárt séta, ezért a befok és a kifok minden csúcsnál egyenlő, a fiktív élek elhagyása után pedig a páratlan fokú városoknál pontosan 1 az eltérés. Az időigény O(N + M).
*/
/*
Hint 1: || Egy város terhelése kimenő és bejövő élek számának különbsége, és ennek paritása megegyezik a fokszám paritásával. Gondold végig, mekkora lehet legalább egy páratlan fokú város terhelése. ||
Hint 2: || Adj hozzá egy fiktív csúcsot, és kösd össze minden páratlan fokú várossal. Így minden fok páros lesz, és a fiktív élek elhagyása után az eredeti élek irányítását kapod. ||
Hint 3: || Minden csúcsból indulva járd be a még nem használt éleket, amíg lehet, és minden élt abba az irányba irányíts, amerre bejárod. Ezek zárt sétáknak felelnek meg, így befok = kifok. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> a(m), b(m), deg(n + 1, 0);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
        deg[a[i]]++;
        deg[b[i]]++;
    }

    // Fiktív csúcs: a 0. csúcs. Minden páratlan fokú városhoz egy él köti.
    vector<int> eu = a, ev = b;
    int odd = 0;
    for (int v = 1; v <= n; v++) {
        if (deg[v] % 2 == 1) {
            eu.push_back(0);
            ev.push_back(v);
            odd++;
        }
    }
    int total = (int)eu.size();

    vector<vector<int>> inc(n + 1);
    for (int e = 0; e < total; e++) {
        inc[eu[e]].push_back(e);
        inc[ev[e]].push_back(e);
    }

    vector<char> used(total, 0);
    vector<char> forward(m, 0);   // forward[i] = 1, ha a_i -> b_i
    vector<size_t> pos(n + 1, 0);

    for (int s = 0; s <= n; s++) {
        int cur = s;
        while (true) {
            while (pos[cur] < inc[cur].size() && used[inc[cur][pos[cur]]]) pos[cur]++;
            if (pos[cur] == inc[cur].size()) break;   // cur-nek nincs több szabad éle
            int e = inc[cur][pos[cur]];
            used[e] = 1;
            int nxt = (eu[e] == cur) ? ev[e] : eu[e];
            if (e < m) forward[e] = (cur == a[e]);
            cur = nxt;
        }
    }

    cout << odd << '\n';
    for (int i = 0; i < m; i++) {
        cout << (forward[i] ? "->" : "<-") << (i + 1 < m ? ' ' : '\n');
    }
    return 0;
}
