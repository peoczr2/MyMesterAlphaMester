/*
Megoldás lényege:
Minden művelet (forgatás vagy átmenet) egy lépésnek számít, ezért a feladat a legkisebb költségű út keresése.
A jármű állapota a cellája és a cella sínének tengelye (vízszintes vagy függőleges). Egy szomszédos cellába
csak akkor mehet át, ha az aktuális és a célcella sínje ugyanabban a tengelyben áll; ehhez mindkét cellát
szükség esetén egy-egy forgatással be kell állítani. Így az átmenet költsége 1 + [az aktuális cella rossz
irányú] + [a célcella rossz irányú], vagyis 1, 2 vagy 3. Egy optimális útban nem kell olyan cellába
visszatérni, amelyet már elhagytunk, ezért minden átmenetnél a cella eredeti sínállását vehetjük alapul.
A súlyozott legrövidebb utat Dijkstra-algoritmussal számoljuk; a jobb alsó cella két állapota közül a kisebb
távolság a válasz, ha nincs elérhető állapot, akkor -1. Az időigény O(MN log(MN)).
*/
/*
Hint 1: || A forgatás nem mozgatja a járművet, csak beállítja a sínt. Ezért a jármű állapota a cellája és a cellán lévő sín iránya, vagyis minden cellához két állapot tartozik. ||
Hint 2: || Két szomszédos cella között akkor lehet átmenni, ha mindkét cellán ugyanolyan irányú (vízszintes vagy függőleges) sín áll. A rossz irányú cella beállítása mindig pontosan 1 lépés, és ezt az átmenet előtt kell elvégezned. ||
Hint 3: || Az átmenetek költsége 1, 2 vagy 3 lehet, ezért a sima szélességi bejárás nem ad helyes választ. Súlyozott legrövidebb utat keress: minden (cella, irány) párra tárold a legkisebb eddigi lépésszámot, és prioritásos sorral dolgozz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    vector<int> palya(m * n);
    for (int i = 0; i < m * n; i++) cin >> palya[i];

    int kezdo = 0, cel = m * n - 1;
    if (kezdo == cel) {
        cout << 0 << '\n';
        return 0;
    }

    // Állapot: (cella, a cella sínének tengelye). A tengely 0 = vízszintes, 1 = függőleges
    const int VEGTELEN = INT_MAX;
    vector<int> tav(2 * m * n, VEGTELEN);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    if (palya[kezdo] != 0) {
        int tengely = palya[kezdo] - 1;
        tav[2 * kezdo + tengely] = 0;
        pq.push({0, 2 * kezdo + tengely});
    }

    // Irányok: jobbra, balra, lefelé, felfelé; a mozgás tengelye vízszintes (0) vagy függőleges (1)
    const int dr[4] = {0, 0, 1, -1};
    const int dc[4] = {1, -1, 0, 0};
    const int tengelyIrany[4] = {0, 0, 1, 1};

    while (!pq.empty()) {
        auto [d, allapot] = pq.top();
        pq.pop();
        if (d != tav[allapot]) continue;

        int c = allapot / 2, tengely = allapot % 2;
        int r = c / n, oszlop = c % n;
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = oszlop + dc[k];
            if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
            int celCella = nr * n + nc;
            if (palya[celCella] == 0) continue;

            int irany = tengelyIrany[k];
            // Az aktuális cella és a célcella forgatása (ha kell), majd maga az átmenet
            int koltseg = (tengely != irany) + 1 + ((palya[celCella] - 1) != irany);
            int uj = d + koltseg;
            int ujAllapot = 2 * celCella + irany;
            if (uj < tav[ujAllapot]) {
                tav[ujAllapot] = uj;
                pq.push({uj, ujAllapot});
            }
        }
    }

    int valasz = min(tav[2 * cel], tav[2 * cel + 1]);
    cout << (valasz == VEGTELEN ? -1 : valasz) << '\n';
    return 0;
}
