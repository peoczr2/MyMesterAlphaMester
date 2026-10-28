/*
Megoldás lényege:
Kieső egy kutya az adott szempont szerint, ha a pontja kisebb a szempont alsó ponthatáránál. A kiesést szempontonként külön kell vizsgálni: egy kutya attól még bent maradhat más szempontokból.
Szempontonként összegezzük a kiesők pontjait és megszámoljuk őket, így kapjuk a kiesők átlagát. Azokat a szempontokat, ahol nincs kiesés, nem hasonlítjuk össze. A legnagyobb átlagú szempont sorszámát írjuk ki, egyenlőség esetén a legkisebbet; ha nincs egyetlen kiesés sem, -1 a válasz.
Az átlagokat tört nélkül, keresztbe szorzással hasonlítjuk össze. Az idő O(N·M), a memóriaigény O(M).
*/
/*
Hint 1: || Egy kutya a j. szempont szerint akkor esik ki, ha a j. pontja kisebb a j. szempont alsó ponthatáránál. Ezt minden (kutya, szempont) párra külön döntsd el, ne a kutya egészére. ||
Hint 2: || Szempontonként tarts nyilván két értéket: a kiesők pontösszegét és darabszámát. Két átlag összehasonlításához ne osztást végezz: a/b > c/d pontosan akkor, ha a·d > c·b (b, d > 0). ||
Hint 3: || Ha egyik szempontnál sincs kiesés, a darabszám minden szempontnál 0, és -1-et kell kiírni. A 0 darabszámú szempontokat ilyenkor ki kell hagyni az összehasonlításból. ||
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
            if (p < minPont[j]) {
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
