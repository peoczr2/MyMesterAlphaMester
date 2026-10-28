/*
Megoldás lényege:
Egy település akkor felel meg, ha a hőmérséklet legalább 7 egymást követő napon át szigorúan csökken, azaz van 7 egymás utáni csökkenő lépés. Soronként egy számlálóval mérjük az aktuális csökkenő sorozat hosszát: csökkenésnél nő, különben nullázódik. Ha a számláló eléri a 7-et, a település bekerül a listába. A sor végéig minden értéket be kell olvasni, hogy a következő település adatai ne csússzanak el. Az idő O(N·M), a memória O(N).
*/
/*
Hint 1: || Egy település akkor felel meg, ha a napi hőmérséklet legalább 7 egymás utáni napon át csökken, vagyis legalább 7 egymást követő csökkenő lépés van. Egy-egy napon belül nem a hőmérséklet nagysága, hanem a változás iránya a fontos. ||
Hint 2: || Tarts nyilván egy számlálót, amely az aktuális csökkenő sorozat hosszát adja: csökkenésnél nő, különben nullázódik. Ha eléri a 7-et, a település megfelel, de a sor többi értékét is végig kell olvasni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> hideg;
    for (int i = 1; i <= n; i++) {
        int elozo;
        cin >> elozo;
        int futas = 0;
        bool megfelel = false;
        for (int j = 1; j < m; j++) {
            int h;
            cin >> h;
            futas = (h < elozo) ? futas + 1 : 0;
            if (futas >= 7) megfelel = true;
            elozo = h;
        }
        if (megfelel) hideg.push_back(i);
    }

    cout << hideg.size();
    for (int s : hideg) cout << ' ' << s;
    cout << '\n';
    return 0;
}
