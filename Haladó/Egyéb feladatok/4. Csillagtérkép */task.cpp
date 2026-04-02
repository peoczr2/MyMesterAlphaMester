/*
Egy teglalap akkor jo, ha a kijelolt x-es y-os koordinatatartomanyban egyetlen csillagpont sincs.
M <= 200, ezert vegig tudjuk probalni a teglalap also es felso y-koordinatajat. Egy ilyen savban
megjegyezzuk, mely oszlopok rosszak, vagyis melyikben van legalabb egy csillag. A savon belul a
legnagyobb ures teglalap pontosan a leghosszabb egymas utani jo oszlopszakasz.

Az algoritmus tehat O(M^3): minden also y-hoz egyre noveljuk a felso y-t, frissitjuk az oszlopok
allapotat, majd linearis bejarassal megkeressuk a leghosszabb jo oszlopszakaszt.
*/
/*
Hint 1: || Rögzítsd a téglalap alsó és felső sorát, és csak az oszlopok mentén kell majd dönteni. ||
Hint 2: || Egy oszlop akkor használható az adott sávban, ha ebben a sorintervallumban nincs benne csillag. ||
Hint 3: || Az adott sáv legjobb téglalapja a leghosszabb összefüggő használható oszlopszakasz lesz. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> hasStar(m + 1, vector<int>(m + 1, 0));
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        hasStar[y][x] = 1;
    }

    int bestArea = 0;
    int bestX1 = 1, bestY1 = 1, bestX2 = 1, bestY2 = 1;

    for (int y1 = 1; y1 <= m; ++y1) {
        vector<int> badColumn(m + 1, 0);
        for (int y2 = y1; y2 <= m; ++y2) {
            for (int x = 1; x <= m; ++x) {
                badColumn[x] += hasStar[y2][x];
            }

            int currentStart = -1;
            for (int x = 1; x <= m + 1; ++x) {
                bool freeColumn = (x <= m && badColumn[x] == 0);
                if (freeColumn) {
                    if (currentStart == -1) currentStart = x;
                } else if (currentStart != -1) {
                    int x1 = currentStart;
                    int x2 = x - 1;
                    int area = (x2 - x1 + 1) * (y2 - y1 + 1);
                    if (area > bestArea) {
                        bestArea = area;
                        bestX1 = x1;
                        bestY1 = y1;
                        bestX2 = x2;
                        bestY2 = y2;
                    }
                    currentStart = -1;
                }
            }
        }
    }

    cout << bestArea << '\n';
    cout << bestX1 << ' ' << bestY1 << ' ' << bestX2 << ' ' << bestY2 << '\n';
    return 0;
}