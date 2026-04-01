/*
Megoldási ötlet:
A cél az, hogy a K darab összefüggő szakasz közül a legkisebb szakaszösszeg a lehető legnagyobb legyen. Ha megadunk egy X értéket,
akkor a kérdés csak az, hogy ki tudunk-e alakítani legalább K olyan szakaszt, amelyek összege legalább X. Pozitív súlyok mellett ezt
greedyn a lehető legkorábbi vágásokkal lehet eldönteni.

Ezért binárisan kereshetjük az optimális X-et. Ha megvan, egy újabb balról jobbra menettel előállítunk pontosan K szakaszt: amikor az
aktuális részösszeg már eléri X-et, és marad elég elem a hátralévő kamionokra, ott vágunk.
*/
/*
Hint 1: || Gondold át először az eldöntési változatot: „lehet-e minden kamionra legalább X súlyt rakni?”. ||
Hint 2: || Pozitív számoknál az eldöntésnél az a legjobb, ha mindig a lehető legkorábban vágsz. ||
Hint 3: || A bináris keresés után még egy greedy kör elég a konkrét kezdőindexek visszaadásához. ||
*/

#include <bits/stdc++.h>
using namespace std;

static bool feasible(const vector<int>& a, int k, long long need) {
    long long sum = 0;
    int cnt = 0;
    for (int x : a) {
        sum += x;
        if (sum >= need) {
            ++cnt;
            sum = 0;
        }
    }
    return cnt >= k;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    long long total = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        total += a[i];
    }

    long long lo = 0, hi = total, ans = 0;
    while (lo <= hi) {
        long long mid = (lo + hi) / 2;
        vector<int> raw(a.begin() + 1, a.end());
        if (feasible(raw, k, mid)) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    vector<int> starts;
    starts.push_back(1);
    long long sum = 0;
    int made = 1;
    for (int i = 1; i <= n && made < k; ++i) {
        sum += a[i];
        int remainingItems = n - i;
        int remainingSegments = k - made;
        if (sum >= ans && remainingItems >= remainingSegments) {
            starts.push_back(i + 1);
            ++made;
            sum = 0;
        }
    }

    cout << ans << '\n';
    for (int i = 0; i < (int)starts.size(); ++i) {
        if (i) cout << ' ';
        cout << starts[i];
    }
    cout << '\n';
    return 0;
}