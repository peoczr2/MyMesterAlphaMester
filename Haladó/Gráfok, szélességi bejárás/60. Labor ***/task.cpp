/*
Megoldás lényege:
A tele és az üres kémcsövek értéke a mozgásokban nem tud újat létrehozni: tele kémcsőből
öntve a részlegesen töltött érték csak átkerül egy másik kémcsőbe. Így csak a részlegesen
töltött kémcsövek értékei számítanak, és ezek egymás közti összevonással változnak: két
ilyen kémcső összege megmarad, ha legfeljebb K, és az egyik kiürül; különben az egyik tele
lesz, a másikban pedig az összeg K-val csökkentve marad. Ezért minden részlegesen töltött
érték a kezdeti részlegesen töltött értékek egy nemüres részhalmazának összege modulo K.
Ezeket egy K hosszúságú bitsettel gyűjtjük: minden kezdeti értéknél a halmazt eltoljuk
p-vel modulo K. A 0 akkor szerepel, ha N nagyobb a legkevesebb nemüres kémcsövet igénylő
számnál (ceil(S/K)); a K akkor, ha az összes víz S legalább K. Az időigény O(N·K/64).
*/
/*
Hint 1: || Figyeld meg, mi történik a tele és az üres kémcsövekkel: az öntögetés a részlegesen töltött kémcsövek tartalmát tudja csak összevonni. ||
Hint 2: || Két részlegesen töltött kémcső összeöntésekor, ha összegük legfeljebb K, az egyik kiürül; ha több lenne, az egyik tele lesz, a másikban pedig az összeg K-val csökkentve marad. ||
Hint 3: || A lehetséges részlegesen töltött értékek a kezdeti részlegesen töltött értékek nemüres részhalmazainak összege modulo K; ezt bitsettel gyűjtsd, és minden értéknél tolással bővítsd a halmazt. ||
Hint 4: || Az üres kémcső akkor marad, ha N nagyobb, mint az összes víz K-val felfelé osztott értéke; a K pedig akkor szerepel, ha az összes víz legalább K. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAXK = 100000;

    int n, k;
    cin >> n >> k;

    vector<int> partial;
    long long total = 0;
    for (int i = 0; i < n; ++i) {
        int u;
        cin >> u;
        total += u;
        if (u > 0 && u < k) partial.push_back(u);
    }

    // reach[s] = 1, ha van olyan részhalmaz, amelynek összege modulo K éppen s.
    bitset<MAXK> reach, mask;
    reach[0] = 1;
    for (int i = 0; i < k; ++i) mask[i] = 1;
    for (int p : partial) {
        reach |= ((reach << p) | (reach >> (k - p))) & mask;
    }

    vector<long long> values;
    long long minNonEmpty = (total + k - 1) / k;
    if (n > minNonEmpty) values.push_back(0);
    for (int v = 1; v < k; ++v) {
        if (reach[v]) values.push_back(v);
    }
    if (total >= k) values.push_back(k);

    cout << values.size() << '\n';
    for (size_t i = 0; i < values.size(); ++i) {
        if (i) cout << ' ';
        cout << values[i];
    }
    cout << '\n';
    return 0;
}
