/*
Megoldás lényege:
Egy település akkor felel meg, ha a hőmérséklet legalább 7 egymás utáni napon át szigorúan nő, azaz van 7 egymást követő növekvő lépés. Soronként egy számlálóval mérjük az aktuális növekvő sorozat hosszát: ha a mai érték nagyobb a tegnapinál, nő, különben nullázódik. Amint a számláló eléri a 7-et, a település bekerül a listába. A sor végéig minden értéket be kell olvasni, hogy a következő település adatai ne csússzanak el. Az idő O(N·M), a memória O(N).
*/
/*
Hint 1: || Egy település akkor felel meg, ha a napi hőmérséklet legalább 7 egymás utáni napon át nő, vagyis legalább 7 egymást követő szigorúan növekvő lépés van. Itt nem a hőmérséklet nagysága, hanem a változás iránya a fontos. ||
Hint 2: || Tarts nyilván egy számlálót, amely az aktuális növekvő sorozat hosszát adja: ha a mai érték nagyobb a tegnapinál, nő, különben nullázódik. Ha eléri a 7-et, a település megfelel, de a sor többi értékét is végig kell olvasni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> melegebb;
    for (int i = 1; i <= n; i++) {
        int elozo;
        cin >> elozo;
        int futas = 0;
        bool megfelel = false;
        for (int j = 1; j < m; j++) {
            int h;
            cin >> h;
            futas = (h > elozo) ? futas + 1 : 0;
            if (futas >= 7) megfelel = true;
            elozo = h;
        }
        if (megfelel) melegebb.push_back(i);
    }

    cout << melegebb.size();
    for (int s : melegebb) cout << ' ' << s;
    cout << '\n';
    return 0;
}
