/*
Megoldás lényege:
Mivel a sorozat szigorúan növekvő, minden előállítás egyértelműen megadható három különböző indexszel (i < l < r). Rögzítjük az i-edik elemet, és a tőle jobbra eső részen két mutatóval (l és r) keressük azt a párt, amelyre a[i] + a[l] + a[r] = X. Ha az összeg kisebb X-nél, az l mutatót, ha nagyobb, az r mutatót léptetjük; pontos találatkor mindkettőt, és eggyel növeljük a számlálót. Így minden i-re O(N) munka van, összesen O(N^2), ami N <= 1000 mellett bőven belefér az időkorlátba.
*/
/*
Hint 1: || Rögzíts egy elemet, és a tőle jobbra eső részen keress két másik elemet, amelyek összege a maradék érték. ||
Hint 2: || A sorozat rendezettsége miatt két mutatóval (az elejéről és a végéről) végigmehetsz a tartományon: kis összegnél a bal, nagy összegnél a jobb mutatót léptesd. ||
Hint 3: || Minden pontos találat egy új előállítást jelent; mivel a számok szigorúan nőnek, egy előállítást sem számolunk kétszer. ||
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
