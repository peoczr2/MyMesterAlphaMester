#include <bits/stdc++.h>
using namespace std;

/*
    A kérdéssor egy teljes bináris fa. DFS-sel bejárjuk, és minden levélhez
    kiszámoljuk, hogy a gyökértől odáig vezető úton mennyi IGEN és NEM válasz
    szerepelt. A címke ezek különbsége, a feladat pedig a leggyakoribb címkét
    kéri.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> yes(2 * n + 2), no(2 * n + 2);
    for (int i = 1; i <= n; ++i) cin >> yes[i] >> no[i];

    unordered_map<int, int> freq;
    vector<tuple<int, int, int>> st;
    st.push_back({1, 0, 0});
    while (!st.empty()) {
        auto [u, y, nn] = st.back();
        st.pop_back();
        if (u > n) {
            ++freq[y - nn];
            continue;
        }
        st.push_back({yes[u], y + 1, nn});
        st.push_back({no[u], y, nn + 1});
    }

    int bestLabel = 0, bestCnt = -1;
    for (auto [lab, cnt] : freq) {
        if (cnt > bestCnt || (cnt == bestCnt && lab < bestLabel)) {
            bestCnt = cnt;
            bestLabel = lab;
        }
    }

    cout << bestLabel << ' ' << bestCnt << '\n';
    return 0;
}