/*
Megoldás lényege:
A könyvtár csak körüljárási lekérdezést ad, ezért a pontokat az 1. pont körüli szögrendezéssel dolgozzuk fel: a 2. ponttal történő félsíkos felosztás után minden félsíkban a szögek 180 foknál kisebb tartományban vannak, így a rendezés lekérdezésekkel egyértelmű. Ha az 1. pont körül van 180 foknál nagyobb rés, az 1. pont konvex burok csúcs, és a rés utáni kezdéssel Graham-bejárás adja a csúcsokat. Különben az 1. pont belső pont, a körbejárás csillagalakú sokszög, amelynek minden befelé forduló csúcsa a két szomszédjával és az 1. ponttal alkotott háromszögben van, így törölhető; a maradék konvex sokszög csúcsainak száma a válasz. A lekérdezések száma n ≤ 40 000 esetén kb. n log n, azaz 10^6 alatt marad.
*/
/*
Hint 1: || A koordináták nem ismertek, csak háromszögek körüljárása; ezért egy biztos pont körüli szögrendezést kell összehasonlító lekérdezésekkel megvalósítani, és a pontokat előbb a 2. ponthoz képest két félsíkba kell osztani. ||
Hint 2: || Ha a rendezett sorrendben az 1. ponttól 180 foknál nagyobb rés van, az 1. pont burokcsúcs: a rés utáni elemtől kezdve Graham-bejárással megkapod a csúcsokat. ||
Hint 3: || Ha az 1. pont belső pont, a körbejárás csillagalakú sokszög; egy csúcs, amely a szomszédai között befelé hajlik, nem burokcsúcs, ezért törölhető, és csak a törlés után szomszédai újraellenőrzése szükséges. ||
*/
#include "trilib.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = get_n();
    const int p = 1, r = 2;   // p: pivot point, r: reference point for the angular split

    // Split the other points by the side of the directed line p->r.
    vector<int> L, R;
    for (int x = 3; x <= n; x++) {
        if (!is_clockwise(p, r, x)) L.push_back(x);   // left side: angles (0, 180) seen from r
        else R.push_back(x);                          // right side: angles (180, 360)
    }
    // u before v iff v lies counterclockwise from u around p (valid inside one half-plane)
    auto ccwLess = [&](int u, int v) { return !is_clockwise(p, u, v); };
    stable_sort(L.begin(), L.end(), ccwLess);
    stable_sort(R.begin(), R.end(), ccwLess);

    // Cyclic order of all points except p, counterclockwise around p.
    vector<int> cyc;
    cyc.push_back(r);
    cyc.insert(cyc.end(), L.begin(), L.end());
    cyc.insert(cyc.end(), R.begin(), R.end());
    const int m = (int)cyc.size();                    // = n - 1

    // p is a hull vertex iff some consecutive pair spans an angle larger than 180 degrees.
    int bigGap = -1;
    for (int i = 0; i < m; i++) {
        if (is_clockwise(p, cyc[i], cyc[(i + 1) % m])) { bigGap = i; break; }
    }

    if (bigGap >= 0) {
        // Case A: p is a hull vertex. Graham scan around p, starting after the big gap.
        vector<int> st;
        st.push_back(p);
        for (int t = 0; t < m; t++) {
            int x = cyc[(bigGap + 1 + t) % m];
            while (st.size() >= 2 && is_clockwise(st[st.size() - 2], st.back(), x)) st.pop_back();
            st.push_back(x);
        }
        give_answer((int)st.size());
        return 0;
    }

    // Case B: p is inside the hull. The cycle cyc is a star-shaped polygon around p.
    // A reflex vertex v (clockwise turn at v between its current neighbours a and b) lies in
    // triangle (p, a, b), so v is not a hull vertex and can be deleted.
    vector<int> prv(m), nxt(m);
    vector<char> alive(m, 1);
    for (int i = 0; i < m; i++) {
        prv[i] = (i + m - 1) % m;
        nxt[i] = (i + 1) % m;
    }
    vector<int> work(m);
    for (int i = 0; i < m; i++) work[i] = i;
    int cnt = m;
    while (!work.empty() && cnt > 3) {
        int i = work.back();
        work.pop_back();
        if (!alive[i]) continue;
        int a = prv[i], b = nxt[i];
        if (is_clockwise(cyc[a], cyc[i], cyc[b])) {
            alive[i] = 0;
            cnt--;
            nxt[a] = b;
            prv[b] = a;
            work.push_back(a);
            work.push_back(b);
        }
    }
    give_answer(cnt);
    return 0;
}
