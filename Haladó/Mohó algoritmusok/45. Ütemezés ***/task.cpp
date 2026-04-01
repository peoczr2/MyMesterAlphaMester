/*
Feladat: A programok közül a lehető legtöbbet kell kiválasztani úgy, hogy a kiválasztottak mind határidőre befejezhetők legyenek.
Ötlet: Határidő szerint rendezve tartunk egy aktuális halmazt; ha túlcsordulunk, a leghosszabb futásidejűt eldobjuk.
Hint 1: || A határidők szerinti sorrendben mindig az eddigi legjobb részhalmazt érdemes fenntartani. ||
Hint 2: || Túlcsorduláskor a leghosszabb feladat eldobása csökkenti legjobban az összidőt. ||
Hint 3: || A végső halmazt határidő szerint kiírva az ütemezés érvényes lesz. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Job { int t, d, id; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Job> a(n), orig(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].t >> a[i].d;
        a[i].id = i + 1;
        orig[i + 1] = a[i];
    }
    sort(a.begin(), a.end(), [](const Job &x, const Job &y) {
        if (x.d != y.d) return x.d < y.d;
        if (x.t != y.t) return x.t < y.t;
        return x.id < y.id;
    });

    priority_queue<pair<int,int>> pq;
    long long sum = 0;
    vector<int> keep(n + 1, 0);
    for (auto &j : a) {
        pq.push({j.t, j.id});
        keep[j.id] = 1;
        sum += j.t;
        if (sum > j.d) {
            auto [t, id] = pq.top(); pq.pop();
            sum -= t;
            keep[id] = 0;
        }
    }

    vector<int> ans;
    for (auto &j : a) if (keep[j.id]) ans.push_back(j.id);
    sort(ans.begin(), ans.end(), [&](int x, int y) {
        if (orig[x].d != orig[y].d) return orig[x].d < orig[y].d;
        return x < y;
    });

    cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}