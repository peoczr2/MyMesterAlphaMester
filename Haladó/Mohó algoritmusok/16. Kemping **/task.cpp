/*
Feladat: K darab faház van, minden foglalás pontosan M napos. A lehető legtöbb igényt kell elfogadni.
Ötlet: Az igény egy [s, s+M) intervallum. Standard több-erőforrásos intervallum ütemezés: végidő szerint rendezünk, és mindig ahhoz a faházhoz tesszük az igényt, amelyik legkésőbb, de még időben felszabadult.
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
