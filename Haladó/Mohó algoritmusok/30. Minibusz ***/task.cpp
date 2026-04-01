/*
Feladat: Egy meneten belül legfeljebb K utast szállíthatunk, és a megállók között csak előre haladhatunk.
Ötlet: Az intervallumokat a kezdő megálló szerint rendezzük, és amikor a jelenlegi megállónál a fedettség meghaladná K-t, a legtovább tartó utast el kell engedni. Ez a kapacitásos intervallum kiválasztás klasszikus mohója.
Hint 1: || A busz egy adott szakaszon akkor túlterhelt, ha azon több mint K kiválasztott utas halad. ||
Hint 2: || A legjobban a legkésőbb végző utast érdemes kihagyni, ha muszáj csökkenteni a fedést. ||
Hint 3: || Előrehaladva egy aktív halmazt kell nyomon követni a kiválasztott utasok végpontjaival. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Ride { int u, v; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K, N, M;
    cin >> K >> N >> M;
    vector<Ride> rides(M);
    for (int i = 0; i < M; ++i) cin >> rides[i].u >> rides[i].v;

    sort(rides.begin(), rides.end(), [](const Ride &a, const Ride &b) {
        if (a.u != b.u) return a.u < b.u;
        return a.v < b.v;
    });

    multiset<pair<int,int>> active;
    int ans = 0;
    for (auto [u, v] : rides) {
        while (!active.empty() && active.begin()->first <= u) active.erase(active.begin());
        active.insert({v, ans++});
        if ((int)active.size() > K) {
            auto it = prev(active.end());
            active.erase(it);
            --ans;
        }
    }

    cout << ans << '\n';
    return 0;
}