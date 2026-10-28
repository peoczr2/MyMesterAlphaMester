/*
Megoldás lényege:
Egy négyzet alakú járólap pontosan akkor jó minden teremhez, ha mérete osztója a terem minden szélességének és hosszúságának.
Ezért a keresett méret a kastély összes oldalának legnagyobb közös osztója, amit egy nullától induló akkumulátorral számolunk: minden beolvasott számra g = gcd(g, szám).
Minden kastélynál a g értéket újra nullázzuk, így a kastélyok egymástól függetlenül kapják meg az eredményüket.
Az időigény kastélyonként O(T · log C), ahol T ≤ 10 a termek száma és C ≤ 10^9 az oldalhossz.
*/
/*
Hint 1: || Egy szám akkor osztja a járólap méretét, ha osztja a terem összes oldalát. Mi a legnagyobb olyan szám, amely egyszerre osztja az összes beolvasott számot? ||
Hint 2: || Egy 0-val induló változóban halmozd a gcd-t: a beolvasott összes számra hívd meg a std::gcd függvényt. Minden kastélynál ezt a változót nullázd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;
    while (k--) {
        int t;
        cin >> t;
        long long g = 0;
        for (int i = 0; i < t; ++i) {
            long long a, b;
            cin >> a >> b;
            g = std::gcd(g, a);
            g = std::gcd(g, b);
        }
        cout << g << '\n';
    }
    return 0;
}