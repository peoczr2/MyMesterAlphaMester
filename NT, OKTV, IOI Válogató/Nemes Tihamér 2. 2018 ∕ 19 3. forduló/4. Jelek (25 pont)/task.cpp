/*
Megoldás lényege:
Legyen dp[i][j] az i-edik és a j-edik kezdőpozícióról induló részsorozatok közös előtagjának hossza (i < j, az átfedés megengedett). Ha a[i] = a[j], akkor dp[i][j] = dp[i+1][j+1] + 1, különben 0. Mivel egy sor csak a következő sortól függ, elég két tömböt tárolni, és i-t fordított sorrendben bejárni. A legnagyobb hossz mellett a legkisebb kezdőindexet tartjuk meg, így a legkorábbi leghosszabb ismétlődő rész kerül kiírásra. Az időigény O(N^2), a memóriaigény O(N).
*/
/*
Hint 1: || Rögzíts két kezdőpozíciót (i < j), és nézd meg, hány egymást követő elem egyezik kezdettől. Ha a[i] és a[j] egyenlő, az egyezés hossza az (i+1, j+1) pár egyezési hosszánál eggyel nagyobb. ||
Hint 2: || Az i-t n-től 1-ig csökkenő sorrendben bejárva elég az előző sor értékeit tartani. Minden talált egyezésnél frissíts, ha a hossz nagyobb a legjobbnál, vagy azonos hosszú, de kisebb a kezdőindex. Ha egyáltalán nincs egyezés, a válasz -1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    vector<int> nxt(n + 2, 0), cur(n + 2, 0);
    int bestLen = 0, bestPos = n + 1;

    for (int i = n; i >= 1; --i) {
        fill(cur.begin(), cur.end(), 0);
        for (int j = n; j > i; --j) {
            if (a[i] == a[j]) {
                cur[j] = nxt[j + 1] + 1;
                if (cur[j] > bestLen || (cur[j] == bestLen && i < bestPos)) {
                    bestLen = cur[j];
                    bestPos = i;
                }
            }
        }
        swap(cur, nxt);
    }

    if (bestLen == 0) {
        cout << -1 << '\n';
        return 0;
    }

    for (int i = 0; i < bestLen; ++i) {
        if (i) cout << ' ';
        cout << a[bestPos + i];
    }
    cout << '\n';
    return 0;
}