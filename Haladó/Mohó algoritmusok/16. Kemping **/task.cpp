/*
Megoldás lényege:
Minden foglalás azonos, M napos, ezért egy igény az [s, s+M) intervallum, a faházak állapota pedig elég a következő szabad napjukkal leírni. Az igényeket a befejezési idejük (s+M) szerint növekvő sorrendben dolgozzuk fel, így nem zárunk ki korábban befejeződő lehetőségeket. Minden igényt ahhoz a faházhoz rendelünk, amelyik a legkésőbb, de még s előtt szabadult fel: a szabad napokat multihalmazban tartjuk, és az utolsó, s-nél nem nagyobb elemet keressük. Ha nincs ilyen faház, az igény nem fogadható el. Az időigény O(N log N), a multihalmaz-műveletek miatt.
*/
/*
Hint 1: || Mivel minden foglalás azonos hosszú, az intervallum ütközések kezelésére elég a kezdőnap és a felszabadulás ideje. ||
Hint 2: || Végidő szerint választva nem zársz ki korán befejező lehetőségeket. ||
Hint 3: || Multihalmazban tartsd a faházak „következő szabad napját”, és keresd az utolsó <= start elemet. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K, M, N;
    cin >> K >> M >> N;

    vector<int> starts(N);
    for (int i = 0; i < N; ++i) cin >> starts[i];

    vector<pair<int,int>> jobs;
    jobs.reserve(N);
    for (int s : starts) jobs.push_back({s + M, s});
    sort(jobs.begin(), jobs.end());

    multiset<int> freeAt;
    for (int i = 0; i < K; ++i) freeAt.insert(1);

    int ans = 0;
    for (auto [endT, startT] : jobs) {
        auto it = freeAt.upper_bound(startT);
        if (it == freeAt.begin()) continue;
        --it;
        freeAt.erase(it);
        freeAt.insert(endT);
        ++ans;
    }

    cout << ans << '\n';
    return 0;
}
