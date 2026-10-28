/*
Megoldás lényege: minden versenyző M pontszámát rendezzük, a legkisebb és a legnagyobb elem kimarad, a maradék
M-2 szám összege lesz a végeredménye. Ezután a versenyzőket csökkenő pontszám szerint, azonos pontszámnál
sorszám szerint rendezzük. A helyezési szám: ha a pontszám megegyezik az előző versenyzőével, átvesszük az ő
helyezését (holtverseny), különben a rendezett listabeli pozíció (1-től számolva) lesz a helyezés.
Időigény: O(N · M log M + N log N).
*/
/*
Hint 1: || Minden versenyzőnél külön számold ki a pontszámot: az M pontot rendezd, és a legkisebb és a legnagyobb
érték nélkül összegezz. ||
Hint 2: || A versenyzőket pontszám szerint csökkenő sorrendbe rendezd, azonos pontszámnál sorszám szerint növekvően.
Végigmenve a listán: ha az aktuális pontszám az előzővel egyezik, az előző helyezési számát vedd át, különben
az aktuális, 1-től számolt pozíció lesz a helyezés. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> score(n + 1, 0);
    vector<int> pts(m);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) cin >> pts[j];
        sort(pts.begin(), pts.end());
        int sum = 0;
        for (int j = 1; j < m - 1; j++) sum += pts[j];
        score[i] = sum;
    }

    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    sort(order.begin(), order.end(), [&](int a, int b) {
        if (score[a] != score[b]) return score[a] > score[b];
        return a < b;
    });

    int place = 0;
    for (int i = 0; i < n; i++) {
        int id = order[i];
        if (i == 0 || score[id] != score[order[i - 1]]) place = i + 1;
        cout << place << ' ' << id << ' ' << score[id] << '\n';
    }
    return 0;
}
