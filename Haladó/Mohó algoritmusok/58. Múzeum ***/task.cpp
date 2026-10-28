/*
Megoldás lényege:
Két őr akkor látja egymást, ha azonos sorban vagy oszlopban áll, ezért minden sorban és minden oszlopban pontosan egy őrnek kell lennie. Így az oszlopokat és a sorokat is egy-egy permutációval kell kiosztani: az i. őr oszlopa a [BAO, JFO], sora a [BAS, JFS] intervallumból való. A két hozzárendelés független, mert az oszlop- és a sorintervallumok külön kezelhetők. Intervallumok egyedi értékekkel való lefedésére a mohó módszer működik: pozíciónként 1-től N-ig a még aktív intervallumok közül azt választjuk, amelynek jobb vége a legkisebb. Ha valamelyik pozícióhoz nem jut intervallum, nincs megoldás, és -1 kerül a kimenetre. Az időigény O(N log N).
*/
/*
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
