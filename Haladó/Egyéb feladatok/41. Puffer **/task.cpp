/*
Megoldás lényege:
A csomagokat érkezési sorrendben dolgozzuk fel, és nyilvántartjuk, hogy az 1..P sorszámú byte-ok már továbbításra kerültek. Ha egy csomag a-1 <= P, azonnal kiadható, P-t megnöveljük, majd a pufferből addig vesszük ki a csatlakozó csomagokat, amíg a legkisebb kezdő byte legfeljebb P+1. A puffert kezdő byte szerinti minimum-kupacban tároljuk, így a következő csatlakozó csomag mindig a kupac tetején van. Ha a csomag nem csatlakozik, bekerül a pufferbe, és a puffer aktuális bájtszámát frissítjük. A válasz a puffer bájtszámának maximuma a folyamat során, a működés O(N log N).
*/
/*
Hint 1: || Elég nyilván tartani, hogy az 1..P sorszámú byte-ok már továbbítva vannak. Egy a sorszámú csomag akkor adható ki azonnal, ha a-1 <= P. ||
Hint 2: || A kiadás után a pufferben lévő csomagok közül mindig a legkisebb kezdő byte-ú lehet a következő csatlakozó. Ehhez minimum-kupac kell a pufferben lévő csomagoknak. ||
Hint 3: || A puffer méretét a benne lévő csomagok hosszának összegeként tartsd nyilván, és minden beérkező, pufferbe kerülő csomag után frissítsd a maximumot. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // Min-kupac: (kezdő byte, vég byte) a pufferben várakozó csomagokra.
    priority_queue<pair<long long, long long>, vector<pair<long long, long long>>,
                   greater<pair<long long, long long>>> buffer;

    long long done = 0;  // az 1..done sorszámú byte-ok már továbbítva vannak
    long long used = 0;  // a pufferben lévő csomagok bájtjainak száma
    long long best = 0;  // a puffer maximális mérete

    for (int i = 0; i < n; ++i) {
        long long a, b;
        cin >> a >> b;
        if (a > done + 1) {
            buffer.push({a, b});
            used += b - a + 1;
            best = max(best, used);
            continue;
        }
        done = max(done, b);
        while (!buffer.empty() && buffer.top().first <= done + 1) {
            auto [s, e] = buffer.top();
            buffer.pop();
            used -= e - s + 1;
            done = max(done, e);
        }
    }

    cout << best << '\n';
    return 0;
}
