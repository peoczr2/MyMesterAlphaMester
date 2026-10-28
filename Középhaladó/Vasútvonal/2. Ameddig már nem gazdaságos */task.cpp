/*
Megoldás lényege:
Legyen c_i a vonaton lévő utasok száma az i. és (i+1). állomás között, amit léptetéssel kapunk: c_i = c_{i-1} + fel_i − le_i. Az i. szakasz bevétele U·c_i, költsége V, így az eredménye U·c_i − V. A k. állomástól a végállomásig tartó út eredménye S_k = Σ (U·c_i − V) az i = k … N−1 tagokra, amelyet a végállomástól visszafelé összegezve kapunk. A válasz az első olyan k állomást követő állomás sorszáma, amelyre S_k < 0, vagyis az előző állomástól a végállomásig már nem gazdaságos az üzemeltetés; ha ilyen nincs, a válasz 0. Az időigény O(N), az összegekhez long long kell.
*/
/*
Hint 1: || Egy szakasz eredménye U-szor a rajta utazók száma mínusz V. Egy állomástól a végállomásig tartó út eredménye ezeknek az összege. ||
Hint 2: || Ezt az összeget a végállomástól visszafelé számold ki minden állomásra, majd keresd az első (Budapest felőli) állomást, ahonnan negatív. A válasz az erre következő állomás sorszáma, különben 0. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long U, V;
    cin >> n >> U >> V;
    vector<long long> le(n + 1), fel(n + 1);
    for (int i = 1; i <= n; i++) cin >> le[i] >> fel[i];

    // c[i]: utasok száma az i. állomás elhagyása után (az i. és (i+1). állomás közötti szakaszon)
    vector<long long> c(n + 1, 0);
    long long load = 0;
    for (int i = 1; i <= n; i++) {
        load += fel[i] - le[i];
        c[i] = load;
    }

    // S[k]: az k. állomástól a végállomásig tartó út eredménye, hátulról számolva
    vector<long long> S(n + 2, 0);
    for (int k = n - 1; k >= 1; k--) S[k] = S[k + 1] + U * c[k] - V;

    int ans = 0;
    for (int k = 1; k <= n - 1; k++) {
        if (S[k] < 0) {
            ans = k + 1;
            break;
        }
    }
    cout << ans << "\n";
    return 0;
}
