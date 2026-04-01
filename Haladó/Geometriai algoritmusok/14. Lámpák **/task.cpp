/*
Megoldás lényege:
Az egyes lámpák által megvilágított tartományokat egyesítjük, és ebből következtetünk a látható szakaszokra. A lényeg a fedett intervallumok pontos kezelése.
*/
#include <bits/stdc++.h>
using namespace std;

struct House {
    long long x, w, h;
};

struct Interval {
    int l, r;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    if (!(cin >> n >> k)) return 0;

    vector<House> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i].x >> a[i].w >> a[i].h;

    if (n == 1) {
        cout << 0 << '\n';
        return 0;
    }

    vector<Interval> intervals;
    intervals.reserve(n - 1);

    const long double EPS = 1e-18L;

    for (int g = 1; g < n; ++g) {
        long long leftEdge = a[g].x + a[g].w;
        long long rightEdge = a[g + 1].x;
        long double lampX = ((long double)leftEdge + (long double)rightEdge) / 2.0L;
        long double lampY = (long double)k;

        int L = g, R = g + 1;

        long double prev = numeric_limits<long double>::infinity();
        for (int i = g; i >= 1; --i) {
            long double cornerX = (long double)(a[i].x + a[i].w);
            long double s = (lampY - (long double)a[i].h) / (lampX - cornerX);
            if (i == g || s <= prev + EPS) {
                L = i;
                prev = s;
            } else {
                break;
            }
        }

        prev = numeric_limits<long double>::infinity();
        for (int i = g + 1; i <= n; ++i) {
            long double cornerX = (long double)a[i].x;
            long double s = (lampY - (long double)a[i].h) / (cornerX - lampX);
            if (i == g + 1 || s <= prev + EPS) {
                R = i;
                prev = s;
            } else {
                break;
            }
        }

        intervals.push_back({L, R});
    }

    sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b) {
        if (a.l != b.l) return a.l < b.l;
        return a.r > b.r;
    });

    int ans = 0;
    int covered = 0;
    int idx = 0;
    while (covered < n) {
        int best = covered;
        while (idx < (int)intervals.size() && intervals[idx].l <= covered + 1) {
            best = max(best, intervals[idx].r);
            ++idx;
        }
        if (best == covered) {
            cout << 0 << '\n';
            return 0;
        }
        ++ans;
        covered = best;
    }

    cout << ans << '\n';
    return 0;
}
