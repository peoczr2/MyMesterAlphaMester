/*
Megoldás lényege:
Megkeressük a szigeteket: a 0-ás mérésekkel elválasztott pozitív szakaszokat, amelyeknek mindkét partja
mért. Minden szigetről a legmagasabb pontját, vagyis a szakasz legnagyobb mérését jegyezzük fel.
Az út akkor lesz egyre magasabb, ha minden sziget csúcsa szigorúan nagyobb az előzőénél, ezt a
szomszédos szigetpárokra ellenőrizzük egyszer végigmenve. Ha nincs sziget, a válasz 0, egyetlen
sziget esetén nincs összehasonlítás, így a válasz 1. Az időigény O(N).
*/
/*
Hint 1: || Egy sziget legmagasabb pontja a szakasz legnagyobb mérése. A szakasz bejárása közben tartsd nyilván az eddigi maximumot. ||
Hint 2: || Az eredmény 1, ha a szigetek csúcsai sorban szigorúan nőnek; már egyetlen szomszédos pár is elég a 0-hoz. Ha nincs sziget, a válasz 0. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> h(n + 2, 0);  // h[1..n] a mérések, h[0] és h[n+1] nulla
    for (int i = 1; i <= n; i++) cin >> h[i];

    // minden sziget legmagasabb pontja, balról jobbra
    vector<int> csucsok;
    int i = 1;
    while (i <= n) {
        if (h[i] == 0) {
            i++;
            continue;
        }
        int l = i, mx = 0;
        while (i <= n && h[i] > 0) {
            mx = max(mx, h[i]);
            i++;
        }
        int r = i - 1;
        if (l > 1 && r < n) csucsok.push_back(mx);
    }

    if (csucsok.empty()) {
        cout << 0 << '\n';
        return 0;
    }

    bool egyre_magasabb = true;
    for (size_t k = 1; k < csucsok.size(); k++) {
        if (csucsok[k] <= csucsok[k - 1]) {
            egyre_magasabb = false;
            break;
        }
    }

    cout << (egyre_magasabb ? 1 : 0) << '\n';
    return 0;
}
