/*
Feladat: Minden vendég egy [Ei, Ti] (zárt) időintervallumban fotózható, egy vendég legfeljebb egy képen szerepelhet, egy időpontban pedig legfeljebb egy K fős csoportképet lehet készíteni. A cél a képek számának maximalizálása.
Ötlet: Időben balról jobbra haladunk. Az éppen elérhető, még nem fotózott vendégeket lejárati idő (Ti) szerint minimum-kupacban tartjuk. Minden időpontban legfeljebb egy képet készíthetünk: ha legalább K aktív vendég van, akkor a K legkorábban lejárót fotózzuk le. Ez EDF-jellegű mohó döntés: a legszűkebb határidejűeket érdemes előre venni, különben könnyen elvesznek.
Hint 1: || Egy időponthoz csak egy kép tartozhat, tehát időnként „slotokért” versenyeznek a vendégek. ||
Hint 2: || Ha most tudsz fotózni, a legkorábban távozókat érdemes kiválasztani. ||
Hint 3: || Használj min-kupacot a Ti értékekre, és minden időpontban előbb dobd ki a már lejárt vendégeket. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<vector<pair<int,int>>> arrivals;
    int maxT = 0;
    {
        vector<pair<int,int>> people(N + 1);
        int maxE = 0;
        for (int i = 1; i <= N; ++i) {
            int e, t;
            cin >> e >> t;
            people[i] = {e, t};
            maxE = max(maxE, e);
            maxT = max(maxT, t);
        }
        arrivals.assign(max(maxE, maxT) + 2, {});
        for (int i = 1; i <= N; ++i) {
            arrivals[people[i].first].push_back({people[i].second, i});
        }
    }

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; // (Ti, id)
    vector<vector<int>> photos;

    for (int t = 1; t < (int)arrivals.size(); ++t) {
        for (auto [ti, id] : arrivals[t]) pq.push({ti, id});

        while (!pq.empty() && pq.top().first < t) pq.pop();

        if ((int)pq.size() >= K) {
            vector<int> shot;
            shot.reserve(K);
            for (int i = 0; i < K; ++i) {
                auto [ti, id] = pq.top();
                pq.pop();
                shot.push_back(id);
            }
            photos.push_back(move(shot));
        }
    }

    cout << photos.size() << '\n';
    for (const auto& g : photos) {
        for (int i = 0; i < (int)g.size(); ++i) {
            if (i) cout << ' ';
            cout << g[i];
        }
        cout << '\n';
    }

    return 0;
}
