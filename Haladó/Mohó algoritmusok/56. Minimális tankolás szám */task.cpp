/*
Feladat: A meglévő tankolások közül a lehető legkevesebbet kell felhasználni, hogy eljussunk a célba.
Ötlet: Amíg még tovább tudunk menni, gyűjtjük az elérhető tankolásokat; ha nem elég az üzemanyag, akkor a legnagyobb korábban látott tankolást választjuk. Ez a max-heapes mohó.
Hint 1: || Az elérhető kutak tankolásait egy prioritási sorban tárold. ||
Hint 2: || Amikor kevés a benzin, mindig a legnagyobb eddig látott tankolást használd fel. ||
Hint 3: || A válasz csak a tankolások száma. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long K, N, B, L;
    cin >> K >> N >> B >> L;
    vector<pair<long long, long long>> st(N);
    for (int i = 0; i < N; ++i) cin >> st[i].first >> st[i].second;
    sort(st.begin(), st.end());

    priority_queue<long long> pq;
    long long fuel = B * 100;
    long long used = 0;
    long long pos = 0;
    int ptr = 0;

    auto need = [&](long long d) { return d * L; };

    while (pos < K) {
        long long reach = pos + fuel / L;
        while (ptr < N && st[ptr].first <= reach) {
            pq.push(st[ptr].second * 100);
            ++ptr;
        }
        long long nextPos = K;
        if (ptr < N) nextPos = min(nextPos, st[ptr].first);
        if (fuel >= need(nextPos - pos)) {
            fuel -= need(nextPos - pos);
            pos = nextPos;
            continue;
        }
        if (pq.empty()) break;
        fuel += pq.top();
        pq.pop();
        ++used;
    }

    cout << used << '\n';
    return 0;
}