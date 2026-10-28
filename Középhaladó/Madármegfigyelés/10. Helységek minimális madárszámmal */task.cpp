/*
Megoldás lényege:
Egy helység madárszáma a sorában lévő darabszámok összege. Először minden helységre kiszámoljuk
ezt az összeget, majd megkeressük a legkisebb értéket. Végül kiírjuk, hány helység éri el a
minimumot, és azok sorszámát növekvő sorrendben. Az összegek legfeljebb 200 000 lehetnek, így
egy egyszerű összegzés elég, és a beolvasás gyorsan lefut.
*/
/*
Hint 1: || Egy helység madárszámát úgy kapod meg, hogy a sorában lévő összes számot összeadod. Utána már csak a legkisebb összeget kell megtalálni. ||
Hint 2: || Tárold el minden helység összegét egy tömbben (1-től indexelve), számold ki a minimumot, majd második lépésben gyűjtsd ki a minimummal egyező összegű helységek sorszámait. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;

    vector<long long> osszeg(M + 1, 0);
    for (int i = 1; i <= M; ++i) {
        for (int j = 0; j < N; ++j) {
            long long e;
            cin >> e;
            osszeg[i] += e;
        }
    }

    long long minimum = *min_element(osszeg.begin() + 1, osszeg.end());
    vector<int> helysegek;
    for (int i = 1; i <= M; ++i) {
        if (osszeg[i] == minimum) helysegek.push_back(i);
    }

    cout << helysegek.size() << '\n';
    for (size_t k = 0; k < helysegek.size(); ++k) {
        if (k) cout << ' ';
        cout << helysegek[k];
    }
    cout << '\n';
    return 0;
}
