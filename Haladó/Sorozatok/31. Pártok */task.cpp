/*
Megoldas lenyege:
Mindkét országban az egyes választások között állandó a kormányzó párt típusa.
A dátumokat napindexre alakítjuk, így az egyes időszakok félopen intervallumok
lesznek: a választás napjától a következő választás napjáig tartanak. Ezután a
két ország szakaszait közös időtengelyen végigsöpörve kiválogatjuk azokat a
részeket, ahol a két jelleg megegyezik, majd az egymás melletti azonos részeket
összefűzzük.
*/
/*
Hint 1: || A választás napjától a következő választás napjáig egyetlen párt típusa marad érvényben. ||
Hint 2: || Dátumokból csinálj napindexet, hogy egyszerű legyen az összehasonlítás és a szomszédos napok kezelése. ||
Hint 3: || A közös időszakok a két ország azonos típusú szakaszainak metszetei. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Date {
    int y, m, d;
};

static long long days_from_civil(int y, int m, int d) {
    y -= m <= 2;
    const long long era = (y >= 0 ? y : y - 399) / 400;
    const unsigned yoe = (unsigned)(y - era * 400);
    const unsigned doy = (153u * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;
    const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
    return era * 146097 + (long long)doe - 719468;
}

static Date civil_from_days(long long z) {
    z += 719468;
    const long long era = (z >= 0 ? z : z - 146096) / 146097;
    const unsigned doe = (unsigned)(z - era * 146097);
    const unsigned yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;
    long long y = (long long)yoe + era * 400;
    const unsigned doy = doe - (365 * yoe + yoe / 4 - yoe / 100);
    const unsigned mp = (5 * doy + 2) / 153;
    unsigned d = doy - (153 * mp + 2) / 5 + 1;
    unsigned m = mp + (mp < 10 ? 3 : -9);
    y += (m <= 2);
    return {(int)y, (int)m, (int)d};
}

struct Segment {
    long long l, r;
    char type;
};

static vector<Segment> buildSegments(vector<pair<long long, char>> elections, long long endDay) {
    sort(elections.begin(), elections.end());
    vector<Segment> segs;
    for (int i = 0; i < (int)elections.size(); ++i) {
        long long l = elections[i].first;
        long long r = (i + 1 < (int)elections.size() ? elections[i + 1].first : endDay + 1);
        segs.push_back({l, r, elections[i].second});
    }
    return segs;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int y, m, d;
    cin >> y >> m >> d;
    long long current = days_from_civil(y, m, d);

    int n;
    cin >> n;
    vector<pair<long long, char>> a(n);
    for (int i = 0; i < n; ++i) {
        char c;
        int yy, mm, dd;
        cin >> c >> yy >> mm >> dd;
        a[i] = {days_from_civil(yy, mm, dd), c};
    }

    int k;
    cin >> k;
    vector<pair<long long, char>> b(k);
    for (int i = 0; i < k; ++i) {
        char c;
        int yy, mm, dd;
        cin >> c >> yy >> mm >> dd;
        b[i] = {days_from_civil(yy, mm, dd), c};
    }

    auto sa = buildSegments(a, current);
    auto sb = buildSegments(b, current);

    vector<long long> cuts = {current + 1};
    for (auto &s : sa) {
        cuts.push_back(s.l);
        cuts.push_back(s.r);
    }
    for (auto &s : sb) {
        cuts.push_back(s.l);
        cuts.push_back(s.r);
    }
    sort(cuts.begin(), cuts.end());
    cuts.erase(unique(cuts.begin(), cuts.end()), cuts.end());

    auto typeAt = [](const vector<Segment>& segs, long long x) {
        int lo = 0, hi = (int)segs.size() - 1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (segs[mid].l <= x && x < segs[mid].r) return segs[mid].type;
            if (x < segs[mid].l) hi = mid - 1;
            else lo = mid + 1;
        }
        return '?';
    };

    vector<pair<long long, long long>> ans;
    for (int i = 0; i + 1 < (int)cuts.size(); ++i) {
        long long l = cuts[i];
        long long r = cuts[i + 1];
        if (l >= r || l > current) continue;
        char ta = typeAt(sa, l);
        char tb = typeAt(sb, l);
        if (ta == tb) {
            long long rr = min(r, current + 1);
            if (!ans.empty() && ans.back().second == l) ans.back().second = rr;
            else ans.push_back({l, rr});
        }
    }

    cout << ans.size() << '\n';
    for (auto [l, r] : ans) {
        Date dl = civil_from_days(l);
        Date dr = civil_from_days(r - 1);
        cout << dl.y << ' ' << dl.m << ' ' << dl.d << ' ' << dr.y << ' ' << dr.m << ' ' << dr.d << '\n';
    }
    return 0;
}
