/*
Megoldás lényege:
Minden téglalap a [P, P+K] szakaszt fedi, ezért a kezdő- és végpontok eseményekké alakíthatók, és M(P) csak ezekben a pontokban változik.
Balról jobbra haladva az események x-koordinátáján először a kezdéseket, utána a végpontokat dolgozzuk fel, és az események utáni szakasz értéke az aktív magasságok maximuma.
Az aktív magasságokat rendezett multihalmazban tartjuk, így a maximum lekérdezése és a törlés O(log N) idő alatt végezhető el.
A válasz a vizsgált szakaszok értékeinek minimuma; egész pozícióban a fedettség nem kisebb a szomszédos szakaszok fedettségénél, ezért ezek nem befolyásolják a minimumot.
Az időigény O(N log N).
*/
/*
Hint 1: || Nem kell minden P pozícióra külön számolni: M(P) csak akkor változik, amikor egy téglalap kezdő- vagy végpontját átlépjük, ezért elég ezeket az eseményeket sorba rendezni. ||
Hint 2: || Azonos x-koordinátánál a kezdéseket dolgozd fel a végpontok előtt: így a zárt fedettség és a jobbra eső szakasz fedettsége is helyesen adódik. ||
Hint 3: || Az aktív magasságokat tárold multihalmazban (multiset): a maximum a legnagyobb elem, a törlés pedig egy előfordulást vesz el. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Event {
    int x;
    int type; // 0 = end, 1 = start; azonos x-nél a kezdés előbb jön
    int h;
    bool operator<(const Event& other) const {
        if (x != other.x) return x < other.x;
        return type > other.type;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, N, K;
    cin >> H >> N >> K;
    vector<Event> ev;
    ev.reserve(2 * N + 2);
    for (int i = 0; i < N; ++i) {
        int p, d;
        cin >> p >> d;
        ev.push_back({p, 1, d});
        ev.push_back({p + K, 0, d});
    }
    ev.push_back({1, 0, 0});
    ev.push_back({H + 1, 0, 0});
    sort(ev.begin(), ev.end());

    multiset<int> active;
    int ans = INT_MAX;

    for (size_t i = 0; i < ev.size();) {
        int x = ev[i].x;

        while (i < ev.size() && ev[i].x == x && ev[i].type == 1) {
            active.insert(ev[i].h);
            ++i;
        }
        if (1 <= x && x <= H) ans = min(ans, active.empty() ? 0 : *active.rbegin());

        while (i < ev.size() && ev[i].x == x && ev[i].type == 0) {
            if (ev[i].h > 0) active.erase(active.find(ev[i].h));
            ++i;
        }
        if (1 <= x && x < H) ans = min(ans, active.empty() ? 0 : *active.rbegin());
    }

    if (ans == INT_MAX) ans = 0;
    cout << ans << '\n';
    return 0;
}
