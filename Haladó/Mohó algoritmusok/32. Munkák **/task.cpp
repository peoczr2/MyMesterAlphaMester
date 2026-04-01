/*
Feladat: Minden munkát el kell végezni, és a cél a legnagyobb késés minimalizálása.
Ötlet: A határidők szerint növekvő sorrendben végrehajtott ütemezés minimális maximum késést ad. Ez az EDD szabály.
Hint 1: || Ha egy munka késik, az csak a korábban elhelyezett munkák miatt történhet. ||
Hint 2: || A határidők szerinti sorrend a maximum lateness klasszikus optimális sorrendje. ||
Hint 3: || Elég a kumulált időt és az aktuális határidőt összevetni. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int,int>> jobs(n);
    for (int i = 0; i < n; ++i) cin >> jobs[i].first >> jobs[i].second;
    sort(jobs.begin(), jobs.end(), [](auto &a, auto &b) {
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    });

    long long time = 0, ans = 0;
    for (auto [t, d] : jobs) {
        time += t;
        ans = max(ans, time - d);
    }
    cout << ans << '\n';
    return 0;
}