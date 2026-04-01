/*
Feladat: A rúdból levágandó darabok összköltségét kell minimalizálni.
Ötlet: Mindig a két legkisebb még különálló darabot érdemes összevonni először, mert ezek többször vesznek részt a további vágásokban. Ez a Huffman-stratégia.
Hint 1: || Egy vágás költsége mindig az éppen vágott darab hossza. ||
Hint 2: || A kisebb darabokat érdemes előbb összevonni, hogy később kevesebbszer fizessük meg őket. ||
Hint 3: || A vágási sorrendet egy min-heapből lehet felépíteni. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    struct Node { long long len; int l = -1, r = -1; };
    vector<Node> nodes;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;
        nodes.push_back({x, -1, -1});
        pq.push({x, (int)nodes.size() - 1});
    }

    long long cost = 0;
    while (pq.size() > 1) {
        auto [aLen, aId] = pq.top(); pq.pop();
        auto [bLen, bId] = pq.top(); pq.pop();
        cost += aLen + bLen;
        nodes.push_back({aLen + bLen, aId, bId});
        pq.push({aLen + bLen, (int)nodes.size() - 1});
    }

    int root = pq.top().second;
    vector<pair<long long, long long>> steps;
    function<void(int)> emit = [&](int u) {
        if (nodes[u].l == -1) return;
        long long left = nodes[nodes[u].l].len;
        steps.push_back({nodes[u].len, left});
        emit(nodes[u].l);
        emit(nodes[u].r);
    };
    emit(root);

    cout << cost << '\n';
    for (auto [len, cut] : steps) cout << len << ' ' << cut << '\n';
    return 0;
}