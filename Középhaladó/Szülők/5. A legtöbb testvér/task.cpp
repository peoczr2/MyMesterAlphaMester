/*
A feladatban minden emberhez eltároljuk a szüleit és a gyermekeit. Egy ember testvéreinek száma
úgy kapható meg, hogy végigmegyünk az összes szülőjén, és az adott szülő összes gyermekét megjelöljük.
A saját magát kihagyjuk, a megjelölt emberek száma pedig a testvérek száma lesz. Mivel N legfeljebb
1000, ezért ezt minden emberre külön végig lehet csinálni.
*/
/*
Hint 1: || Egy ember testvérei azok, akikkel legalább egy közös szülőt oszt meg. ||
Hint 2: || Érdemes minden emberhez eltárolni a szüleit és a szülőkhöz a gyereklistát is. ||
Hint 3: || Egy jelölő tömbbel könnyen megszámolhatók az ismétlődés nélkül megjelenő testvérek. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<vector<int>> gyerekek(N + 1), szulok(N + 1);
    for (int i = 0; i < K; ++i) {
        int sz, gy;
        cin >> sz >> gy;
        gyerekek[sz].push_back(gy);
        szulok[gy].push_back(sz);
    }

    vector<int> testverek(N + 1, 0);
    for (int szemely = 1; szemely <= N; ++szemely) {
        vector<char> jelolt(N + 1, false);
        for (int szulo : szulok[szemely]) {
            for (int gy : gyerekek[szulo]) {
                if (gy != szemely) jelolt[gy] = true;
            }
        }
        for (int masik = 1; masik <= N; ++masik) {
            if (jelolt[masik]) ++testverek[szemely];
        }
    }

    int legjobb = 1;
    for (int i = 2; i <= N; ++i) {
        if (testverek[i] > testverek[legjobb]) legjobb = i;
    }

    cout << legjobb << '\n';
    return 0;
}
