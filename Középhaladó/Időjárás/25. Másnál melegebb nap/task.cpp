/*
Megoldás lényege:
Egy d nap akkor felel meg, ha van olyan e (e ≠ d) nap, amelyre minden településen H[i][d] > H[i][e]. Minden d naphoz egy bitsetben tároljuk azokat az e napokat, amelyek eddig minden településen szigorúan kisebbek voltak; kezdetben minden nap jelölt. Településenként a napokat hőmérséklet szerint csoportosítjuk (a -50 és 50 közötti értékek miatt 101 csoport elég), és sorban haladva a már bejárt, kisebb értékű napokat egy bitsetben gyűjtjük, és ezt metsszük (ÉS) a d napok bitsetjével. Az egyenlő értékű napok nem számítanak kisebbnek, ezért a csoport tagjait előbb metsszük, és csak utána tesszük be a halmazba. A végén a legkisebb olyan d sorszámot írjuk ki, amelyhez a halmaz nem üres, különben -1-et. Az idő O(N·M + N·M²/64), ami a naiv O(N·M²) helyett gyors.
*/
/*
Hint 1: || Egy d nap akkor felel meg, ha van olyan másik e nap, amelyre minden településen d-re magasabb hőmérsékletet jósolnak. A feltétel tehát napok párjaira vonatkozik, de nem kell minden párt külön, településről településre végigellenőrizni. ||
Hint 2: || A páronkénti ellenőrzés N·M² ≈ 10⁹ műveletet jelent, ami 0,1 mp alatt nem fér bele. Érdemes településenként haladni, és egy településen belül azt gondolni végig, mely napok lehetnek szigorúan kisebbek egy adott napnál. ||
Hint 3: || Egy településen a hőmérséklet szerint csoportosított napokon sorban haladva tartsd nyilván a már bejárt, kisebb értékű napokat egy bitsetben. Minden napra egy másik bitsetben tárold azokat az e napokat, amelyek eddig minden településen kisebbek voltak, és ezt metszd a bitsettel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // ok[d]: azon napok halmaza, amelyek eddig minden településen kisebbek voltak d-nél
    vector<bitset<1000>> ok(m);
    for (int d = 0; d < m; d++) ok[d].set();

    // csoport[v+50]: azon napok, amelyeken az aktuális településnek v a hőmérséklete
    vector<vector<int>> csoport(101);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int h;
            cin >> h;
            csoport[h + 50].push_back(j);
        }

        // kisebb: azok a napok, amelyeken ennél a településnél szigorúan kisebb a hőmérséklet
        bitset<1000> kisebb;
        for (auto& cs : csoport) {
            for (int d : cs) ok[d] &= kisebb;
            for (int d : cs) kisebb.set(d);
            cs.clear();
        }
    }

    for (int d = 0; d < m; d++) {
        if (ok[d].any()) {
            cout << d + 1 << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';
    return 0;
}
