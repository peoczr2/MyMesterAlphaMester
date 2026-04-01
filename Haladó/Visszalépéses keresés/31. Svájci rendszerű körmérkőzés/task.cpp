/*
Hungarian megoldás: a még nem találkozott csapatok között olyan tökéletes
párosítást keresünk, amelynél a pontkülönbségek összege minimális.

Hint 1: || A csapatok száma legfeljebb 16, ezért a bitmaskos DP belefér. ||
Hint 2: || A legkisebb szabad csapatot mindig érdemes először párosítani. ||
*/

#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<char>> volt;
vector<int> pont;
vector<long long> memo;
vector<int> par;

long long solve(int mask) {
    if (mask == (1 << n) - 1) return 0;
    long long &res = memo[mask];
    if (res != -1) return res;
    int i = 0;
    while (mask & (1 << i)) ++i;
    res = (1LL << 60);
    for (int j = i + 1; j < n; ++j) {
        if (mask & (1 << j)) continue;
        if (volt[i][j]) continue;
        long long cand = llabs(pont[i] - pont[j]) + solve(mask | (1 << i) | (1 << j));
        if (cand < res) {
            res = cand;
            par[mask] = j;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    volt.assign(n, vector<char>(n, 0));
    pont.assign(n, 0);
    for (int i = 0; i < n; ++i) {
        int s;
        cin >> s;
        for (int j = 0; j < s; ++j) {
            int x; cin >> x; --x;
            volt[i][x] = volt[x][i] = 1;
            ++pont[i];
        }
    }
    memo.assign(1 << n, -1);
    par.assign(1 << n, -1);
    long long best = solve(0);
    cout << best << '\n';
    int mask = 0;
    while (mask != (1 << n) - 1) {
        int i = 0;
        while (mask & (1 << i)) ++i;
        int j = par[mask];
        cout << i + 1 << ' ' << j + 1 << '\n';
        mask |= (1 << i) | (1 << j);
    }
    return 0;
}