/*
Hungarian megoldás: a még nem találkozott csapatok között kell tökéletes
párosítást találni.

Hint 1: || Az N legfeljebb 16, ezért bitmaskos visszalépés bőven elég. ||
Hint 2: || Mindig a legkisebb szabad csapatot érdemes először párosítani. ||
*/

#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<char>> volt;
vector<pair<int,int>> valasz;

bool dfs(int mask) {
    if (mask == (1 << n) - 1) return true;
    int i = 0;
    while (mask & (1 << i)) ++i;
    for (int j = i + 1; j < n; ++j) {
        if (mask & (1 << j)) continue;
        if (volt[i][j]) continue;
        valasz.push_back({i + 1, j + 1});
        if (dfs(mask | (1 << i) | (1 << j))) return true;
        valasz.pop_back();
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    volt.assign(n, vector<char>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int x; cin >> x; --x;
            volt[i][x] = volt[x][i] = 1;
        }
    }
    dfs(0);
    for (auto [a, b] : valasz) cout << a << ' ' << b << '\n';
    return 0;
}