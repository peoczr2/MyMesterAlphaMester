/*
Megoldás lényege: az utasok csak az érkezési idejük alapján különböznek, ezért nem egyesével, hanem időegységenként darabszámmal szimuláljuk az állomást. Az utcai sorból időegységenként legfeljebb 2 fő lép a lefelé menő lépcsőre, és a lépcső K időegység múlva engedi be őket a váróterembe, ezért a beérkezéseket egy K-val eltolt tömbben tároljuk. Minden időegységben előbb a metró (M-enként) viszi el a váróteremben addig összegyűlt utasokat, utána jönnek a lépcsőről érkezők, és csak ezután lép a lépcsőre a következő két utas; ha a váróterem kapacitása túllépődne, a szimuláció megáll. A szimuláció O(N+K+M) időben fut.
*/
/*
Hint 1: || Az utcai sorban az utasok csak darabszámként számítanak: minden időegységben annyi lép a lépcsőre, amennyi legfeljebb 2-t és a sorban várók számát engedi. ||
Hint 2: || A lépcsőre lépés időpontjából K időegységet kell hozzáadni a váróterembe érkezés időpontjához, ezért érdemes egy K-val eltolt tömbben tárolni, hány utas érkezik a váróterembe. ||
Hint 3: || Egy időegységen belül a sorrend számít: előbb a metró viszi el a korábban érkezett utasokat, utána érkeznek be az aktuális időegységben a váróterembe lépők, és csak ezután lép be a lépcsőre a következő csoport. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, k, l, m, u;
    cin >> n >> k >> l >> m >> u;
    vector<long long> arrivals(n + 1, 0);
    for (long long i = 0; i < u; ++i) {
        long long a;
        cin >> a;
        arrivals[a]++;
    }

    long long last = n + k + m;
    vector<long long> toRoom(last + k + 2, 0);
    long long street = 0;
    long long room = 0;
    vector<long long> served;

    for (long long t = 0; t <= last; ++t) {
        if (t > 0 && t % m == 0) {
            served.push_back(room);
            room = 0;
        }
        room += toRoom[t];
        if (room > l) break;

        if (t <= n) street += arrivals[t];
        long long enter = min(2LL, street);
        street -= enter;
        toRoom[t + k] += enter;
    }

    cout << served.size() << '\n';
    for (size_t i = 0; i < served.size(); ++i) {
        if (i) cout << ' ';
        cout << served[i];
    }
    cout << '\n';
    return 0;
}
