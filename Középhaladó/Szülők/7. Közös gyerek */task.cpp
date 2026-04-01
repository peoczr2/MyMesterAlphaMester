/*
A megoldás lényege, hogy minden emberhez eltároljuk a gyermekeit, illetve minden gyermekhez az őt
nevelő szülőket. A kérdezett Y személy közös gyerekes partnerei pontosan azok a személyek, akik Y
legalább egyik gyermekének másik szülői. Ezért elegendő végignézni Y összes gyermekét, és az összes
hozzájuk tartozó szülőt megjelölni. A legkisebb megjelölt sorszámot kell kiírni, ha pedig nincs ilyen,
akkor 0-t.
*/
/*
Hint 1: || Először gyűjtsd össze minden ember gyerekeit, és minden gyerekhez azt is, kik a szülei. ||
Hint 2: || Egy jelölő tömbbel Y gyerekeinek „másik szülei” egyszerűen megkereshetők. ||
Hint 3: || A legkisebb megfelelő sorszámhoz elég 1-től N-ig végigszkennelni a jelölő tömböt. ||
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

    int Y;
    cin >> Y;

    vector<char> jelolt(N + 1, false);
    for (int gy : gyerekek[Y]) {
        for (int szulo : szulok[gy]) {
            if (szulo != Y) jelolt[szulo] = true;
        }
    }

    for (int i = 1; i <= N; ++i) {
        if (jelolt[i]) {
            cout << i << '\n';
            return 0;
        }
    }

    cout << 0 << '\n';
    return 0;
}
