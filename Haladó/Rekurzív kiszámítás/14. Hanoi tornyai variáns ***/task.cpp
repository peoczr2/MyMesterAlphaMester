/*
Megoldás lényege:
Rekurzívan a legnagyobb eltérő korongot mozgatjuk. Először a kisebb korongokat egy közös
segédtoronyra rendezzük, majd áthelyezzük a nagy korongot, végül a kisebbeket a célállásba
rakjuk vissza.

*/

// Hint 1: || A legnagyobb korong pozíciója dönti el, kell-e egyáltalán mozgatni őt. ||
// Hint 2: || A kisebb korongok először egy közös segédtoronyra kerülnek, csak utána jöhet a nagy korong. ||
// Hint 3: || Minden lépést azonnal kiírhatsz, miközben a belső állapotot frissíted. ||

#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> curPeg, goalPeg;
vector<pair<int, int>> moves;

void moveDisk(int d, int from, int to) {
    moves.push_back({from, to});
    curPeg[d] = to;
}

void solve(int k) {
    if (k == 0) return;
    if (curPeg[k] == goalPeg[k]) {
        solve(k - 1);
        return;
    }

    int s = curPeg[k];
    int t = goalPeg[k];
    int u = 6 - s - t;

    vector<int> savedGoal(k, 0);
    for (int i = 1; i < k; ++i) savedGoal[i] = u;
    vector<int> oldGoal = goalPeg;
    for (int i = 1; i < k; ++i) goalPeg[i] = u;
    solve(k - 1);

    moveDisk(k, s, t);

    for (int i = 1; i < k; ++i) goalPeg[i] = oldGoal[i];
    solve(k - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<int>> initial(3), target(3);
    int x;
    for (int peg = 0; peg < 3; ++peg) {
        while (cin >> x && x != 0) initial[peg].push_back(x);
    }
    for (int peg = 0; peg < 3; ++peg) {
        while (cin >> x && x != 0) target[peg].push_back(x);
    }

    N = 0;
    for (const auto& v : initial) for (int d : v) N = max(N, d);
    for (const auto& v : target) for (int d : v) N = max(N, d);

    curPeg.assign(N + 1, 0);
    goalPeg.assign(N + 1, 0);
    for (int peg = 0; peg < 3; ++peg) {
        for (int d : initial[peg]) curPeg[d] = peg + 1;
        for (int d : target[peg]) goalPeg[d] = peg + 1;
    }

    solve(N);

    cout << moves.size() << '\n';
    for (auto [a, b] : moves) cout << a << ' ' << b << '\n';
    return 0;
}
