/*
Megoldás:
Mivel a téglalap területe pontosan T, a lehetséges méretei csak a T osztópárjai lehetnek.
Minden olyan (magasság, szélesség) párra, amelynek szorzata T és belefér az N x N táblába,
végignézzük az összes elhelyezést, és 2D prefixösszeggel O(1) idő alatt kiszámítjuk az adott
téglalap hasznát.

Az osztópárok száma kicsi, ezért ez a teljes keresés elég gyors. Az algoritmus O(D * N^2),
ahol D a T osztóinak száma.
*/
/*
Hint 1: || Pontos terület esetén csak a T osztópárjai jöhetnek szóba téglalap-méretként. ||
Hint 2: || Egy adott méret összes elhelyezését prefixösszeggel nagyon gyorsan lehet értékelni. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

long long rectangleSum(const vector<vector<long long>> &prefix, int r1, int c1, int r2, int c2) {
    return prefix[r2][c2] - prefix[r1 - 1][c2] - prefix[r2][c1 - 1] + prefix[r1 - 1][c1 - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, t;
    cin >> n >> t;

    vector<vector<long long>> prefix(n + 1, vector<long long>(n + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            long long value;
            cin >> value;
            prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + value;
        }
    }

    long long bestValue = -(1LL << 60);
    int bestR1 = 1;
    int bestC1 = 1;
    int bestR2 = 1;
    int bestC2 = t;

    vector<pair<int, int>> shapes;
    for (int h = 1; 1LL * h * h <= t; ++h) {
        if (t % h != 0) {
            continue;
        }
        int w = t / h;
        shapes.push_back({h, w});
        if (h != w) {
            shapes.push_back({w, h});
        }
    }

    for (const auto &[height, width] : shapes) {
        if (height > n || width > n) {
            continue;
        }
        for (int r1 = 1; r1 + height - 1 <= n; ++r1) {
            int r2 = r1 + height - 1;
            for (int c1 = 1; c1 + width - 1 <= n; ++c1) {
                int c2 = c1 + width - 1;
                long long value = rectangleSum(prefix, r1, c1, r2, c2);
                if (value > bestValue) {
                    bestValue = value;
                    bestR1 = r1;
                    bestC1 = c1;
                    bestR2 = r2;
                    bestC2 = c2;
                }
            }
        }
    }

    cout << bestValue << '\n';
    cout << bestR1 << ' ' << bestC1 << ' ' << bestR2 << ' ' << bestC2 << '\n';
    return 0;
}