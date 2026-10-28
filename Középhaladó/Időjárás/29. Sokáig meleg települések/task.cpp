/*
Megoldás lényege:
Egy település akkor felel meg, ha legalább 7 egymás utáni napon a hőmérséklet 30 fok felett van, vagyis szigorúan nagyobb 30-nál. Soronként egy számlálóval mérjük az aktuális, 30 fok feletti napokból álló sorozat hosszát: ha a nap hőmérséklete nagyobb 30-nál, nő, különben nullázódik. Amint a számláló eléri a 7-et, a település bekerül a listába, de a sor többi értékét is be kell olvasni. Az idő O(N·M), a memória O(N).
*/
/*
Hint 1: || Egy település akkor felel meg, ha van legalább 7 egymást követő nap, amikor a hőmérséklete 30 fok felett van. Figyelj arra, hogy a pontosan 30 fokos érték nem számít „30 fok felettinek”. ||
Hint 2: || Soronként haladj végig a napokon, és tarts nyilván egy számlálót az aktuális 30 fok feletti sorozat hosszáról: ha a nap értéke nagyobb 30-nál, nő, különben nullázódik. Amint eléri a 7-et, a település megfelel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> meleg;
    for (int i = 1; i <= n; i++) {
        int futas = 0;
        bool megfelel = false;
        for (int j = 1; j <= m; j++) {
            int h;
            cin >> h;
            futas = (h > 30) ? futas + 1 : 0;
            if (futas >= 7) megfelel = true;
        }
        if (megfelel) meleg.push_back(i);
    }

    cout << meleg.size();
    for (int s : meleg) cout << ' ' << s;
    cout << '\n';
    return 0;
}
