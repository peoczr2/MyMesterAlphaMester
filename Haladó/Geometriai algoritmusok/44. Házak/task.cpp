/*
Megoldás: A pontok iránya szerint körbejárunk A körül. Minden élhez azt a szögintervallumot
keressük meg, amelyből A-ból nézve metszi a sugár az élt; ez az a két végponti irány közül az,
amelyik tartalmazza az él felezőirányát. A körsöprés alatt az aktív szakaszok sorrendje nem
változik két esemény között, ezért mindig elegendő a legközelebbi metszést nyilvántartani. Egy
csomópont csak akkor látható, ha a saját sugara mentén nincs nála közelebbi aktív él, és ugyanazon
az irányon csak a legközelebbi csomópont lehet jelölt.
*/

#include <bits/stdc++.h>
using namespace std;

struct Event {
    long long num, den;
    int id;
    int kind; // 0 = add bottom, 1 = add left, 2 = remove bottom, 3 = remove left
};

static bool fracLess(const Event& a, const Event& b) {
    return (__int128)a.num * b.den < (__int128)b.num * a.den;
}

static bool fracEqual(const Event& a, const Event& b) {
    return (__int128)a.num * b.den == (__int128)b.num * a.den;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> x1(n + 1), y1(n + 1), x2(n + 1), y2(n + 1);
    vector<Event> events;
    events.reserve(4LL * n);

    for (int i = 1; i <= n; ++i) {
        cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
        events.push_back({y1[i], x2[i], i, 0});
        events.push_back({y1[i], x1[i], i, 1});
        events.push_back({y1[i], x1[i], i, 2});
        events.push_back({y2[i], x1[i], i, 3});
    }

    sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
        if (fracLess(a, b)) return true;
        if (fracLess(b, a)) return false;
        return a.kind < b.kind;
    });

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> bottomHeap, leftHeap;
    vector<char> bottomAlive(n + 1, false), leftAlive(n + 1, false), visible(n + 1, false);

    auto cleanTop = [](auto& heap, const vector<char>& alive) -> pair<long long, int> {
        while (!heap.empty() && !alive[heap.top().second]) heap.pop();
        if (heap.empty()) return {LLONG_MAX, -1};
        return heap.top();
    };

    int m = (int)events.size();
    for (int i = 0; i < m; ) {
        int j = i;
        while (j < m && fracEqual(events[i], events[j])) ++j;

        Event slope = events[i];
        for (int k = i; k < j; ++k) {
            const auto& e = events[k];
            if (e.kind == 0) {
                bottomAlive[e.id] = true;
                bottomHeap.push({y1[e.id], e.id});
            } else if (e.kind == 1) {
                leftAlive[e.id] = true;
                leftHeap.push({x1[e.id], e.id});
            }
        }

        auto bottomMinExact = cleanTop(bottomHeap, bottomAlive);
        auto leftMinExact = cleanTop(leftHeap, leftAlive);
        if (bottomMinExact.second != -1 && leftMinExact.second != -1) {
            __int128 cmp = (__int128)bottomMinExact.first * slope.den - (__int128)leftMinExact.first * slope.num;
            if (cmp <= 0) visible[bottomMinExact.second] = true;
            if (cmp >= 0) visible[leftMinExact.second] = true;
        } else if (bottomMinExact.second != -1) {
            visible[bottomMinExact.second] = true;
        } else if (leftMinExact.second != -1) {
            visible[leftMinExact.second] = true;
        }

        for (int k = i; k < j; ++k) {
            const auto& e = events[k];
            if (e.kind == 2) bottomAlive[e.id] = false;
            else if (e.kind == 3) leftAlive[e.id] = false;
        }

        if (j < m) {
            auto bottomMin = cleanTop(bottomHeap, bottomAlive);
            auto leftMin = cleanTop(leftHeap, leftAlive);
            if (bottomMin.second != -1 && leftMin.second != -1) {
                __int128 startCmp = (__int128)bottomMin.first * slope.den - (__int128)leftMin.first * slope.num;
                __int128 endCmp = (__int128)bottomMin.first * events[j].den - (__int128)leftMin.first * events[j].num;
                if (startCmp <= 0) {
                    visible[bottomMin.second] = true;
                } else {
                    visible[leftMin.second] = true;
                    if (endCmp <= 0) visible[bottomMin.second] = true;
                }
            } else if (bottomMin.second != -1) {
                visible[bottomMin.second] = true;
            } else if (leftMin.second != -1) {
                visible[leftMin.second] = true;
            }
        }

        i = j;
    }

    vector<int> ans;
    for (int i = 1; i <= n; ++i) {
        if (visible[i]) ans.push_back(i);
    }

    cout << ans.size() << '\n';
    for (size_t i = 0; i < ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
