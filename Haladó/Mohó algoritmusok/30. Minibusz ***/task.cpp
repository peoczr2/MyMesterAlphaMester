/*
Megoldás lényege: Az utas az U-tól V-ig tartó szakaszokon ül a buszon. Az utasokat kezdő megálló (U) szerint rendezzük, és egy aktív halmazban tartjuk a még utazó utasok célállomásának (V) sorszámát. Ha az új utas felvétele után több mint K utas lenne egy szakaszon, a legkésőbb célba érő utast elengedjük, mert az foglalná le a legtöbb további szakaszt. Így minden szakaszon legfeljebb K utas utazik, és a felvett utasok száma maximális. Időigény: O(M log M).
*/
/*
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