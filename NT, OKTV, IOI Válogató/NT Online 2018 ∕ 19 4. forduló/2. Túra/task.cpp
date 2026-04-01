/*
Megoldás lényege:
Először egy előremenő greedy-vel eldöntjük, meddig lehet legfeljebb eljutni. Az
aktuális kikötőben mindig annyi élelmiszert tartunk a hajón, amennyi a következő
szakasz teljesítéséhez szükséges, de nem többet a kapacitásnál: ha a meglévő
készlet és az adott kikötőben felvehető mennyiség együtt sem elég, akkor ott ér
véget az út.

Ha az utolsó kikötő elérhető, akkor visszafelé számoljuk ki az egyes kikötőkben
felveendő minimális mennyiségeket. A következő kikötőhöz szükséges `need`
mennyi-séghez az aktuális szakasz teljesítéséhez `need + K_i` kell induláskor;
ebből legfeljebb `V_i` vehető fel, ezért az érkezéskor szükséges minimum
`max(0, need + K_i - V_i)`.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, h;
    cin >> n >> h;

    vector<int> v(n), k(n);
    for (int i = 1; i <= n - 1; ++i) cin >> v[i] >> k[i];

    int cur = 0;
    for (int i = 1; i <= n - 1; ++i) {
        if (cur + v[i] < k[i]) {
            cout << i << '\n';
            return 0;
        }
        cur = min(h, cur + v[i]) - k[i];
    }

    vector<int> need(n + 2, 0);
    vector<int> take(n + 2, 0);
    for (int i = n - 1; i >= 1; --i) {
        int req = need[i + 1] + k[i];
        need[i] = max(0, req - v[i]);
        take[i] = req - need[i];
    }

    for (int i = 1; i <= n - 1; ++i) {
        if (i > 1) cout << ' ';
        cout << take[i];
    }
    cout << '\n';
    return 0;
}
