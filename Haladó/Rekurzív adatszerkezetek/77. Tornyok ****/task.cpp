/*
Megoldási ötlet:
Egy épület akkor látható az adótoronyról, ha a torony magasabb nála, és tőle nyugatra nem áll nála magasabb vagy vele
azonos épület. Ez azt jelenti, hogy egy i. épülethez az érvényes toronyhelyek egy összefüggő intervallumot alkotnak: a
legutóbbi nála magasabb épület utáni helyektől az i. épület előtti helyig.

Minden épülethez kiszámítjuk a bal oldali legközelebbi magasabb épületet, és ebből intervallumot képezünk. Ha a torony
magassága kisebb, mint az épületé, az interval nem aktív. A toronyhát végül az aktív intervallumok fedésének maximális
értéke adja, amit magas­ság szerint offline feldolgozással és szegmensfás tartományfrissítéssel számolunk.
*/
/*
Hint 1: || Egy épület láthatósága egy toronyhelyekből álló intervallumra korlátozódik. ||
Hint 2: || A bal oldali legközelebbi magasabb épület adja az intervallum bal szélét. ||
Hint 3: || A különböző toronymagasságokat növekvő sorrendben feldolgozva csak intervallumokat kell hozzáadni. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct SegTree {
    int n;
    vector<int> mx, lazy;
    explicit SegTree(int n) : n(n), mx(4 * (n + 2), 0), lazy(4 * (n + 2), 0) {}

    void apply(int node, int value) {
        mx[node] += value;
        lazy[node] += value;
    }

    void push(int node) {
        if (lazy[node] == 0) return;
        apply(node * 2, lazy[node]);
        apply(node * 2 + 1, lazy[node]);
        lazy[node] = 0;
    }

    void update(int node, int l, int r, int ql, int qr, int value) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            apply(node, value);
            return;
        }
        push(node);
        int mid = (l + r) / 2;
        update(node * 2, l, mid, ql, qr, value);
        update(node * 2 + 1, mid + 1, r, ql, qr, value);
        mx[node] = max(mx[node * 2], mx[node * 2 + 1]);
    }
};

struct TowerQuery {
    int h;
    int idx;
};

struct Building {
    int h;
    int l;
    int r;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> heights(n + 1);
    for (int i = 1; i <= n; ++i) cin >> heights[i];
    vector<int> queryHeights(q);
    for (int i = 0; i < q; ++i) cin >> queryHeights[i];

    vector<int> nextGreater(n + 1, n + 1);
    vector<int> st;
    for (int i = n; i >= 1; --i) {
        while (!st.empty() && heights[st.back()] < heights[i]) st.pop_back();
        nextGreater[i] = st.empty() ? n + 1 : st.back();
        st.push_back(i);
    }

    vector<Building> buildings;
    buildings.reserve(n);
    for (int i = 1; i <= n; ++i) {
        buildings.push_back({heights[i], i, nextGreater[i] - 1});
    }
    sort(buildings.begin(), buildings.end(), [](const Building& a, const Building& b) {
        return a.h < b.h;
    });

    vector<TowerQuery> queries;
    queries.reserve(q);
    for (int i = 0; i < q; ++i) queries.push_back({queryHeights[i], i});
    sort(queries.begin(), queries.end(), [](const TowerQuery& a, const TowerQuery& b) {
        return a.h < b.h;
    });

    SegTree seg(n);
    vector<int> answer(q, 0);
    int ptr = 0;
    for (const auto& query : queries) {
        while (ptr < n && buildings[ptr].h < query.h) {
            if (buildings[ptr].l <= buildings[ptr].r) {
                seg.update(1, 1, n, buildings[ptr].l, buildings[ptr].r, 1);
            }
            ++ptr;
        }
        answer[query.idx] = seg.mx[1];
    }

    for (int i = 0; i < q; ++i) {
        if (i) cout << ' ';
        cout << answer[i];
    }
    cout << '\n';
    return 0;
}
