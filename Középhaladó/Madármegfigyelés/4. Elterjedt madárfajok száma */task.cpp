/*
Megoldás lényege:
Fajonként megszámoljuk, hány helységben fordult elő (legalább egy egyed). Egy faj akkor felel meg, ha ez a szám a helységek számának több mint 90%-a; ezt törtek nélkül, egész aritmetikával vizsgáljuk: 10·h > 9·M. A mátrixot soronként olvassuk be, így az idő O(M·N), a memóriaigény O(N).
*/
/*
Hint 1: || Egy fajhoz elég tudni, hány helységben fordult elő; az egyes darabszámok nagysága nem számít. ||
Hint 2: || A „több mint 90%” feltételt írd fel egész számokkal: ha a faj h helységben volt, akkor 10·h > 9·M. Így nem kell törtekkel dolgoznod. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;
    vector<int> helyekSzama(N, 0);
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j) {
            int e;
            cin >> e;
            if (e > 0) ++helyekSzama[j];
        }

    int db = 0;
    for (int j = 0; j < N; ++j)
        if (10 * helyekSzama[j] > 9 * M) ++db;

    cout << db << '\n';
    return 0;
}
