/*
Megoldás:
Egy rögzített felső és alsó sor között a kiválasztott téglalap sűrűsége már csak attól függ, melyik
oszlopintervallumot választjuk. A magasság rögzítése után minden oszlophoz tudjuk, hány fa esik az
adott sávba. Innen minden bal-jobb oszloppárra azonnal kiszámítható a fák száma és a terület.

Az összes lehetséges sorpárt végignézzük, folyamatosan karbantartva az oszlopösszegeket. Minden
ilyen sávra kipróbáljuk az összes olyan oszlopintervallumot, amelynek területe legalább T, és
egész törtként hasonlítjuk össze a sűrűségeket, így nincs lebegőpontos pontatlanság.

Az algoritmus O(N^2 * M^2), ami a 150-es korlát mellett belefér.
*/
/*
Hint 1: || Először rögzítsd a téglalap magasságát egy felső-alsó sorpárral. ||
Hint 2: || Ekkor minden oszlophoz egyetlen szám tartozik: hány fa esik bele ebbe a vízszintes sávba. ||
Hint 3: || A sűrűségeket ne lebegőponttal, hanem keresztszorzással hasonlítsd össze. ||
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, f, t;
    cin >> n >> m >> f >> t;

    vector<vector<int>> grid(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i < f; ++i) {
        int row, col;
        cin >> row >> col;
        grid[row][col] = 1;
    }

    long long bestTrees = -1;
    long long bestArea = 1;
    int bestR1 = 1;
    int bestC1 = 1;
    int bestR2 = 1;
    int bestC2 = t;

    vector<int> columnSum(m + 1);
    vector<int> prefix(m + 1);

    for (int top = 1; top <= n; ++top) {
        fill(columnSum.begin(), columnSum.end(), 0);
        for (int bottom = top; bottom <= n; ++bottom) {
            int height = bottom - top + 1;
            for (int col = 1; col <= m; ++col) {
                columnSum[col] += grid[bottom][col];
                prefix[col] = prefix[col - 1] + columnSum[col];
            }

            int minWidth = (t + height - 1) / height;
            if (minWidth > m) {
                continue;
            }

            for (int left = 1; left <= m; ++left) {
                int startRight = left + minWidth - 1;
                if (startRight > m) {
                    break;
                }
                for (int right = startRight; right <= m; ++right) {
                    long long trees = prefix[right] - prefix[left - 1];
                    long long area = 1LL * height * (right - left + 1);
                    if (bestTrees == -1 || trees * bestArea > bestTrees * area) {
                        bestTrees = trees;
                        bestArea = area;
                        bestR1 = top;
                        bestC1 = left;
                        bestR2 = bottom;
                        bestC2 = right;
                    }
                }
            }
        }
    }

    cout << bestR1 << ' ' << bestC1 << ' ' << bestR2 << ' ' << bestC2 << '\n';
    return 0;
}