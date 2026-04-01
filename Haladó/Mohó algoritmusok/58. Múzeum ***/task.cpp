/*
Feladat: N őrt kell elhelyezni N x N teremben. Az i. őr csak a saját téglalapjában állhat. Az összes termet látni kell (azonos sor/oszlop mentén), viszont őrök ne lássák egymást.
Ötlet: Két őr akkor látja egymást, ha soruk vagy oszlopuk azonos, ezért minden őrnek külön sort és külön oszlopot kell adni. Mivel N őr van N sorra/oszlopra, ez pontosan egy sor-permutáció és egy oszlop-permutáció. A téglalap-feltétel szétválik: sor az [BAS,JFS], oszlop a [BAO,JFO] intervallumban legyen. Tehát két független intervallum-hozzárendelés kell (őr -> egyedi érték 1..N), amit klasszikus greedy-vel oldunk: pozíciónként a legkisebb jobb végű aktív intervallumot választjuk.
Hint 1: || „Ne lássák egymást” => minden őr külön sorban és külön oszlopban legyen. ||
Hint 2: || A téglalap korlátja külön sor- és oszlop-intervallumot ad, ezeket külön is lehet kezelni. ||
Hint 3: || Intervallumokra egyedi értékadásnál használj jobb vég szerint min-kupacot. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Rect {
    int c1, r1, c2, r2;
};

struct Item {
    int l, r, id;
};

static bool assignIntervalValues(int N, const vector<Item>& items, vector<int>& outVal) {
    vector<Item> a = items;
    sort(a.begin(), a.end(), [](const Item& x, const Item& y) {
        if (x.l != y.l) return x.l < y.l;
        if (x.r != y.r) return x.r < y.r;
        return x.id < y.id;
    });

    outVal.assign(N + 1, 0);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; // (r, id)
    int ptr = 0;
    for (int pos = 1; pos <= N; ++pos) {
        while (ptr < N && a[ptr].l <= pos) {
            pq.push({a[ptr].r, a[ptr].id});
            ++ptr;
        }

        while (!pq.empty() && pq.top().first < pos) pq.pop();
        if (pq.empty()) return false;

        auto [r, id] = pq.top();
        pq.pop();
        outVal[id] = pos;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<Rect> rec(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> rec[i].c1 >> rec[i].r1 >> rec[i].c2 >> rec[i].r2;
    }

    vector<Item> rowItems, colItems;
    rowItems.reserve(N);
    colItems.reserve(N);
    for (int i = 1; i <= N; ++i) {
        rowItems.push_back({rec[i].r1, rec[i].r2, i});
        colItems.push_back({rec[i].c1, rec[i].c2, i});
    }

    vector<int> rowOfGuard, colOfGuard;
    if (!assignIntervalValues(N, rowItems, rowOfGuard) ||
        !assignIntervalValues(N, colItems, colOfGuard)) {
        cout << -1 << '\n';
        return 0;
    }

    for (int i = 1; i <= N; ++i) {
        cout << colOfGuard[i] << ' ' << rowOfGuard[i] << '\n';
    }
    return 0;
}
