/*
Megoldás lényege:
Először egy előremenő greedy-vel eldöntjük, meddig lehet legfeljebb eljutni. Az
aktuális kikötőben mindig annyi élelmiszert tartunk a hajón, amennyi a következő
szakasz teljesítéséhez szükséges, de nem többet a kapacitásnál: ha a meglévő
készlet és az adott kikötőben felvehető mennyiség együtt sem elég, akkor ott ér
véget az út.

Ha az utolsó kikötő elérhető, akkor visszafelé számoljuk ki az egyes kikötőkben
felveendő minimális mennyiségeket. A következő kikötőhöz szükséges `need`
mennyiséghez az aktuális szakasz teljesítéséhez `need + K_i` kell induláskor;
ebből legfeljebb `V_i` vehető fel, ezért az érkezéskor szükséges minimum
`max(0, need + K_i - V_i)`.
*/
/*
Hint 1: || Két menetben dolgozzunk: előre haladva ellenőrizzük, meddig jutunk el, majd visszafelé számoljuk ki a felveendő mennyiségeket. Ha valahol a készlet és a helyben felvehető mennyiség együtt nem elég a következő szakaszra, akkor az a kikötő lesz a kimenet, ahol az út véget ér. ||
Hint 2: || Visszafelé haladva legyen need az (i+1)-edik kikötőben érkezéskor szükséges mennyiség. Az i-edik kikötőből a szakasz teljesítéséhez need + K_i kell induláskor, és ebből legfeljebb V_i vehető fel, így az i-edik kikötőbe érkezéskor max(0, need + K_i - V_i) kell. ||
Hint 3: || Az utolsó kikötőben nincs további szükséglet, így a visszafelé számolás need = 0 értékkel indul. Ha az előremenő ellenőrzés sikeres volt, a H kapacitás a visszafelé számolásban sem sérül. ||
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
