/*
Megoldás lényege:
Minden x <= N számra kiszámoljuk az osztók számát egy szitával: minden d-re a d
többszöröseinek (d, 2d, 3d, ...) osztószámát eggyel növeljük. Ezután x-et 1-től N-ig
sorban nézzük, és kiírjuk azokat, amelyek osztószáma nagyobb az addig látott
összes szám osztószámánál (a futó maximumnál). A szita O(N log N) időben fut,
ami N <= 1 200 000 esetén bőven belefér az időkorlátba.
*/
/*
Hint 1: || Az osztók számát ne egyenként számold: minden d-re végigmész a d többszörösein, és mindegyiknek eggyel növeled az osztószámát. ||
Hint 2: || A kiírandó számok azok, amelyek osztószáma szigorúan nagyobb az eddig látott minden számnál; ezt egy futó maximummal követheted. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> divs(n + 1, 0);
    for (int d = 1; d <= n; ++d) {
        for (int m = d; m <= n; m += d) ++divs[m];
    }
    int best = 0;
    bool first = true;
    for (int x = 1; x <= n; ++x) {
        if (divs[x] > best) {
            best = divs[x];
            if (!first) cout << ' ';
            first = false;
            cout << x;
        }
    }
    cout << '\n';
    return 0;
}
