#include <bits/stdc++.h>
using namespace std;

/*
    Az összes téglalap kezdő- és végpontja esemény. Balról jobbra végigmenve
    karbantartjuk az aktív magasságok halmazát, és minden esemény után
    megvizsgáljuk az adott tartományon érvényes maximális magasságot.
*/

struct Event {
    int x;
    int type; // 0 = end, 1 = start
    int h;
    bool operator<(const Event& other) const {
        if (x != other.x) return x < other.x;
        return type < other.type;
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

    vector<int> cnt(10001, 0);
    int curMax = 0;
    int ans = INT_MAX;

    for (size_t i = 0; i < ev.size();) {
        int x = ev[i].x;

        while (i < ev.size() && ev[i].x == x && ev[i].type == 1) {
            ++cnt[ev[i].h];
            curMax = max(curMax, ev[i].h);
            ++i;
        }
        if (1 <= x && x <= H) ans = min(ans, curMax);

        while (i < ev.size() && ev[i].x == x && ev[i].type == 0) {
            if (ev[i].h > 0) {
                --cnt[ev[i].h];
                if (ev[i].h == curMax && cnt[ev[i].h] == 0) {
                    while (curMax > 0 && cnt[curMax] == 0) --curMax;
                }
            }
            ++i;
        }
        if (1 <= x && x < H) ans = min(ans, curMax);
    }

    if (ans == INT_MAX) ans = 0;
    cout << ans << '\n';
    return 0;
}