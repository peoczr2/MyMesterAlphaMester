/*
Megoldás lényege:
Minden bolygó észlelési időpontjai rendezett sorozatot alkotnak. Olyan legszűkebb
zárt intervallumot keresünk, amely mindegyik sorozatból tartalmaz legalább egy időpontot.

Ez a klasszikus minimum-rés feladat: egy min-heapben mindig a jelenlegi legkisebb
elemet tartjuk, mellette pedig nyilván tartjuk a jelenlegi legnagyobb kiválasztott
időpontot. Minden lépésben a legkisebb elemet toljuk előre a saját sorozatában,
és frissítjük a legjobb [A,B] intervallumot. Amint valamelyik sorozat elfogy,
nem tudunk több teljes fedést alkotni.
*/

#include <bits/stdc++.h>
using namespace std;

struct Item {
    long long value;
    int listId;
    int index;
    bool operator>(const Item& other) const {
        if (value != other.value) return value > other.value;
        return listId > other.listId;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<vector<long long>> a(n);
    for (int i = 0; i < n; ++i) {
        int m;
        cin >> m;
        a[i].resize(m);
        for (int j = 0; j < m; ++j) cin >> a[i][j];
    }

    priority_queue<Item, vector<Item>, greater<Item>> pq;
    long long currentMax = LLONG_MIN;
    for (int i = 0; i < n; ++i) {
        pq.push({a[i][0], i, 0});
        currentMax = max(currentMax, a[i][0]);
    }

    long long bestA = 0, bestB = LLONG_MAX;
    bool hasAnswer = false;

    while ((int)pq.size() == n) {
        Item cur = pq.top();
        pq.pop();

        long long candA = cur.value;
        long long candB = currentMax;
        if (!hasAnswer || candB - candA < bestB - bestA ||
            (candB - candA == bestB - bestA && candA < bestA)) {
            hasAnswer = true;
            bestA = candA;
            bestB = candB;
        }

        int nextIndex = cur.index + 1;
        if (nextIndex >= (int)a[cur.listId].size()) break;
        long long nextValue = a[cur.listId][nextIndex];
        pq.push({nextValue, cur.listId, nextIndex});
        currentMax = max(currentMax, nextValue);
    }

    cout << bestA << ' ' << bestB << '\n';
    return 0;
}