/*
Megoldás lényege:
Ha az A->B egyenes minden más pont bal oldalán van, akkor A->B a pontok konvex burkának óramutató-ellenkező irányú éle, és az egyenesen A-n és B-n kívül nincs más pont. Ezért a konvex burkot kell megadni: rendezés után monoton lánccal O(N log N) időben. A határ egy egyenesre eső pontjait is megtartjuk, és csak azokat az éleket írjuk ki, amelyeken A és B mellett nincs más pont.
*/
/*
Hint 1: || Melyik A,B párra lesz igaz, hogy a többi pont mind az A->B egyenes bal oldalán van? Gondolj a pontok konvex burkára: melyik éle, milyen irányban bejárva. ||
Hint 2: || A konvex burkot rendezés után monoton lánccal kapod meg. Vigyázz az egy egyenesre eső határpontokkal: ha egy burokél mentén más pont is van, az él nem felel meg, ezt a szomszédos határpontok ellenőrzésével szűrheted ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
    int id;
};

static long long cross(const Pt& a, const Pt& b, const Pt& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// A konvex burok határa óramutató-ellenkezőleg, a határon lévő egy egyenesre eső pontokkal együtt.
static vector<Pt> boundary(vector<Pt> pts) {
    sort(pts.begin(), pts.end(), [](const Pt& a, const Pt& b) {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        return a.id < b.id;
    });
    vector<Pt> lower, upper;
    for (const auto& p : pts) {
        while (lower.size() >= 2 && cross(lower[lower.size() - 2], lower.back(), p) < 0) lower.pop_back();
        lower.push_back(p);
    }
    for (int i = (int)pts.size() - 1; i >= 0; --i) {
        const auto& p = pts[i];
        while (upper.size() >= 2 && cross(upper[upper.size() - 2], upper.back(), p) < 0) upper.pop_back();
        upper.push_back(p);
    }
    lower.pop_back();
    upper.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<Pt> pts(n);
    for (int i = 0; i < n; ++i) {
        cin >> pts[i].x >> pts[i].y;
        pts[i].id = i + 1;
    }

    vector<Pt> B = boundary(pts);
    int m = (int)B.size();
    vector<pair<int, int>> ans;
    for (int k = 0; k < m; ++k) {
        const Pt& a = B[k];
        const Pt& b = B[(k + 1) % m];
        const Pt& prev = B[(k - 1 + m) % m];
        const Pt& next = B[(k + 2) % m];
        // a és b között nincs más pont az egyenesen, ha a szomszédos határpontok nincsenek rajta
        if (cross(prev, a, b) == 0 || cross(a, b, next) == 0) continue;
        ans.push_back({a.id, b.id});
    }

    cout << ans.size() << '\n';
    for (auto [u, v] : ans) cout << u << ' ' << v << '\n';
    return 0;
}
