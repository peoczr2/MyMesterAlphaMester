/*
Megoldási ötlet:
A társaság fáját gyökerezzük az 1-es csúcsban. Egy címzett pontosan akkor jó, ha az A-ból induló útban összesen K+1 él van, és ezen az úton az első L lépés felfelé, a maradék pedig lefelé megy. Ezért elég az A összes ősét végigjárni.

Minden csúcsra eltároljuk a mélységét, a belépési és kilépési időpontját, valamint mélységenként a subtree-belépési időpontokat rendezett listában. Így egy tetszőleges csúcs részfájában, egy adott mélységen lévő csúcsok száma bináris kereséssel lekérdezhető.

Ha az aktuális ős U L lépésre van A-tól, akkor a címzettek azok a csúcsok, amelyek U részfájában pontosan K+1-L mélységgel lejjebb vannak, de ha L>0, akkor ki kell vonni azt a gyerekágat, amelyen visszaérnénk A felé. Ezzel minden L-re O(log N) időben megkapjuk a darabszámot.
*/
/*
Hint 1: || A küldemény útja mindig egyetlen felfelé menő szakaszból és utána egy lefelé menő szakaszból áll. ||
Hint 2: || Egy részfában egy adott mélységhez tartozó csúcsok száma Euler-számozással és bináris kereséssel gyorsan megszámolható. ||
Hint 3: || Az A-tól felfelé haladva minden ősre külön számold ki, hány csúcs érhető el pontosan a maradék lépésekkel. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, a, k;
    cin >> n >> m >> a >> k;

    vector<vector<int>> children(n + 1);
    vector<int> parent(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int boss, cnt;
        cin >> boss >> cnt;
        children[boss].reserve(children[boss].size() + cnt);
        for (int j = 0; j < cnt; ++j) {
            int child;
            cin >> child;
            children[boss].push_back(child);
            parent[child] = boss;
        }
    }

    vector<int> depth(n + 1, 0), tin(n + 1, 0), tout(n + 1, 0);
    vector<vector<int>> byDepth(n + 1);
    int timer = 0;
    int maxDepth = 0;

    vector<pair<int, int>> st;
    st.push_back({1, 0});
    while (!st.empty()) {
        int node = st.back().first;
        int& idx = st.back().second;
        if (idx == 0) {
            tin[node] = ++timer;
            if ((int)byDepth[depth[node]].size() == 0) {
                byDepth[depth[node]].reserve(4);
            }
            byDepth[depth[node]].push_back(tin[node]);
            maxDepth = max(maxDepth, depth[node]);
        }
        if (idx < (int)children[node].size()) {
            int child = children[node][idx++];
            depth[child] = depth[node] + 1;
            st.push_back({child, 0});
        } else {
            tout[node] = timer;
            st.pop_back();
        }
    }

    auto countAtDepth = [&](int node, int targetDepth) -> long long {
        if (targetDepth < 0 || targetDepth > maxDepth) {
            return 0;
        }
        const auto& bucket = byDepth[targetDepth];
        auto left = lower_bound(bucket.begin(), bucket.end(), tin[node]);
        auto right = upper_bound(bucket.begin(), bucket.end(), tout[node]);
        return right - left;
    };

    long long total = 0;
    long long bestCount = -1;
    int bestL = 0;

    int current = a;
    int childTowardA = 0;
    for (int l = 0; current != 0 && l <= k + 1; ++l) {
        int down = k + 1 - l;
        long long ways = 0;
        if (down == 0) {
            ways = 1;
        } else {
            int targetDepth = depth[current] + down;
            ways = countAtDepth(current, targetDepth);
            if (childTowardA != 0) {
                ways -= countAtDepth(childTowardA, targetDepth);
            }
        }
        total += ways;
        if (ways >= bestCount) {
            bestCount = ways;
            bestL = l;
        }
        childTowardA = current;
        current = parent[current];
    }

    cout << total << '\n' << bestL << '\n';
    return 0;
}
