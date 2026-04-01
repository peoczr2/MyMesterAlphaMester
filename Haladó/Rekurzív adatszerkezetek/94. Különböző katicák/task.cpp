/*
Megoldási ötlet:
Az élek mentén a pöttyök száma mindig pontosan 1-gyel változik, tehát a fa két szomszédos szintjén a paritás
automatikusan váltakozik. Ezért egy rögzített gyökérparitás mellett minden csúcs lehetséges értéke egy azonos paritású
intervallum.

Alulról felfelé számoljuk ki minden csúcsra azt az intervallumot, amelyben az értéke még összeegyeztethető a részfával.
Egy gyermek intervalluma a szülőnél ±1-gyel tolódik, majd a szülő saját korlátaival metsződik. Ha a gyökérnél van nem
üres intervallum, akkor egy tetszőleges értékkel vissza is tudjuk építeni a teljes kiosztást.
*/
/*
Hint 1: || Minden él mentén a pöttyök száma pontosan 1-gyel változik, tehát a paritás váltakozik. ||
Hint 2: || Egy csúcs lehetséges értékei egy rögzített gyökérparitás mellett intervallumot alkotnak. ||
Hint 3: || Először alulról fölfelé szűkítsd az intervallumokat, utána felülről lefelé válassz konkrét értékeket. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

static const int INF = 200000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> parent(n + 1, 0);
    vector<vector<int>> children(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> parent[i];
        if (i >= 2) children[parent[i]].push_back(i);
    }
    vector<int> fixed(n + 1, -1);
    for (int i = 1; i <= n; ++i) cin >> fixed[i];

    vector<int> depth(n + 1, 0), order;
    order.reserve(n);
    vector<int> stack = {1};
    while (!stack.empty()) {
        int node = stack.back();
        stack.pop_back();
        order.push_back(node);
        for (int child : children[node]) {
            depth[child] = depth[node] + 1;
            stack.push_back(child);
        }
    }

    auto solve = [&](int rootParity, vector<int>& answer) -> bool {
        vector<int> lo(n + 1), hi(n + 1);
        vector<char> ok(n + 1, 1);
        for (int idx = n - 1; idx >= 0; --idx) {
            int node = order[idx];
            int nodeParity = rootParity ^ (depth[node] & 1);
            if (fixed[node] != -1) {
                if ((fixed[node] & 1) != nodeParity) return false;
                lo[node] = hi[node] = fixed[node];
            } else {
                lo[node] = nodeParity;
                hi[node] = INF - ((INF - nodeParity) & 1);
            }
            for (int child : children[node]) {
                int childLo = max(0, lo[child] - 1);
                int childHi = min(INF, hi[child] + 1);
                lo[node] = max(lo[node], childLo);
                hi[node] = min(hi[node], childHi);
            }
            if (lo[node] > hi[node]) return false;
            if ((lo[node] & 1) != nodeParity) ++lo[node];
            if ((hi[node] & 1) != nodeParity) --hi[node];
            if (lo[node] > hi[node]) return false;
        }

        answer.assign(n + 1, -1);
        answer[1] = lo[1];
        vector<int> st = {1};
        while (!st.empty()) {
            int node = st.back();
            st.pop_back();
            for (int child : children[node]) {
                int want1 = answer[node] - 1;
                int want2 = answer[node] + 1;
                if (want1 >= lo[child] && want1 <= hi[child]) answer[child] = want1;
                else answer[child] = want2;
                st.push_back(child);
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (answer[i] < 0 || answer[i] > INF) return false;
            if (fixed[i] != -1 && answer[i] != fixed[i]) return false;
            if (parent[i] != 0 && abs(answer[i] - answer[parent[i]]) != 1) return false;
        }
        return true;
    };

    vector<int> answer;
    if (solve(0, answer) || solve(1, answer)) {
        cout << "IGEN\n";
        for (int i = 1; i <= n; ++i) {
            if (i > 1) cout << ' ';
            cout << answer[i];
        }
        cout << '\n';
    } else {
        cout << "NEM\n";
    }
    return 0;
}
