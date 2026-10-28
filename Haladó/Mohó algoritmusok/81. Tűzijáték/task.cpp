/*
Megoldás lényege:
A telephely mindenképpen benne van, így a többi tűzijáték a telephelytől balra és jobbra külön-külön választható ki. Mindkét irányban mohón haladunk: mindig a telephelyhez legközelebbi olyan települést vesszük, amely még legalább T távolságra van az utoljára kiválasztottól. A két oldal egymástól független, a határon lévő két választás távolsága a telephely miatt legalább 2T, így a T-korlát ott is teljesül. A legközelebbi lehetséges választás hagyja a legtöbb helyet a további települések számára, ezért a mohó megoldás optimális. Az időigény O(N).
*/
/*
Hint 1: || A bal oldali és a jobb oldali választás egymástól független. ||
Hint 2: || Balra a legközelebbi, még engedett települést, jobbra pedig ugyanígy a legközelebbit érdemes választani. ||
Hint 3: || A telephely sorszáma kötelező, ezért innen indulj mindkét irányban. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, s, t;
    cin >> n >> s >> t;
    vector<long long> dist(n + 1);
    for (int i = 1; i <= n; ++i) cin >> dist[i];

    vector<int> lefts, rights;
    long long last = dist[s];
    for (int i = s - 1; i >= 1; --i) {
        if (last - dist[i] >= t) {
            lefts.push_back(i);
            last = dist[i];
        }
    }
    reverse(lefts.begin(), lefts.end());

    last = dist[s];
    for (int i = s + 1; i <= n; ++i) {
        if (dist[i] - last >= t) {
            rights.push_back(i);
            last = dist[i];
        }
    }

    vector<int> ans = lefts;
    ans.push_back(s);
    ans.insert(ans.end(), rights.begin(), rights.end());

    cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}