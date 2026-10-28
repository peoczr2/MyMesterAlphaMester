/*
Megoldás lényege:
Egy helységben a „féle madár” a különböző fajok számát jelenti, vagyis azoknak a fajoknak a számát, amelyekből legalább egy egyedet láttak. Soronként olvassuk be a számokat, és minden helységhez megszámoljuk a nullától különböző darabszámokat. Ezután kiválasztjuk a legkisebb számlálójú helységet. Ha több helység is ugyanannyi fajt lát, a legkisebb sorszámút írjuk ki, ez egyezik a példával. Mivel minden helységhez csak egy számlálót tárolunk, a memóriaigény O(M), az idő O(M·N).
*/
/*
Hint 1: || Egy helységhez csak azt kell tudnod, hány olyan faj van, amelyből legalább egy egyed fordult elő. Ehhez elég a sort egyszer végigolvasni és a nullától különböző számokat megszámolni. ||
Hint 2: || Tárolj M darab számlálót, és beolvasás közben minden nullától különböző szám után növeld a megfelelő helység számlálóját. A végén keresd meg a legkisebb számlálójú helységet, holtversenynél a kisebb sorszámút válaszd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;

    vector<int> fajszam(M + 1, 0);
    for (int i = 1; i <= M; ++i) {
        for (int j = 0; j < N; ++j) {
            int e;
            cin >> e;
            if (e > 0) ++fajszam[i];
        }
    }

    int legjobb = 1;
    for (int i = 2; i <= M; ++i) {
        if (fajszam[i] < fajszam[legjobb]) legjobb = i;
    }

    cout << legjobb << '\n';
    return 0;
}
