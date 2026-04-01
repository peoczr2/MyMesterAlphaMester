/*
Feladat: Tréning-időszakokra szállásajánlatokból kell minimális számút választani úgy, hogy a lefedett tréningnapok száma maximális legyen.
Ötlet: A tréning-intervallumok unióját (célhalmaz) fedjük ajánlat-intervallumokkal. Balról jobbra haladunk: az aktuális még fedetlen, de potenciálisan fedhető ponthoz az addig induló ajánlatok közül a legtovább nyúlót választjuk (max-end heap). Ha egy pont nem fedhető, ugrunk a következő ajánlat indulására. Ez adja a maximális lefedést, és azon belül minimális ajánlatszámot.
Hint 1: || Először vond össze az átfedő tréningidőszakokat (célintervallumok). ||
Hint 2: || A következő fedendő pontnál mindig a legnagyobb végpontú elérhető ajánlatot válaszd. ||
Hint 3: || Ha pont nem fedhető, ugrás a következő ajánlat startjára megőrzi az optimalitást. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Seg {
    int l, r;
};

struct Offer {
    int l, r, id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;

    vector<Seg> tr(M);
    for (int i = 0; i < M; ++i) cin >> tr[i].l >> tr[i].r;

    // Tréningek összevonása.
    sort(tr.begin(), tr.end(), [](const Seg& a, const Seg& b) {
        if (a.l != b.l) return a.l < b.l;
        return a.r < b.r;
    });
    vector<Seg> target;
    for (auto s : tr) {
        if (target.empty() || s.l > target.back().r + 1) target.push_back(s);
        else target.back().r = max(target.back().r, s.r);
    }

    vector<Offer> off(N);
    for (int i = 0; i < N; ++i) {
        cin >> off[i].l >> off[i].r;
        off[i].id = i + 1;
    }
    sort(off.begin(), off.end(), [](const Offer& a, const Offer& b) {
        if (a.l != b.l) return a.l < b.l;
        if (a.r != b.r) return a.r < b.r;
        return a.id < b.id;
    });

    priority_queue<pair<int,int>> pq; // (r, id)
    vector<int> chosen;
    chosen.reserve(N);

    long long covered = 0;
    int p = 0;
    long long carryEnd = LLONG_MIN; // utolsó választott ajánlat vége

    for (auto seg : target) {
        long long cur = seg.l;

        if (carryEnd >= cur) {
            long long x = min<long long>(carryEnd, seg.r);
            covered += x - cur + 1;
            cur = x + 1;
        }

        while (cur <= seg.r) {
            while (p < N && off[p].l <= cur) {
                pq.push({off[p].r, off[p].id});
                ++p;
            }

            while (!pq.empty() && pq.top().first < cur) pq.pop();

            if (pq.empty()) {
                if (p < N && off[p].l <= seg.r) {
                    cur = max<long long>(cur + 1, off[p].l);
                    if (carryEnd >= cur) {
                        long long x = min<long long>(carryEnd, seg.r);
                        covered += x - cur + 1;
                        cur = x + 1;
                    }
                    continue;
                }
                break;
            }

            auto [r, id] = pq.top();
            pq.pop();
            chosen.push_back(id);
            carryEnd = r;

            long long x = min<long long>(carryEnd, seg.r);
            if (x >= cur) {
                covered += x - cur + 1;
                cur = x + 1;
            } else {
                ++cur;
            }
        }
    }

    cout << covered << '\n';
    cout << chosen.size() << '\n';
    for (int i = 0; i < (int)chosen.size(); ++i) {
        if (i) cout << ' ';
        cout << chosen[i];
    }
    cout << '\n';
    return 0;
}
