/*
Ötlet:
Pontosan a nyitva levő ládák töltöttségét kell nyomon követni. Ha még csak egy láda van nyitva,
akkor elég annak súlyát tárolni. Ha már kettő nyitva van, akkor a két súlyt rendezetten kezeljük:
legyen x <= y.

Egyládás állapot:
- one_cost: ennyi ládát használtunk eddig minimum,
- one_load: az egyetlen nyitott láda aktuális töltése ennél a minimumhoz.

Kétládás állapot:
- two_cost[x]: az első i tárgy után, ha a kisebbik nyitott láda töltése x, akkor minimálisan hány
  ládát kellett eddig használni.
- two_big[x]: ugyanehhez a minimumhoz tartozó lehető legkisebb nagyobbik töltés.

Miért elég egy adott x-hez csak a legkisebb y-t megtartani?
Mert ugyanannyi felhasznált láda mellett a kisebb y minden jövőbeli lépésre legalább olyan jó:
abba minden olyan tárgy belefér, ami egy nagyobb y-hoz még beleférne, és a csere-műveletek is ugyanazok.
Ha pedig valaki ugyanahhoz az x-hez már több ládát használt el, az sem lehet jobb, mert a jövőben
ugyanazokat a műveleteket végezheti, csak rosszabb induló költséggel.

Átmenetek az aktuális w súlyú tárgyra:
- berakjuk az egyik nyitott ládába, ha belefér,
- vagy bezárjuk az egyik nyitott ládát, nyitunk helyette egy újat, és ebbe rakjuk w-t.

Ez pontosan a feladat összes megengedett lépése, tehát a DP egzakt. Az állapottér mérete O(S),
minden tárgyra O(S) átmenetet próbálunk, így az idő O(N*S), a memória O(S).
*/
/*
Hint 1: || Kezeld külön azt az esetet, amikor még csak egy láda van nyitva, és azt, amikor már kettő. ||
Hint 2: || Két nyitott ládánál rendezd a töltéseket x <= y alakba, így ugyanaz az állapot nem jelenik meg kétszer. ||
Hint 3: || Rögzített kisebbik töltés mellett csak a legkisebb nagyobbik töltés érdekes. ||
Hint 4: || Az új tárgynál pontosan négy lehetőség van: elsőbe rak, másodikba rak, elsőt cseréli, másodikat cseréli. ||
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int s, n;
    cin >> s >> n;

    const int INF = 1e9;
    vector<int> two_cost(s + 1, INF), two_big(s + 1, INF);
    vector<int> next_two_cost(s + 1, INF), next_two_big(s + 1, INF);

    int one_cost = 0;
    int one_load = 0;

    auto relax_one = [](int load, int cost, int &best_cost, int &best_load) {
        if (cost < best_cost || (cost == best_cost && (best_load == -1 || load < best_load))) {
            best_cost = cost;
            best_load = load;
        }
    };

    auto relax_two = [](int x, int y, int cost, vector<int> &costs, vector<int> &bigs) {
        if (cost < costs[x] || (cost == costs[x] && y < bigs[x])) {
            costs[x] = cost;
            bigs[x] = y;
        }
    };

    for (int i = 0; i < n; ++i) {
        int w;
        cin >> w;

        fill(next_two_cost.begin(), next_two_cost.end(), INF);
        fill(next_two_big.begin(), next_two_big.end(), INF);

        int next_one_cost = INF;
        int next_one_load = -1;

        if (one_cost < INF) {
            if (one_load == 0) {
                relax_one(w, 1, next_one_cost, next_one_load);
            } else {
                if (one_load + w <= s) {
                    relax_one(one_load + w, one_cost, next_one_cost, next_one_load);
                }

                int x = min(one_load, w);
                int y = max(one_load, w);
                relax_two(x, y, one_cost + 1, next_two_cost, next_two_big);
            }
        }

        for (int x = 1; x <= s; ++x) {
            if (two_cost[x] == INF) {
                continue;
            }

            int used = two_cost[x];
            int y = two_big[x];

            if (x + w <= s) {
                int nx = x + w;
                int ny = y;
                if (nx > ny) {
                    swap(nx, ny);
                }
                relax_two(nx, ny, used, next_two_cost, next_two_big);
            }

            if (y + w <= s) {
                int nx = x;
                int ny = y + w;
                if (nx > ny) {
                    swap(nx, ny);
                }
                relax_two(nx, ny, used, next_two_cost, next_two_big);
            }

            {
                int nx = min(w, y);
                int ny = max(w, y);
                relax_two(nx, ny, used + 1, next_two_cost, next_two_big);
            }

            {
                int nx = min(x, w);
                int ny = max(x, w);
                relax_two(nx, ny, used + 1, next_two_cost, next_two_big);
            }
        }

        one_cost = next_one_cost;
        one_load = next_one_load;
        two_cost.swap(next_two_cost);
        two_big.swap(next_two_big);
    }

    int answer = one_cost;
    for (int x = 1; x <= s; ++x) {
        answer = min(answer, two_cost[x]);
    }

    cout << answer << '\n';
    return 0;
}