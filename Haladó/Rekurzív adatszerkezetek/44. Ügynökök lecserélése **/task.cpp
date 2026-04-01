/*
Megoldási ötlet:
Az ügynökszervezet egy gyökerezett fa. Ha lecserélünk egy ügynököt, akkor az egész részfáját „lefedjük”, ezért onnan
már nem érdemes senki mást lecserélni. Csak olyan csúcs választható, amelynek legfeljebb 2 közvetlen beosztottja van.

Ezért minden részfára fa-knapsack DP-t számolunk. A `dp[u][k]` azt jelenti, hogy az `u` részfájában legfeljebb mennyi
ember fedhető le pontosan `k` lecserélt ügynökkel.
- Ha `u`-t nem cseréljük le, akkor a gyerekrészfák eredményeit kell összefésülni.
- Ha `u` lecserélhető, akkor önmagában egyetlen választással lefedi az egész `u` részfát.

A gyökér DP-jéből az első olyan `k` kell, amellyel legalább `ceil(N/2)` ember lefedhető.
*/
/*
Hint 1: || Egy lecserélt ügynök részfájában már nincs értelme további ügynököt lecserélni, mert a lefedés átfedne. ||
Hint 2: || Ha nem a szülőt választod, akkor a gyerekrészfák függetlenül kombinálhatók. ||
Hint 3: || A cél nem az összlefedés maximalizálása mindenáron, hanem a minimum darabszám elérése legalább fél szervezetre. ||
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

    vector<int> parent(n + 1, 0), childCount(n + 1, 0);
    vector<vector<int>> children(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int node, boss;
        cin >> node >> boss;
        parent[node] = boss;
        children[boss].push_back(node);
        ++childCount[boss];
    }

    int root = 1;
    while (parent[root] != 0) {
        root = parent[root];
    }

    vector<int> order;
    order.reserve(n);
    vector<int> depth(n + 1, 0), subtree(n + 1, 1);
    vector<pair<int, int>> stack = {{root, 0}};
    while (!stack.empty()) {
        auto [node, phase] = stack.back();
        stack.pop_back();
        if (phase == 0) {
            stack.push_back({node, 1});
            for (int child : children[node]) {
                depth[child] = depth[node] + 1;
                stack.push_back({child, 0});
            }
        } else {
            order.push_back(node);
        }
    }

    for (int node : order) {
        for (int child : children[node]) {
            subtree[node] += subtree[child];
        }
    }

    const int need = (n + 1) / 2;
    const int negInf = -1e9;
    vector<vector<int>> dp(n + 1);

    for (int node : order) {
        vector<int> current(1, 0);
        for (int child : children[node]) {
            vector<int> merged(min(need, static_cast<int>(current.size() + dp[child].size() - 1)), negInf);
            for (int usedHere = 0; usedHere < static_cast<int>(current.size()); ++usedHere) {
                if (current[usedHere] < 0) {
                    continue;
                }
                for (int usedChild = 0; usedChild < static_cast<int>(dp[child].size()); ++usedChild) {
                    if (dp[child][usedChild] < 0) {
                        continue;
                    }
                    int totalUsed = usedHere + usedChild;
                    if (totalUsed >= need) {
                        break;
                    }
                    merged[totalUsed] = max(merged[totalUsed], min(need, current[usedHere] + dp[child][usedChild]));
                }
            }
            current.swap(merged);
            vector<int>().swap(dp[child]);
        }

        if (childCount[node] <= 2) {
            if (static_cast<int>(current.size()) < 2) {
                current.resize(2, negInf);
            }
            current[1] = max(current[1], min(need, subtree[node]));
        }

        dp[node] = move(current);
    }

    int answer = need;
    for (int used = 1; used < static_cast<int>(dp[root].size()); ++used) {
        if (dp[root][used] >= need) {
            answer = used;
            break;
        }
    }

    cout << answer << '\n';
    return 0;
}