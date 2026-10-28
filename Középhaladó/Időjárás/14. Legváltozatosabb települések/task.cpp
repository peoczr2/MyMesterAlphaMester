/*
Megoldás lényege:
Egy település hőmérsékletének irányát a szomszédos napok különbségének előjele adja: +1 a növekedés, -1 a csökkenés.
Az egyenlő szomszédos napok (nulla különbség) nem változtatják az irányt, ezért ezeket kihagyjuk, és csak a nem nulla különbségek előjelét követjük.
Irányváltás akkor van, amikor két egymást követő nem nulla különbség előjele eltér, vagyis növekedés után csökkenés, vagy csökkenés után növekedés.
Soronként egyetlen bejárással megszámoljuk minden település irányváltásait, majd kiírjuk azoknak a településeknek a sorszámát, ahol ez a szám a legnagyobb, növekvő sorrendben.
Az idő O(N · M).
*/
/*
Hint 1: || Ne a hőmérsékletek értékeit, hanem a napról napra bekövetkező változás irányát figyeld: növekedés, csökkenés vagy egyenlő. ||
Hint 2: || Tartsd nyilván az utolsó nem nulla változás irányát, és ha egy új nem nulla változás iránya eltér ettől, számold eggyel többnek az irányváltásokat. Az egyenlő szomszédos napokat hagyd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> changes(n, 0);
    for (int i = 0; i < n; i++) {
        vector<int> row(m);
        for (int j = 0; j < m; j++)
            cin >> row[j];

        int last = 0;
        int cnt = 0;
        for (int j = 1; j < m; j++) {
            int d = row[j] - row[j - 1];
            if (d == 0)
                continue;
            int dir = d > 0 ? 1 : -1;
            if (last != 0 && dir != last)
                cnt++;
            last = dir;
        }
        changes[i] = cnt;
    }

    int best = *max_element(changes.begin(), changes.end());
    vector<int> chosen;
    for (int i = 0; i < n; i++)
        if (changes[i] == best)
            chosen.push_back(i + 1);

    cout << chosen.size();
    for (int x : chosen)
        cout << ' ' << x;
    cout << '\n';
    return 0;
}
