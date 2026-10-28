/*
Megoldás lényege:
Egy vágás költsége a vágott darab hossza, és a teljes költség a fordított folyamatban (összeragasztás) pontosan a vágási fa belső csúcsainak hosszösszege. Ezért mindig a két legkisebb darabot érdemes összevonni (Huffman-stratégia): a kicsi darabok így kevesebbszer kerülnek bele a költségbe. Az összevonásokat min-heap segítségével végezzük, az időigény O(N log N). A vágási sorrendet a kialakult fából gyökértől indulva, preorder bejárással írjuk ki, így minden vágás olyan darabot vág, amely a korábbi lépésekből már létezik. Ha több optimális sorrend is van, bármelyik megadható.
*/
/*
Hint 1: || Fordítsd meg a folyamatot: képzeld, hogy a darabokat ragasztod össze, és minden ragasztás költsége az új darab hossza. ||
Hint 2: || Mindig a két legrövidebb darabot ragaszd össze; ezt min-heapből egyszerűen kiveheted, az összegüket pedig visszateszed a heapbe. ||
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