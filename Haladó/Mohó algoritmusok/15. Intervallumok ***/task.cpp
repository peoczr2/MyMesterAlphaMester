/*
Feladat: A lehető legkevesebb embert kell kiválasztani úgy, hogy mindenki legalább egy kiválasztott emberrel átfedésben legyen.
Ötlet: Ez intervallumgráf minimum domináló halmaz feladat. Mohó stratégia: mindig vesszük a legkisebb jobb végpontú még nem dominált intervallumot v, majd v szomszédai közül azt választjuk u-nak, amelyiknek a jobb vége a legnagyobb. Ezután u minden szomszédját domináljuk, és ismétlünk.
Hint 1: || A „hír eljut” feltétel pontosan azt jelenti, hogy minden intervallum metszi valamelyik kiválasztottat. ||
Hint 2: || A legkorábban „lejáró” még lefedetlen intervallum jó kapaszkodó egy mohó lépéshez. ||
Hint 3: || Ha ebből annak a szomszédját választod, amelyik jobbra a legtovább nyúlik, tipikusan több jövőbeli intervallumot is lefedsz. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Interval {
    int l, r, id;
};

static inline bool overlap(const Interval& a, const Interval& b) {
    return max(a.l, b.l) <= min(a.r, b.r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Interval> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].l >> a[i].r;
        a[i].id = i + 1;
    }

    sort(a.begin(), a.end(), [](const Interval& x, const Interval& y) {
        if (x.r != y.r) return x.r < y.r;
        return x.l < y.l;
    });

    vector<char> dominated(n, 0);
    vector<int> ans;
    int dominatedCnt = 0;

    while (dominatedCnt < n) {
        int i = -1;
        for (int k = 0; k < n; ++k) {
            if (!dominated[k]) {
                i = k;
                break;
            }
        }

        Interval v = a[i];
        int best = -1;
        int bestR = -1;
        for (int k = i; k < n; ++k) {
            if (overlap(a[k], v) && a[k].r > bestR) {
                bestR = a[k].r;
                best = k;
            }
        }

        Interval u = a[best];
        ans.push_back(u.id);

        for (int k = 0; k < n; ++k) {
            if (!dominated[k] && overlap(a[k], u)) {
                dominated[k] = 1;
                ++dominatedCnt;
            }
        }
    }

    cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
