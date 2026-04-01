/*
Megoldás lényege:
Geometriai optimalizálási feladat, ahol a korlátok között kell a legjobb elrendezést megtalálni. A megoldás a helyzetek struktúráját használja ki, nem bruteforce-ol.
*/
#include <bits/stdc++.h>
using namespace std;

static long long floor_div(long long a, long long b) {
    if (a >= 0) return a / b;
    return -(( -a + b - 1) / b);
}

static long long ceil_div(long long a, long long b) {
    if (a >= 0) return (a + b - 1) / b;
    return -((-a) / b);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long h, s;
    if (!(cin >> n >> h >> s)) return 0;

    vector<int> hiddenDiff(s + 3, 0);
    vector<int> badDiff(s + 3, 0);

    for (int i = 0; i < n; ++i) {
        long long x, y;
        cin >> x >> y;

        if (x == 0 && y == 0) {
            continue;
        }

        long long denom = x + y;
        long long l = max<long long>({0, s - y, ceil_div(x * s - y * h, denom)});
        long long r = min<long long>({s, x, floor_div(x * (s + h), denom)});
        if (l <= r) {
            ++hiddenDiff[l];
            --hiddenDiff[r + 1];
        }

        long long badL = max<long long>({0, x - h, s - y});
        long long badR = min<long long>({s, x, s - y + h});
        if (badL <= badR) {
            ++badDiff[badL];
            --badDiff[badR + 1];
        }
    }

    int hidden = 0;
    int bad = 0;
    int bestCount = -1;
    long long bestX = -1;

    for (long long x = 0; x <= s; ++x) {
        hidden += hiddenDiff[x];
        bad += badDiff[x];
        if (bad == 0) {
            if (hidden > bestCount || (hidden == bestCount && x > bestX)) {
                bestCount = hidden;
                bestX = x;
            }
        }
    }

    if (bestCount < 0) {
        cout << -1 << '\n';
        return 0;
    }

    cout << bestCount << '\n' << bestX << ' ' << (s - bestX) << '\n';
    return 0;
}