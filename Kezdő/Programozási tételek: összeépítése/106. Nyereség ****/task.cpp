/*
Megoldás lényege: minden üdülőhöz tartozik egy d_i = K_i - B_i nyereség, egy szakasz haszna pedig a benne lévő d-értékek összege.
Ezt prefixösszegekkel számoljuk: P_j az első j üdülő összege, így az [l..r] szakasz haszna P_r - P_{l-1}.
Egyetlen balról jobbra haladó bejárás elég: minden r-hez a korábbi prefixösszegek közül a legkisebb adja a legjobb bal végpontot.
Döntetlennél a kisebb kezdő-, majd a kisebb záró sorszámú szakaszt írjuk ki.
Ha a legnagyobb haszon nem pozitív, csak -1 a válasz.
Időigény: O(N), memóriaigény: O(1).
*/
/*
Hint 1: || Egy szakasz haszna a benne lévő K_i - B_i értékek összege. Írd fel ezt két prefixösszeg különbségeként! ||
Hint 2: || Ha a jobb végpontot rögzíted, a legjobb bal végpont az a korábbi prefixösszeg, amelyik a legkisebb. Ezt a minimumot menet közben tartsd nyilván! ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    long long prefix = 0;     // P_j: az első j üdülő haszonösszege
    long long minPrefix = 0;  // a P_0 ... P_{j-1} közül a legkisebb
    int minIdx = 0;           // ennek a legkisebb indexe

    long long best = LLONG_MIN;
    int bestL = 0, bestR = 0;

    for (int j = 1; j <= n; j++) {
        long long b, k;
        cin >> b >> k;
        prefix += k - b;

        long long cand = prefix - minPrefix;
        int l = minIdx + 1, r = j;
        if (cand > best || (cand == best && make_pair(l, r) < make_pair(bestL, bestR))) {
            best = cand;
            bestL = l;
            bestR = r;
        }

        if (prefix < minPrefix) {
            minPrefix = prefix;
            minIdx = j;
        }
    }

    if (best <= 0) {
        cout << -1 << "\n";
    } else {
        cout << best << "\n" << bestL << " " << bestR << "\n";
    }
    return 0;
}
