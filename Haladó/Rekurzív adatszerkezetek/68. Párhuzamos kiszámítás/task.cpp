/*
Megoldási ötlet:
Egy levél kiszámítása 0 időt igényel, egy belső csúcs pedig akkor végezhető el, amikor mindkét gyereke elkészült.
Ezért minden csúcsra kiszámítható az a szint, amelyikben dolgozni fogunk: a levél 0, a belső csúcs pedig a gyerekei
közül a nagyobbik szintje + 1.

A teljes kifejezés minimális ideje a gyökér szintje. A szükséges minimális processzorszám pedig az egy időben végrehajtott
csúcsok közül a legtöbb, vagyis az azonos szintű belső csúcsok maximális száma.
*/
/*
Hint 1: || A gyerekek eredménye nélkül egy belső csúcsot nem lehet kiszámítani. ||
Hint 2: || A szintje minden csúcsnak a legmélyebb lefelé vezető út hossza. ||
Hint 3: || Ezután csak azt kell megszámolni, melyik szinten hány műveleti csúcs van. ||
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
    vector<int> ops(n + 1, 0);
    for (int node : order) {
        if (tree[node].leaf) {
            height[node] = 0;
            ops[node] = 0;
        } else {
            int left = tree[node].left;
            int right = tree[node].right;
            height[node] = max(height[left], height[right]) + 1;
            ops[node] = ops[left] + ops[right] + 1;
        }
    }

    if (tree[1].leaf) {
        cout << 0 << '\n' << 0 << '\n';
        return 0;
    }

    int time = height[1];
    int processors = (ops[1] + time - 1) / time;
    cout << time << '\n' << processors << '\n';
    return 0;
}
