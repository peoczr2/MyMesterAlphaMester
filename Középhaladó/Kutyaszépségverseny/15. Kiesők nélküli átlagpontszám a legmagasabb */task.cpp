/*
Megoldás lényege:
Kieső egy kutya az adott szempont szerint, ha a pontja kisebb a szempont alsó ponthatáránál. A kiesést szempontonként külön kell vizsgálni, így egy kutya attól még beleszámít más szempontok átlagába.
Szempontonként csak a ponthatárt elérő kutyák pontjait összegezzük és számoljuk, így kapjuk a kiesők nélküli átlagot. Azokat a szempontokat, ahol nincs ilyen kutya, nem hasonlítjuk össze. A legnagyobb átlagú szempont sorszámát írjuk ki, egyenlőség esetén a legkisebbet; ha egyik szempontnál sincs bent maradó kutya, -1 a válasz.
Az átlagokat tört nélkül, keresztbe szorzással hasonlítjuk össze. Az idő O(N·M), a memóriaigény O(M).
*/
/*
Hint 1: || Szempontonként külön dől el, ki számít kiesőnek: a j. szempontban a kutya akkor marad bent, ha a j. pontja eléri a j. szempont alsó ponthatárát. ||
Hint 2: || Szempontonként gyűjtsd az összeget és a darabszámot csak a bent maradók pontjaira. Két átlag összehasonlításához keresztbe szorzást használj: a/b > c/d pontosan akkor, ha a·d > c·b (b, d > 0). ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> maxPont(m), minPont(m);
    for (int &x : maxPont) cin >> x;
    for (int &x : minPont) cin >> x;

    vector<int> osszeg(m, 0), db(m, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            int p;
            cin >> p;
            if (p >= minPont[j]) {
                osszeg[j] += p;
                db[j]++;
            }
        }

    int legjobb = -1;
    for (int j = 0; j < m; j++) {
        if (db[j] == 0) continue;
        if (legjobb == -1 || osszeg[j] * db[legjobb] > osszeg[legjobb] * db[j])
            legjobb = j;
    }

    cout << (legjobb == -1 ? -1 : legjobb + 1) << '\n';
    return 0;
}
