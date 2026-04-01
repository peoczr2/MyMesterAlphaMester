/*
Feladat: A rendezvény teljes időtartamát a lehető legkevesebb tanulóval kell lefedni úgy, hogy a szolgálat átadható legyen.
Ötlet: Mindig az aktuálisan lefedett pontig elérő jelentkezők közül azt választjuk, aki a legtovább képes tovább tartani a szolgálatot.
Hint 1: || Az aktuális időpontig minden olyan intervallum használható, amely már elkezdődött. ||
Hint 2: || Ezek közül mindig a legnagyobb jobb végpontú intervallum a legjobb. ||
Hint 3: || Ha a következő lépésben semmilyen új tanuló nem érhető el, akkor nincs megoldás. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Seg { int a, b; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Seg> a;
    while (true) {
        int x, y;
        cin >> x >> y;
        if (x == 0 && y == 0) break;
        a.push_back({x, y});
    }
    sort(a.begin(), a.end(), [](const Seg &x, const Seg &y) {
        if (x.a != y.a) return x.a < y.a;
        return x.b > y.b;
    });

    priority_queue<int> pq;
    int ptr = 0, cur = 1, cnt = 0;
    while (cur < n) {
        while (ptr < (int)a.size() && a[ptr].a <= cur) {
            pq.push(a[ptr].b);
            ++ptr;
        }
        while (!pq.empty() && pq.top() < cur) pq.pop();
        if (pq.empty()) {
            cout << 0 << '\n';
            return 0;
        }
        cur = pq.top();
        pq.pop();
        ++cnt;
    }

    cout << cnt << '\n';
    return 0;
}