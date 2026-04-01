/*
Feladat: 1 napos munkákból kell olyan részhalmazt és sorrendet választani, hogy minden munka a határidőig elkészüljön, az összhaszon pedig maximális legyen.
Ötlet: Határidő szerint haladva minimum-kupacban tartjuk a beválasztott munkákat (profit, id, deadline). Ha túl sok munka lenne az adott határidőig, a legkisebb profitút eldobjuk. A kiválasztott halmazból DSU-val napokra ültetünk: minden munkát a lehető legkésőbbi szabad napra teszünk.
Hint 1: || A „deadline-ig max ennyi munka fér be” feltétel miatt deadline szerinti sorrend természetes. ||
Hint 2: || Ha telítettél egy prefixet, mindig a legkisebb hasznú munkát érdemes kivenni. ||
Hint 3: || Kimeneti sorrendhez készíts konkrét nap-beosztást: legkésőbbi szabad nap <= határidő. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Job {
    int d, p, id;
};

struct DSU {
    vector<int> p;
    explicit DSU(int n = 0) { init(n); }
    void init(int n) {
        p.resize(n + 1);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        if (x <= 0) return 0;
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    void occupy(int x) { p[find(x)] = find(x - 1); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<Job> jobs(N);
    int maxD = 0;
    for (int i = 0; i < N; ++i) {
        cin >> jobs[i].d >> jobs[i].p;
        jobs[i].id = i + 1;
        maxD = max(maxD, jobs[i].d);
    }

    sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
        if (a.d != b.d) return a.d < b.d;
        return a.p > b.p;
    });

    using T = tuple<int,int,int>; // profit, id, deadline
    priority_queue<T, vector<T>, greater<T>> pq;

    for (const auto& j : jobs) {
        pq.push({j.p, j.id, j.d});
        if ((int)pq.size() > j.d) pq.pop();
    }

    vector<Job> picked;
    long long total = 0;
    while (!pq.empty()) {
        auto [p, id, d] = pq.top();
        pq.pop();
        picked.push_back({d, p, id});
        total += p;
    }

    sort(picked.begin(), picked.end(), [](const Job& a, const Job& b) {
        if (a.p != b.p) return a.p > b.p;
        return a.id < b.id;
    });

    DSU dsu(maxD);
    vector<int> dayToId(maxD + 1, 0);
    for (const auto& j : picked) {
        int day = dsu.find(j.d);
        if (day > 0) {
            dayToId[day] = j.id;
            dsu.occupy(day);
        }
    }

    vector<int> order;
    for (int day = 1; day <= maxD; ++day) {
        if (dayToId[day]) order.push_back(dayToId[day]);
    }

    cout << total << '\n';
    for (int i = 0; i < (int)order.size(); ++i) {
        if (i) cout << ' ';
        cout << order[i];
    }
    cout << '\n';
    return 0;
}
