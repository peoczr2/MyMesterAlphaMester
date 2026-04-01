/*
Feladat: A megadott benzinkutak közül a lehető legkevesebbet kell tankolásra használni, hogy az autó eljusson a célig.
Ötlet: Sorban haladva mindig gyűjtjük a már elérhető kutak tankolásait, és amikor már nem érnénk el a következő pontot, a legnagyobb eddig látott tankolást vesszük fel. Ez a klasszikus "max heap" mohó.
Hint 1: || Amíg elérsz a következő állomásig, addig gyűjtsd a közben látott kutak tankolásait. ||
Hint 2: || Ha kevés a benzin, mindig a legnagyobb korábban látott tankolást használd fel. ||
Hint 3: || A cél az, hogy ugyanannyi megtett út mellett a lehető legkevesebbszer állj meg. ||
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
    long long prev = 0;
    int ptr = 0;

    auto needTo = [&](long long dist) { return dist * L; };

    while (prev < K) {
        long long nextPos = K;
        if (ptr < N) nextPos = min(nextPos, st[ptr].first);

        while (ptr < N && st[ptr].first <= prev + fuel / L) {
            pq.push(st[ptr].second * 100);
            ++ptr;
        }

        long long target = nextPos;
        if (fuel >= needTo(target - prev)) {
            fuel -= needTo(target - prev);
            prev = target;
            if (prev == K) break;
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