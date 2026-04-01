/*
Feladat: Rendezvény-napok adottak, filmesek elérhetőségi intervallumokkal. Maximum hány rendezvényről készülhet film, és ehhez minimum mennyi a költség (A fix + B*forgatott nap / filmes).
Ötlet: Ha E rendezvényről készül film, a B*E rész fix. Így a költség minimalizálása ekvivalens a felvett filmesek számának minimalizálásával. Tehát a feladat: eseménypontok lefedése intervallumokkal úgy, hogy először a lefedett pontok száma maximális legyen, azon belül az intervallumok száma minimális. Ez ugyanaz a mohó, mint pontfedésnél: az első lefedhető, még fedetlen eseménynél a legtovább nyúló intervallumot választjuk.
Hint 1: || A B szorzós tag csak a lefedett rendezvények számától függ. ||
Hint 2: || Max lefedés + min filmes = pontfedő intervallumok mohó választása. ||
Hint 3: || Az első fedhető eseménynél a legnagyobb végpontú filmest válaszd. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Intv {
    int l, r, id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K, F;
    long long A, B;
    cin >> N >> K >> F >> A >> B;

    vector<int> events(K);
    for (int i = 0; i < K; ++i) cin >> events[i];

    vector<Intv> film(F);
    for (int i = 0; i < F; ++i) {
        cin >> film[i].l >> film[i].r;
        film[i].id = i + 1;
    }

    sort(film.begin(), film.end(), [](const Intv& a, const Intv& b) {
        if (a.l != b.l) return a.l < b.l;
        if (a.r != b.r) return a.r < b.r;
        return a.id < b.id;
    });

    priority_queue<pair<int,int>> pq; // (r, id)
    int p = 0;
    int covered = 0;
    int used = 0;

    int i = 0;
    while (i < K) {
        int day = events[i];

        while (p < F && film[p].l <= day) {
            pq.push({film[p].r, film[p].id});
            ++p;
        }
        while (!pq.empty() && pq.top().first < day) pq.pop();

        if (pq.empty()) {
            ++i;
            continue;
        }

        auto [reach, id] = pq.top();
        pq.pop();
        ++used;

        while (i < K && events[i] <= reach) {
            ++covered;
            ++i;
        }
    }

    long long cost = 1LL * used * A + 1LL * covered * B;
    cout << covered << '\n' << cost << '\n';
    return 0;
}
