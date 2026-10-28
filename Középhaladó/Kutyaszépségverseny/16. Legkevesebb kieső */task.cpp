/*
Megoldás lényege:
Kieső egy kutya az adott szempont szerint, ha a pontja kisebb a szempont alsó ponthatáránál. Szempontonként megszámoljuk, hány kutya esik ki az adott szempont szerint.
A legkevesebb kieső szempont sorszámát írjuk ki. Egyenlőség esetén a kisebb sorszám marad, mert a minimumot csak szigorúan kisebb számláló írja felül.
Minden (kutya, szempont) párt egyszer vizsgálunk, így az idő O(N·M), a memóriaigény O(M).
*/
/*
Hint 1: || Egy (kutya, szempont) párnál elég eldönteni, hogy a pont kisebb-e a szempont alsó ponthatáránál. Ha igen, a szempont számlálóját növeld meg. ||
Hint 2: || Szempontonként egy számlálót tarts, majd keress minimumot. Az első legkisebb értékű szempontot tartsd meg, így egyenlőségnél automatikusan a legkisebb sorszámút kapod. ||
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

    vector<int> kieso(m, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            int p;
            cin >> p;
            if (p < minPont[j])
                kieso[j]++;
        }

    int legjobb = 0;
    for (int j = 1; j < m; j++)
        if (kieso[j] < kieso[legjobb])
            legjobb = j;

    cout << legjobb + 1 << '\n';
    return 0;
}
