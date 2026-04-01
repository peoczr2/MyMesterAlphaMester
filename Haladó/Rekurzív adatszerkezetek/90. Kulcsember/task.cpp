/*
Megoldási ötlet:
A kulcsember a fa centroidja: ha eltávolítjuk, a keletkező komponensek közül a legnagyobb mérete a lehető legkisebb.

Gyökerezzük a bandát az 1-es csúcsban, kiszámítjuk minden csúcs részfaméretét, majd minden csúcsra meghatározzuk, hogy
a gyerek-részfák és a gyökér felőli komponens közül mekkora a legnagyobb. Az a csúcs a jó válasz, amelynél ez a maximum
minimális.
*/
/*
Hint 1: || Eltávolítás után minden komponens vagy egy gyerek részfája, vagy a „fent maradó” rész lesz. ||
Hint 2: || Először részfaméret, utána minden csúcsra a legnagyobb keletkező komponens mérete. ||
Hint 3: || A keresett tag a fa centroidja. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> children(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int boss, employee;
        cin >> boss >> employee;
        children[boss].push_back(employee);
        children[employee].push_back(boss);
    }

    vector<int> parent(n + 1, 0), order;
    order.reserve(n);
    vector<int> stack = {1};
    parent[1] = -1;
    while (!stack.empty()) {
        int node = stack.back();
        stack.pop_back();
        order.push_back(node);
        for (int next : children[node]) {
            if (next == parent[node]) continue;
            parent[next] = node;
            stack.push_back(next);
        }
    }

    vector<int> sub(n + 1, 1);
    for (int idx = n - 1; idx >= 0; --idx) {
        int node = order[idx];
        for (int next : children[node]) {
            if (next == parent[node]) continue;
            sub[node] += sub[next];
        }
    }

    int bestNode = 1;
    int bestMax = n;
    for (int node = 1; node <= n; ++node) {
        int largest = n - sub[node];
        for (int next : children[node]) {
            if (next == parent[node]) continue;
            largest = max(largest, sub[next]);
        }
        if (largest < bestMax || (largest == bestMax && node < bestNode)) {
            bestMax = largest;
            bestNode = node;
        }
    }

    cout << bestNode << ' ' << bestMax << '\n';
    return 0;
}
