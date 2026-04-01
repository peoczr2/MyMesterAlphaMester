/*
Megoldas lenyege:
A vegso sorrendben az 1-esek, majd a 2-esek, majd a 3-asok allnak. Minden
rossz helyen alló kontener egy iranyitott elemet ad: a jelenlegi erteke a
forrascsucs, a cel blokk szama a vegcsucs. Ezek a rossz kontenerek egy
kiegyensulyozott, 3 csucsú irányitott multigráfot alkotnak, amelyben van
Euler-korut. A korut edge-sorrendje pontosan megadja, milyen sorrendben kell a
kontenereket a szabad helyre mozgatni, es a végén egy utolso lepes visszateszi a
lyukat az N+1. helyre.
*/
/*
Hint 1: || Minden rossz helyen alló kontenerhez rendelj egy iranyitott éllel a jelenlegi szama és a cel blokk száma között. ||
Hint 2: || A helyes sorrend egy Euler-korut ezekbol az elekből: a következő kontener mindig annak a szamnak a blokkjaba kell, amelyik az elozo hely celja volt. ||
Hint 3: || Ha a korut eleje es vege is illeszkedik, akkor a lepesek szama a rossz konténerek száma plusz egy, mert a legutolso mozdulattal kell visszatenni az ures helyet a sor vegere. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int pos;
};

static void dfs(int v, vector<vector<Edge>>& adj, vector<int>& order) {
    while (!adj[v].empty()) {
        Edge e = adj[v].back();
        adj[v].pop_back();
        dfs(e.to, adj, order);
        order.push_back(e.pos);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n + 1);
    int cnt[4] = {0, 0, 0, 0};
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        ++cnt[a[i]];
    }

    int c1 = cnt[1];
    int c2 = cnt[2];
    int c3 = cnt[3];
    (void)c3;

    auto target = [&](int i) {
        if (i <= c1) return 1;
        if (i <= c1 + c2) return 2;
        return 3;
    };

    vector<vector<Edge>> adj(4);
    int wrong = 0;
    for (int i = 1; i <= n; ++i) {
        int need = target(i);
        if (a[i] != need) {
            ++wrong;
            adj[a[i]].push_back({need, i});
        }
    }

    if (wrong == 0) {
        cout << 0 << '\n';
        return 0;
    }

    int start = 1;
    while (start <= 3 && adj[start].empty()) ++start;
    vector<int> order;
    dfs(start, adj, order);
    reverse(order.begin(), order.end());

    cout << wrong + 1 << '\n';
    cout << order.front() << ' ' << n + 1 << '\n';
    for (int i = 1; i < (int)order.size(); ++i) {
        cout << order[i] << ' ' << order[i - 1] << '\n';
    }
    cout << n + 1 << ' ' << order.back() << '\n';
    return 0;
}
