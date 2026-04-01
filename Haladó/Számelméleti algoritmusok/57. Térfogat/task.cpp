/*
 * A térfogatot három tényezőre bontjuk, és a legkiegyensúlyozottabb hármast
 * választjuk.
 
Hint 1: || A három él szorzata adott, tehát valójában a számot kell három tényezőre bontanod. ||
Hint 2: || Csak az osztóhármasokat érdemes vizsgálni, és azok közül azt választani, ahol a legnagyobb és a legkisebb él különbsége minimális. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int best_a = n, best_b = 1, best_c = 1;
    int best_diff = n;
    for (int a = 1; 1LL * a * a * a <= n; ++a) {
        if (n % a) continue;
        int rem = n / a;
        for (int b = a; 1LL * b * b <= rem; ++b) {
            if (rem % b) continue;
            int c = rem / b;
            int mx = max({a, b, c});
            int mn = min({a, b, c});
            int diff = mx - mn;
            if (diff < best_diff) {
                best_diff = diff;
                best_a = mx; best_b = b; best_c = mn;
            }
        }
    }
    vector<int> v = {best_a, best_b, best_c};
    sort(v.begin(), v.end(), greater<int>());
    cout << v[0] << ' ' << v[1] << ' ' << v[2] << '\n';
    return 0;
}
