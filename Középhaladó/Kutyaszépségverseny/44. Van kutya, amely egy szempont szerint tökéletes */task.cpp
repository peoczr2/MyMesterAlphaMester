/*
Megoldás lényege:
A kérdés az, hogy létezik-e olyan kutya, amely valamelyik szempontban eléri a szempont maximumát.
Ezt úgy döntjük el, hogy minden kutya minden szempontjánál megnézzük a pontszám és a maximum egyezését, és az első egyezésnél megállunk.
Ha találunk ilyen párt, a válasz VAN, egyébként NINCS; a kiesés ebben a kérdésben nem számít.
Az idő O(N · M), a memóriaigény O(N · M).
*/
/*
Hint 1: || Nem kell összegezni vagy rendezni: elég tudni, hogy van-e legalább egy olyan pont, amely eléri a saját szempontja maximumát. ||
Hint 2: || Járd be a kutyákat és a szempontokat is, és már az első egyezésnél állj meg. Ha végig nem találsz egyezést, a kimenet NINCS. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> maxPont(m), minPont(m);
    for (int &x : maxPont) cin >> x;
    for (int &x : minPont) cin >> x;

    vector<vector<int>> p(n, vector<int>(m));
    for (auto &sor : p)
        for (int &x : sor) cin >> x;

    bool van = false;
    for (int i = 0; i < n && !van; i++)
        for (int j = 0; j < m && !van; j++)
            if (p[i][j] == maxPont[j]) van = true;

    cout << (van ? "VAN" : "NINCS") << '\n';
    return 0;
}
