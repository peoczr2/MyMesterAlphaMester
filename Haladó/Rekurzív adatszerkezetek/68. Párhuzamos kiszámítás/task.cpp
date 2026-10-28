/*
Megoldási ötlet:
Egy levél kiszámítása 0 időt igényel, egy belső csúcs pedig akkor végezhető el, amikor mindkét gyereke elkészült.
A minimális idő a gyökér magassága, vagyis a legmélyebb levélig vezető műveletsor hossza.

A gyökértől d szinten lévő művelet legkésőbb a T - d időegységre készülhet el (T a minimális idő). Ha t időegység alatt
legfeljebb t * P művelet fér el, ezért P legalább ceil(darab / t) kell legyen, ahol a darab azon műveletek száma,
amelyeknek határideje legfeljebb t. A legnagyobb ilyen korlát a szükséges processzorszám, és a határidő szerinti
ütemezéssel ez el is érhető.
*/
/*
Hint 1: || A gyerekek eredménye nélkül egy belső csúcsot nem lehet kiszámítani. ||
Hint 2: || A szintje minden csúcsnak a legmélyebb lefelé vezető út hossza. ||
Hint 3: || A gyökértől mért mélység adja a határidőt: a d mélységű művelet legkésőbb T - d időpontra készülhet el, és ezeket a határidőket érdemes szűrni t szerint. ||
*/

#include <algorithm>
#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    int left = 0;
    int right = 0;
    bool leaf = false;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string line;
    getline(cin, line);

    vector<Node> tree(n + 1);
    for (int i = 1; i <= n; ++i) {
        getline(cin, line);
        while (line.empty()) getline(cin, line);
        if (line[0] == '+' || line[0] == '-' || line[0] == '*' || line[0] == '/') {
            tree[i].leaf = false;
            char op;
            int l, r;
            stringstream ss(line);
            ss >> op >> l >> r;
            tree[i].left = l;
            tree[i].right = r;
        } else {
            tree[i].leaf = true;
        }
    }

    vector<int> order;
    order.reserve(n);
    vector<pair<int, bool>> st = {{1, false}};
    while (!st.empty()) {
        auto [node, visited] = st.back();
        st.pop_back();
        if (visited) {
            order.push_back(node);
        } else {
            st.push_back({node, true});
            if (!tree[node].leaf) {
                st.push_back({tree[node].right, false});
                st.push_back({tree[node].left, false});
            }
        }
    }

    vector<int> height(n + 1, 0);
    for (int node : order) {
        if (!tree[node].leaf) {
            int left = tree[node].left;
            int right = tree[node].right;
            height[node] = max(height[left], height[right]) + 1;
        }
    }

    if (tree[1].leaf) {
        cout << 0 << '\n' << 0 << '\n';
        return 0;
    }

    vector<int> depth(n + 1, 0);
    for (auto it = order.rbegin(); it != order.rend(); ++it) {
        int node = *it;
        if (!tree[node].leaf) {
            depth[tree[node].left] = depth[node] + 1;
            depth[tree[node].right] = depth[node] + 1;
        }
    }

    int time = height[1];
    // suffix[k]: a gyökértől legalább k mélységben lévő műveletek száma
    vector<int> suffix(time + 2, 0);
    for (int node = 1; node <= n; ++node) {
        if (!tree[node].leaf) ++suffix[depth[node]];
    }
    for (int k = time; k >= 0; --k) suffix[k] += suffix[k + 1];

    int processors = 0;
    for (int t = 1; t <= time; ++t) {
        processors = max(processors, (suffix[time - t] + t - 1) / t);
    }
    cout << time << '\n' << processors << '\n';
    return 0;
}
