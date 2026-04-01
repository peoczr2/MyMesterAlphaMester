/*
Feladat: Adottak vendégek jelenléti intervallumai és esemény-időpontok. A lehető legtöbb eseményhez kell tanú, és ehhez minimális számú vendéget kell kiválasztani.
Ötlet: Az eseményeket növekvő sorrendben járjuk. Az aktuális eseményhez betesszük az összes addig induló vendéget egy max-kupacba (távozási idő szerint), és kidobjuk, aki már nem ér rá. Ha van érvényes vendég, kiválasztjuk azt, amelyik legtovább marad; ez minimális tanúszámot ad az adott (maximális) lefedhető eseményhalmazra, mert a legmesszebbre nyúló intervallumot választjuk az első lefedetlen, de lefedhető pontnál.
Hint 1: || Először mindig a legkorábbi még kezeletlen eseményre koncentrálj. ||
Hint 2: || Ha egy esemény lefedhető, a legtovább kitartó tanú választása mohó-optimum. ||
Hint 3: || Az így választott tanúval egyszerre több következő eseményt is „le lehet söpörni”. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Guest {
    int l, r, id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<Guest> guests(N);
    for (int i = 0; i < N; ++i) {
        cin >> guests[i].l >> guests[i].r;
        guests[i].id = i + 1;
    }

    vector<int> ev(M);
    for (int i = 0; i < M; ++i) cin >> ev[i];

    sort(guests.begin(), guests.end(), [](const Guest& a, const Guest& b) {
        if (a.l != b.l) return a.l < b.l;
        if (a.r != b.r) return a.r < b.r;
        return a.id < b.id;
    });

    priority_queue<pair<int,int>> pq; // (r, id)

    int p = 0;
    int covered = 0;
    vector<int> chosen;

    int i = 0;
    while (i < M) {
        int t = ev[i];

        while (p < N && guests[p].l <= t) {
            pq.push({guests[p].r, guests[p].id});
            ++p;
        }
        while (!pq.empty() && pq.top().first < t) pq.pop();

        if (pq.empty()) {
            ++i;
            continue;
        }

        auto [reach, id] = pq.top();
        pq.pop();
        chosen.push_back(id);

        while (i < M && ev[i] <= reach) {
            ++covered;
            ++i;
        }
    }

    cout << covered << '\n';
    cout << chosen.size() << '\n';
    for (int j = 0; j < (int)chosen.size(); ++j) {
        if (j) cout << ' ';
        cout << chosen[j];
    }
    cout << '\n';
    return 0;
}
