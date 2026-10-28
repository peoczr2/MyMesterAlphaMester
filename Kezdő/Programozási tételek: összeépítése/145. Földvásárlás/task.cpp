/*
Megoldás lényege:
K egymás utáni telket kell megvenni, így N-K+1 csoport van. Egy csoport összegét csúszóablakkal számoljuk: a következő csoport összege az előző összegből a kilépő telek árának levonásával és a belépő telek árának hozzáadásával adódik. Közben nyilvántartjuk a legkisebb összeget és azt, hogy hány csoport adja ugyanezt az összeget. Az időigény O(N).
*/
/*
Hint 1: || Pontosan K egymást követő telket kell megvenned, így a lehetséges csoportok száma N-K+1. Ezek összegét mind ki lehet számolni. ||
Hint 2: || Két szomszédos csoport összege csak egy-egy telekben különbözik: az új csoportba belép az új telek, a régiből kilép a legelső. Ezzel az összes csoport összegét egy menetben végigvihetsz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<long long> s(n);
    for (auto &x : s) cin >> x;

    long long window = 0;
    for (int i = 0; i < k; i++) window += s[i];
    long long best = window;
    long long cnt = 1;
    for (int i = k; i < n; i++) {
        window += s[i] - s[i - k];
        if (window < best) {
            best = window;
            cnt = 1;
        } else if (window == best) {
            cnt++;
        }
    }

    cout << best << "\n" << cnt << "\n";
    return 0;
}
