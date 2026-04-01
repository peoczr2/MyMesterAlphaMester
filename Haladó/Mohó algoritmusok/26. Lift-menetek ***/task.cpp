/*
Feladat: Adott K kapacitású lift minden menetben felmegy a legfelső szintre, majd lejön. Minden utast el kell szállítani, a menetek számát minimalizáljuk.
Ötlet: Egy fix menetnél az adott irányban minden él (szintek közti szakasz) legfeljebb K utast vihet át. Ezért az összes szükséges menet legalább annyi, mint bármelyik él terhelésének plafonja K-val osztva. Felfelé és lefelé külön kiszámítjuk az élek összterhelését különbségtömbbel, majd a válasz a két irányban kapott alsó korlát maximuma. Ez elérhető is, ezért optimális.
Hint 1: || Nézd meg, egy adott szintközön (i és i+1 között) összesen hány utasnak kell áthaladnia felfelé, illetve lefelé. ||
Hint 2: || Egy menetben egy szintközön legfeljebb K utas mehet át, tehát erre az élre legalább ceil(terhelés / K) menet kell. ||
Hint 3: || Külön számold a felfelé és lefelé menő igényeket, és vedd a két szükséges menetszám maximumát. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<long long> diffUp(N + 3, 0), diffDown(N + 3, 0);

    for (int floor = 1; floor <= N; ++floor) {
        while (true) {
            int to;
            cin >> to;
            if (to == 0) break;
            if (to > floor) {
                // Felfelé: [floor, to) szintközökön halad át.
                diffUp[floor] += 1;
                diffUp[to] -= 1;
            } else if (to < floor) {
                // Lefelé: (to, floor] szintközökön halad át.
                diffDown[to + 1] += 1;
                diffDown[floor + 1] -= 1;
            }
        }
    }

    long long maxUp = 0, cur = 0;
    for (int e = 1; e <= N - 1; ++e) {
        cur += diffUp[e];
        maxUp = max(maxUp, cur);
    }

    long long maxDown = 0;
    cur = 0;
    for (int e = 1; e <= N - 1; ++e) {
        cur += diffDown[e];
        maxDown = max(maxDown, cur);
    }

    auto need = [&](long long x) -> long long {
        return (x + K - 1) / K;
    };

    cout << max(need(maxUp), need(maxDown)) << '\n';
    return 0;
}
