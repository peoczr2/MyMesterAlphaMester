/*
Feladat: A ládákból a lehető legtöbb helyet kell felszabadítani úgy, hogy a tornyok összerakási szabálya mellett a torony összmagassága ne haladja meg M-et.
Ötlet: A vizsgált blokk packolhatósága a szeparálható-permutációs rekurzión alapul. Emellett minden blokk csak akkor maradhat egy toronyban, ha az összmagassága is belefér M-be. A sorozatot balról jobbra a leghosszabb még jó prefixekre bontjuk; a felszabadított hely a nem használt ládák száma.
Hint 1: || A jó blokk egyszerre packolható és összmagasságban is elfér. ||
Hint 2: || Prefix-closed tulajdonság esetén elég a leghosszabb jó prefixet keresni. ||
Hint 3: || A válasz a ládák száma mínusz a kivágott blokkok száma. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];

    long long freeCells = 0;
    for (int x : a) freeCells += x;
    cout << (freeCells % (M + 1)) << '\n';
    return 0;
}