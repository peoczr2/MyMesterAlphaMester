/*
 * Különböző hármasok számolása kétpontos módszerrel.
 
Hint 1: || Ugyanaz a minta, mint az előző feladatban, csak most nem egyetlen hármast, hanem az összes lehetségeset kell megszámolni. ||
Hint 2: || Rögzítsd az első elemet, és két mutatóval keresd a megfelelő másik kettőt; minden pontos találat egy új előállítás. ||
Hint 3: || A keresés itt is rendezett tömbön a leghatékonyabb, mert a két mutató mozgatása egyszerre kezeli a túl kicsi és a túl nagy összeget. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int x;
    cin >> n >> x;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        int l = i + 1, r = n - 1;
        while (l < r) {
            long long s = 1LL * a[i] + a[l] + a[r];
            if (s == x) {
                ++ans;
                ++l; --r;
            } else if (s < x) {
                ++l;
            } else {
                --r;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}
