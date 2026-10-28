/*
Megoldás lényege: Az első és az utolsó állomás kötelező, ezért a köztes megállókat a kiindulótól kezdve, sorban választjuk: mindig a legkorábbi olyan állomást vesszük fel, amely legalább K kilométerre van az előző megállótól.
Az utolsó állomás előtti megálló csak olyan lehet, amely legalább K kilométerre van a végállomástól, ezért a köztes állomásokat csak a T(N)-K határig keressük; így a végállomás is teljesíti a K-s feltételt.
A korai megálló a legtöbb helyet hagyja a további megállóknak, ezért a mohó választás optimális, és a megoldás O(N) időben fut.
*/
/*
Hint 1: || Az első és az utolsó állomás kötelező, a köztes megállókat ezek között érdemes sorban, a kiindulótól haladva kiválasztani. ||
Hint 2: || Az utolsó állomás előtti megálló csak olyan lehet, amely legalább K-ra van a végállomástól: a mohó bejárást erre a részre szűkítsd, és a végén mindenképpen írd ki az utolsó állomást. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> t(n + 1);
    for (int i = 1; i <= n; ++i) cin >> t[i];

    vector<int> ans{1};
    int last = 1;
    for (int i = 2; i < n; ++i) {
        if (t[i] - t[last] >= k && t[n] - t[i] >= k) {
            ans.push_back(i);
            last = i;
        }
    }
    ans.push_back(n);

    cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}