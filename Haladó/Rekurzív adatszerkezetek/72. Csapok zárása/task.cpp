/*
Megoldási ötlet:
Azokat a csúcsokat kell bezárni, amelyek részfájában nincs kívánt csap, de a szülőjük részfájában már van.
Így pontosan a kívánt csapokhoz vezető utakat nem vágjuk el, az összes többi ágat viszont a lehető legmagasabban
lezárjuk.

Ez ugyanazt a részfa-jelölést használja, mint a nyitós feladat: utólagos bejárással kiszámítjuk, hogy mely részfák
tartalmaznak kívánt csapot, majd a maximalis nem-kívánt részfák gyökereit választjuk.
*/
/*
Hint 1: || Ha egy részfában nincs kívánt csap, azt érdemes a lehető legfelső csúcsnál levágni. ||
Hint 2: || Egy csúcs akkor kerül a válaszba, ha az ő részfája üres a célok szempontjából, de a szülőjéé nem. ||
Hint 3: || Ez a maximális olyan csúcsok halmaza, amelyek alatt nincs célcsap. ||
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
        if (!hasTarget[node] && (parent[node] == 0 || hasTarget[parent[node]])) answer.push_back(node);
    }

    cout << answer.size() << '\n';
    for (int i = 0; i < static_cast<int>(answer.size()); ++i) {
        if (i) cout << ' ';
        cout << answer[i];
    }
    cout << '\n';
    return 0;
}
