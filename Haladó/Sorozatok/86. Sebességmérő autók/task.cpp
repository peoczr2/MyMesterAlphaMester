/*
Megoldás lényege:
A keresett időszakok pontosan a két autó szolgálati intervallumainak unióját adják. Mindkét lista
rendezett és saját magán belül diszjunkt, ezért elég az összes intervallumot kezdőpont szerint
összefésülni, és közben egyesíteni az összeérő vagy átfedő szakaszokat.
*/
/*
Hint 1: || Itt nem metszet kell, hanem unió. ||
Hint 2: || Két rendezett, diszjunkt intervallumlistát könnyű összefésülni. ||
Hint 3: || Ha az új szakasz legfeljebb 1 nappal a mostani után kezdődik, akkor össze kell őket vonni. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int,int>> all;
    all.reserve(200000);
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        all.push_back({l, r});
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        all.push_back({l, r});
    }

    sort(all.begin(), all.end());
    vector<pair<int,int>> answer;
    for (const auto &interval : all) {
        if (answer.empty() || interval.first > answer.back().second + 1) {
            answer.push_back(interval);
        } else {
            answer.back().second = max(answer.back().second, interval.second);
        }
    }

    cout << answer.size() << '\n';
    for (const auto &interval : answer) {
        cout << interval.first << ' ' << interval.second << '\n';
    }
    return 0;
}