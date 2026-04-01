/*
Megoldás lényege:
N legfeljebb 16, ezért bitmaskos visszalépéses keresés elég. Egy állapot azt
mutatja meg, mely csapatok maradtak még párosítatlanul. A legkisebb sorszámú
szabad csapatot megpróbáljuk párosítani minden olyan másik szabad csapattal,
amellyel még nem játszott.
*/

#include <bits/stdc++.h>
using namespace std;

int n, m;
int fullMask;
int pairedWith[1 << 16];
char can[1 << 16];
bitset<17> forbidden[17];

bool solve(int mask) {
    if (mask == 0) return true;
    char& memo = can[mask];
    if (memo != -1) return memo;

    int i = __builtin_ctz(mask) + 1;
    int rest = mask ^ (1 << (i - 1));
    for (int j = i + 1; j <= n; ++j) {
        if (!(rest & (1 << (j - 1)))) continue;
        if (forbidden[i][j]) continue;
        if (solve(rest ^ (1 << (j - 1)))) {
            pairedWith[mask] = (i << 8) | j;
            return memo = 1;
        }
    }
    return memo = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    fullMask = (1 << n) - 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < m; ++j) {
            int x;
            cin >> x;
            forbidden[i][x] = 1;
            forbidden[x][i] = 1;
        }
    }

    memset(can, -1, sizeof(can));
    solve(fullMask);

    int mask = fullMask;
    while (mask) {
        int pairInfo = pairedWith[mask];
        int a = pairInfo >> 8;
        int b = pairInfo & 255;
        cout << a << ' ' << b << '\n';
        mask ^= 1 << (a - 1);
        mask ^= 1 << (b - 1);
    }
    return 0;
}
