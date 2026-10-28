/*
Megoldás lényege:
A vágás után a gyöngyök egy egyenes sort alkotnak, a vágástól mért távolság a két irány közül a kisebb. Így a k-adik gyöngy (k = 1..N a vágás utáni sorrendben) szorzója min(k, N+1-k), vagyis a súlyok 1, 2, ..., N/2, N/2, ..., 2, 1. Ha a vágást eggyel tovább léptetjük, a vágás előtti k = 2..N/2 gyöngyök súlya 1-gyel csökken, a k = N/2+2..N gyöngyöké 1-gyel nő, a többi nem változik. Ezért az összérték egy lépésben két, egyenlő hosszú ciklikus szakasz összegével frissíthető. Az első vágás értékét közvetlenül kiszámoljuk, és a prefixösszegekkel minden vágási helyre O(1) lépésben lépünk tovább. A teljes futás O(N), a legnagyobb értékhez tartozó vágási hely sorszámát adjuk.
*/
/*
Hint 1: || Vágás után a gyöngyök egy sort alkotnak, és a vágástól mért távolság a két irány közül a kisebb. Így a k-edik gyöngy szorzója min(k, N+1-k), ahol k a vágás utáni sorszám. ||
Hint 2: || Ha a vágást eggyel tovább tolod, a k = 2..N/2 sorszámú gyöngyök szorzója 1-gyel csökken, a k = N/2+2..N sorszámúaké 1-gyel nő, a többié nem változik. Ezt a két összeget prefixösszegekkel add össze. ||
Hint 3: || Az első vágás összegét O(N) időben számold ki közvetlenül, utána minden lépésnél csak a két szakasz összegét vond ki, illetve add hozzá az előző értékhez. Közben jegyezd meg a legnagyobb értéket és a hozzá tartozó vágási helyet. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    // P[i] az első i gyöngy összege
    vector<long long> P(n + 1, 0);
    for (int i = 0; i < n; ++i) P[i + 1] = P[i] + a[i];

    // Ciklikus összeg: l-től (0-indexelt, mod n) kezdve len darab gyöngy összege.
    auto sumCyc = [&](long long l, long long len) -> long long {
        if (len <= 0) return 0;
        l %= n;
        if (l + len <= n) return P[l + len] - P[l];
        return (P[n] - P[l]) + P[l + len - n];
    };

    const int h = n / 2;

    // A vágás az i-edik (0-indexelt) gyöngy után van: a sorozat az i+1, ..., i+N gyöngyökből áll,
    // a k-adik gyöngy szorzója min(k, N+1-k). Kezdetben i = N-1.
    long long cur = 0;
    for (int k = 1; k <= n; ++k) {
        long long w = min<long long>(k, n + 1 - k);
        cur += w * a[k - 1];
    }

    long long best = cur;
    int bestI = n - 1;
    int i = n - 1;
    for (int step = 0; step < n - 1; ++step) {
        // Egy lépés: f(i+1) = f(i) - (i+2 .. i+h összege) + (i+h+2 .. i+N összege); mindkét szakasz h-1 hosszú.
        long long delta = -sumCyc(i + 2, h - 1) + sumCyc(i + h + 2, h - 1);
        cur += delta;
        i = (i + 1) % n;
        if (cur > best) {
            best = cur;
            bestI = i;
        }
    }

    cout << bestI + 1 << '\n';
    return 0;
}
