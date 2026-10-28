/*
Megoldás lényege:
Két kiválasztott város nem lehet ős és leszármazottja, mert a fővárosba vezető út nem mehet át másik kiválasztott városon.
Fa-DP: best[u] = max(T_u, a gyerekek best értékeinek összege). Az első esetben u-t választjuk, és részfájának minden csúcsa tiltott; a másodikban a gyerek-részfákat függetlenül optimalizáljuk.
A DP-t úgy számoljuk, hogy a gyerekek mindig a szülő előtt legyenek feldolgozva, a megoldást felülről lefelé rekonstruáljuk.
Időigény: O(N).
*/
/*
Hint 1: || A tiltás pontosan az ős-leszármazott párokra vonatkozik. ||
Hint 2: || Egy csúcsnál két opció van: „csúcsot viszem” vagy „gyerek-részfákat optimalizálom”. ||
Hint 3: || Posztorderben számolj DP-t, majd top-down rekonstruálj. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<long long> w(N + 1);
    for (int i = 1; i <= N; ++i) cin >> w[i];

    vector<vector<int>> ch(N + 1);
    for (int i = 2; i <= N; ++i) {
        int p;
        cin >> p;
        ch[p].push_back(i);
    }

    vector<int> order;
    order.reserve(N);
    vector<int> st = {1};
    while (!st.empty()) {
        int u = st.back();
        st.pop_back();
        order.push_back(u);
        for (int v : ch[u]) st.push_back(v);
    }

    vector<long long> best(N + 1, 0), sumChild(N + 1, 0);
    vector<char> take(N + 1, 0);

    for (int i = N - 1; i >= 0; --i) {
        int u = order[i];
        long long s = 0;
        for (int v : ch[u]) s += best[v];
        sumChild[u] = s;
        if (w[u] >= s) {
            best[u] = w[u];
            take[u] = 1;
        } else {
            best[u] = s;
            take[u] = 0;
        }
    }

    vector<int> chosen;
    vector<pair<int,bool>> q;
    q.push_back({1, false});
    while (!q.empty()) {
        auto [u, blocked] = q.back();
        q.pop_back();
        if (blocked) {
            for (int v : ch[u]) q.push_back({v, true});
            continue;
        }
        if (take[u]) {
            chosen.push_back(u);
            for (int v : ch[u]) q.push_back({v, true});
        } else {
            for (int v : ch[u]) q.push_back({v, false});
        }
    }

    cout << best[1] << '\n';
    cout << chosen.size() << '\n';
    for (int i = 0; i < (int)chosen.size(); ++i) {
        if (i) cout << ' ';
        cout << chosen[i];
    }
    cout << '\n';
    return 0;
}
