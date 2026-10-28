/*
Hátizsák probléma – sok kicsi tárgy: N tárgy (súly S[i], haszon E[i]) közül kell kiválasztani
legfeljebb K összsúlyút úgy, hogy a haszon maximális legyen; ki kell írni a tárgyakat is.

Megoldási ötlet: 0/1 hátizsák egy dimenzióban. dp[w] = az eddigi tárgyakból legfeljebb w
összsúllyal elérhető legnagyobb haszon (ezért minden érték 0-ról indul). Az i-edik tárgynál
w-t K-tól LEFELÉ járjuk, így dp[w - S[i]] még az i-edik tárgy nélküli értéket tartalmazza,
vagyis minden tárgy legfeljebb egyszer kerül be.

Visszafejtés: egy bittáblában jegyezzük, hogy az i-edik tárgy javított-e dp[w]-n
(vesz[i][w]). Ezután w = K-ból indulva, i = N..1 sorrendben: ha vesz[i][w], akkor az i-edik
tárgy benne van, és w -= S[i]. Egy 1-D "utolsó javító tárgy" tömb nem elég, mert egy későbbi
tárgy felülírja, és ugyanaz a tárgy többször is kijöhetne. Itt K ≤ 1000, így a tábla
bitenként mindössze N·K ≈ 125 KB (a K ≤ 100 000-es változatnál 12,5 MB).

Idő: O(N·K), memória: O(K) + N·K bit.
*/
/*
Hint 1: || Minden tárgyról egyetlen döntés születik: bekerül vagy kimarad. Mi az a legkevesebb, amit az első i tárgyról tudnod kell, hogy a többiről dönthess? ||
Hint 2: || dp[w] = az eddigi tárgyakból legfeljebb w összsúllyal elérhető legnagyobb haszon. Egy dimenzió elég, ha az i-edik tárgynál w-t K-tól lefelé járod, így minden tárgy legfeljebb egyszer kerül be. ||
Hint 3: || Jegyezd fel egy bittáblában, hogy az i-edik tárgy javított-e dp[w]-n, és ebből fejtsd vissza a halmazt K-tól, az utolsó tárgytól visszafelé haladva. Egy 1-D szülőtömb nem elég, mert a későbbi tárgyak felülírják. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // beolvasás
    int N, K;
    cin >> N >> K;
    vector<int> S(N + 1), E(N + 1);
    for (int i = 1; i <= N; i++) cin >> S[i];
    for (int i = 1; i <= N; i++) cin >> E[i];

    // dp[w]: legfeljebb w súllyal elérhető legnagyobb haszon ("<= w", ezért minden 0-ról indul)
    vector<int> dp(K + 1, 0);
    // vesz[i][w] = 1, ha az i-edik tárgy javította dp[w]-t (bitenként tárolva)
    vector<vector<bool>> vesz(N + 1, vector<bool>(K + 1, false));

    for (int i = 1; i <= N; i++) {
        int s = S[i], e = E[i];  // helyi változóban gyorsabb a belső ciklus
        // visszafelé: így minden tárgyat legfeljebb egyszer használunk fel
        for (int w = K; w >= s; w--) {
            if (dp[w - s] + e > dp[w]) {
                dp[w] = dp[w - s] + e;
                vesz[i][w] = true;
            }
        }
    }

    // rekonstrukció: az utolsó tárgytól visszafelé, w = K-ból indulva
    vector<int> targyak;
    int w = K;
    for (int i = N; i >= 1; i--) {
        if (vesz[i][w]) {
            targyak.push_back(i);
            w -= S[i];
        }
    }
    reverse(targyak.begin(), targyak.end());

    // kiírás
    cout << dp[K] << '\n' << targyak.size() << '\n';
    for (int j = 0; j < (int)targyak.size(); j++) {
        if (j > 0) cout << ' ';
        cout << targyak[j];
    }
    cout << '\n';
    return 0;
}
