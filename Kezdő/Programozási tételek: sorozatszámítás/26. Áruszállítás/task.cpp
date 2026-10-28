/*
Megoldás lényege:
A bal kamion az 1..k-1, a jobb kamion a k+1..N raktárak áruit viszi a k. raktárba. Ha P_i jelöli az 1..i
raktárak áruösszegét, akkor a bal kamion terhelése P_(k-1), a jobbé az összes áru mínusz P_k. Ezt minden k-ra
előtag-összeggel O(1)-ben kiszámoljuk, és azt a k-t választjuk, ahol a két terhelés maximuma minimális.
Egyenlőség esetén a kisebb sorszám marad. Az időigény O(N).
*/
/*
Hint 1: || A két kamion terhelése csak attól függ, hova érkeznek: a bal kamion az 1..k-1, a jobb a k+1..N raktárak áruját viszi. ||
Hint 2: || Számold ki az előtag-összegeket, és az összes áru ismeretében minden k-ra a bal terhelés P_(k-1), a jobb terhelés az összes áru mínusz P_k. Ezek maximumát minimalizáld. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> p(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        long long s;
        cin >> s;
        p[i] = p[i - 1] + s;
    }
    long long osszes = p[n];

    long long legjobb = LLONG_MAX;
    int ans = 1;
    for (int k = 1; k <= n; k++) {
        long long bal = p[k - 1];
        long long jobb = osszes - p[k];
        long long mx = max(bal, jobb);
        if (mx < legjobb) {
            legjobb = mx;
            ans = k;
        }
    }

    cout << ans << "\n";
    return 0;
}
