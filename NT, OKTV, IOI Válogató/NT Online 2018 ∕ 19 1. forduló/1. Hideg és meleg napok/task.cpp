/*
    Az első és az utolsó nap kivételével minden napot megjelölünk: hideg (+1), ha mindkét
    szomszédjánál hidegebb, meleg (-1), ha mindkettőnél melegebb, egyébként 0. Egy [l, r]
    intervallum pontosan akkor jó, ha l és r is hideg vagy meleg nap (jelük nem 0), és a jelek
    összege az intervallumon 0, vagyis a végpontokat is beleszámolva ugyanannyi hideg és meleg
    nap van benne. Az összeg prefixösszeggel O(1)-ben kiszámítható: pref[r] − pref[l−1].
    Mivel N ≤ 5000, minden (l, r) párt végigpróbálunk; ez O(N²) ≈ 12,5 millió lépés, ami az
    időlimiten belül van.
*/
/*
Hint 1: || Az első és az utolsó nap kivételével minden napról külön eldöntheted, hogy hideg, meleg vagy egyik sem, és ez csak a két szomszédjától függ. Ezeket a jeleket egyszer, előre kiszámíthatod. ||
Hint 2: || Egy [l, r] intervallum akkor jó, ha l és r jele nem 0, és a jelek összege az l-től r-ig tartó szakaszon 0, így a végpontok is számítanak. Ez azt jelenti, hogy ugyanannyi hideg és meleg nap van benne. ||
Hint 3: || Az összegeket prefixösszeggel gyorsan megkaphatod: az [l, r] összege pref[r] − pref[l−1]. Mivel N legfeljebb 5000, két egymásba ágyazott ciklussal az összes (l, r) párt ellenőrizheted. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> t(n + 1);
    for (int i = 1; i <= n; ++i) cin >> t[i];

    vector<int> jel(n + 1);
    for (int i = 2; i <= n - 1; ++i) {
        if (t[i] < t[i - 1] && t[i] < t[i + 1]) jel[i] = 1;
        else if (t[i] > t[i - 1] && t[i] > t[i + 1]) jel[i] = -1;
    }

    vector<int> pref(n + 1);
    for (int i = 1; i <= n; ++i) pref[i] = pref[i - 1] + jel[i];

    long long db = 0;
    for (int l = 1; l <= n; ++l) {
        if (jel[l] == 0) continue;
        for (int r = l; r <= n; ++r) {
            if (jel[r] == 0) continue;
            if (pref[r] - pref[l - 1] == 0) ++db;
        }
    }

    cout << db << '\n';
    return 0;
}
