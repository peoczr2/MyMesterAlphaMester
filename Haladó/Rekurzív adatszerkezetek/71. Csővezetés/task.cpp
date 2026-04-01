/*
Megoldási ötlet:
A kívánt csapokhoz vezető minden útvonal a gyökértől induló egyszerű faút. Ahhoz, hogy ezekhez a csapokhoz víz jusson,
a gyökértől minden kijelölt csapig vezető út összes köztes csapját ki kell nyitni.

Először megjelöljük a kívánt csapokat, majd utólagos bejárással eldöntjük minden csúcsról, hogy van-e a részfájában
kijelölt csap. Ha igen, de maga a csúcs nincs kijelölve, akkor ezt a csapot még ki kell nyitni.
*/
/*
Hint 1: || Minden célcsaphoz a gyökértől vezető úton minden köztes csapot is nyitni kell. ||
Hint 2: || Egy csúcsról elég tudni, hogy van-e a részfájában kijelölt csap. ||
Hint 3: || Azokat a csúcsokat kell kiírni, amelyek részfája tartalmaz célt, de ők maguk nem célcsapok. ||
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
    vector<int> parent(n + 1, 0);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        children[a].push_back(b);
        parent[b] = a;
    }

    int k;
    cin >> k;
    vector<int> target(n + 1, 0);
    for (int i = 0; i < k; ++i) {
        int x;
        cin >> x;
        target[x] = 1;
    }

    vector<int> order;
    order.reserve(n);
    vector<int> stack = {1};
    while (!stack.empty()) {
        int node = stack.back();
        stack.pop_back();
        order.push_back(node);
        for (int child : children[node]) stack.push_back(child);
    }

    vector<int> hasTarget(n + 1, 0);
    for (int idx = n - 1; idx >= 0; --idx) {
        int node = order[idx];
        hasTarget[node] = target[node];
        for (int child : children[node]) hasTarget[node] |= hasTarget[child];
    }

    vector<int> answer;
    for (int node = 1; node <= n; ++node) {
        if (hasTarget[node] && !target[node]) answer.push_back(node);
    }

    cout << answer.size() << '\n';
    for (int i = 0; i < static_cast<int>(answer.size()); ++i) {
        if (i) cout << ' ';
        cout << answer[i];
    }
    cout << '\n';
    return 0;
}
