/*
Megoldas lenyege:
Egy részsorozat t-toleráns pontosan akkor, ha a benne lévő legnagyobb és
legkisebb érték különbsége legfeljebb t. Ezt csúszóablakkal és két monoton
veremként működő deque-vel lehet követni: az egyik a minimumot, a másik a
maximumot tartja karban.
*/
/*
Hint 1: || Az ablak jó akkor és csak akkor, ha max - min <= t. ||
Hint 2: || A minimumot és maximumot fenntartó deques-zel gyorsan lehet bővíteni és szűkíteni az ablakot. ||
Hint 3: || Minden lépésben a bal szélt addig kell tolni, amíg újra teljesül a feltétel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, n;
    cin >> t >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    deque<int> mn, mx;
    int l = 0;
    int best = 0;
    for (int r = 0; r < n; ++r) {
        while (!mn.empty() && a[mn.back()] >= a[r]) mn.pop_back();
        mn.push_back(r);
        while (!mx.empty() && a[mx.back()] <= a[r]) mx.pop_back();
        mx.push_back(r);

        while (!mn.empty() && !mx.empty() && a[mx.front()] - a[mn.front()] > t) {
            ++l;
            while (!mn.empty() && mn.front() < l) mn.pop_front();
            while (!mx.empty() && mx.front() < l) mx.pop_front();
        }
        best = max(best, r - l + 1);
    }

    cout << best << '\n';
    return 0;
}
