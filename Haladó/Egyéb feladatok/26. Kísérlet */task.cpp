/*
Megoldás:
Válasszunk ki K sejtet úgy, hogy a hozzájuk tartozó legkisebb közös megfigyelő intervallum a
lehető legrövidebb legyen. Ha a kiválasztott sejtek közül a legnagyobb keletkezési idő B, illetve
a legkisebb pusztulási idő P, akkor a legrövidebb jó intervallum hossza max(0, B-P), és pozitív
esetben maga [P,B], különben [B,B].

Ezért a sejteket keletkezési idő szerint rendezzük. Balról jobbra haladva mindig az eddig látott
sejtek közül tartjuk meg a K legnagyobb pusztulási időt. Ha az aktuális B mellett ezek közül a
legkisebb P ismert, akkor ez adja a legjobb olyan K elemű választást, amelynek a maximális
keletkezési ideje éppen B.

Az algoritmus O(N log K) idejű, mert egy K méretű kupacot használunk.
*/
/*
Hint 1: || Egy kiválasztott K elemű csoportnál csak a legnagyobb keletkezési idő és a legkisebb pusztulási idő számít. ||
Hint 2: || Ha az aktuális elem lesz a legnagyobb keletkezési idő, akkor mellé az eddigiek közül a lehető legnagyobb pusztulási idejű K-1 elem kell. ||
Hint 3: || Ezt egy K méretű minimumkupaccal lehet karbantartani. ||
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Cell {
    int birth;
    int death;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, m, n;
    cin >> k >> m >> n;

    vector<Cell> cells(n);
    for (int i = 0; i < n; ++i) {
        cin >> cells[i].birth >> cells[i].death;
    }

    sort(cells.begin(), cells.end(), [](const Cell &left, const Cell &right) {
        if (left.birth != right.birth) {
            return left.birth < right.birth;
        }
        return left.death > right.death;
    });

    priority_queue<int, vector<int>, greater<int>> bestDeaths;
    long long bestLength = (1LL << 60);
    int bestA = -1;
    int bestB = -1;

    for (const Cell &cell : cells) {
        bestDeaths.push(cell.death);
        if (static_cast<int>(bestDeaths.size()) > k) {
            bestDeaths.pop();
        }
        if (static_cast<int>(bestDeaths.size()) < k) {
            continue;
        }

        int thresholdDeath = bestDeaths.top();
        int currentA = min(cell.birth, thresholdDeath);
        int currentB = cell.birth;
        long long currentLength = currentB - currentA;

        if (currentLength < bestLength || (currentLength == bestLength && currentA < bestA)) {
            bestLength = currentLength;
            bestA = currentA;
            bestB = currentB;
        }
    }

    cout << bestA << ' ' << bestB << '\n';
    return 0;
}