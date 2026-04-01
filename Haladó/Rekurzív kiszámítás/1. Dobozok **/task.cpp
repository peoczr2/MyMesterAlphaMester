/*
Megoldás lényege:
A dobozokat mindhárom dimenzió szerint növekvő sorrendbe rendezzük a forgatások miatt,
majd a legnagyobb csomagolható sorozatot egy egyszerű O(N^2) dinamikával keressük meg.
Egy doboz belefér egy másikba, ha minden rendezett mérete szigorúan kisebb.

*/

// Hint 1: || A forgathatóság miatt minden dobozt előbb rendezz háromszöggé, majd úgy hasonlítsd össze őket. ||
// Hint 2: || A leghosszabb lánc egy DAG leghosszabb útja: elég az előző, minden dimenzióban kisebb dobozokat nézni. ||
// Hint 3: || Tárold az elődöt is, mert a sorozatot vissza kell fejteni, nem csak a hosszát. ||

#include <bits/stdc++.h>
using namespace std;

struct Box {
    array<int, 3> d;
    int idx;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    vector<Box> boxes(N);
    for (int i = 0; i < N; ++i) {
        cin >> boxes[i].d[0] >> boxes[i].d[1] >> boxes[i].d[2];
        sort(boxes[i].d.begin(), boxes[i].d.end());
        boxes[i].idx = i + 1;
    }

    sort(boxes.begin(), boxes.end(), [](const Box& a, const Box& b) {
        if (a.d != b.d) return a.d < b.d;
        return a.idx < b.idx;
    });

    vector<int> dp(N, 1), parent(N, -1);
    int best = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < i; ++j) {
            if (boxes[j].d[0] < boxes[i].d[0] &&
                boxes[j].d[1] < boxes[i].d[1] &&
                boxes[j].d[2] < boxes[i].d[2] &&
                dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if (dp[i] > dp[best]) best = i;
    }

    vector<int> chain;
    for (int v = best; v != -1; v = parent[v]) chain.push_back(boxes[v].idx);
    reverse(chain.begin(), chain.end());

    cout << chain.size() << '\n';
    for (int i = (int)chain.size() - 1; i >= 0; --i) {
        if (i != (int)chain.size() - 1) cout << ' ';
        cout << chain[i];
    }
    cout << '\n';
    return 0;
}
