/*
Megoldás lényege:
A húzásokat sorban olvassuk, és nyilvántartjuk, hogy az aktuális sorozatban mely lottószámok szerepeltek már, valamint hány különbözőt láttunk.
Ha ez a szám eléri a 90-et, egy teljes sorozatot találtunk: a sorozat a legkorábban lezáruló szakasz, ezért a következő sorozat már a következő húzással kezdődik.
Ekkor a jelöléseket és a számlálót nullázzuk, így a sorozatok száma maximális lesz, és nem fedik egymást.
Időigény O(N), mert minden húzást egyszer dolgozunk fel.
*/
/*
Hint 1: || Haladj a húzásokon balról jobbra, és közben számold, hány különböző lottószám szerepelt már az aktuális sorozatban. ||
Hint 2: || Egy 1–90 közötti jelölőtömb elég: amikor egy sorozat teljesül, nullázd a tömböt és a számlálót, és a következő húzással kezdd újra. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    const int TOTAL = 90;
    int n;
    cin >> n;

    vector<int> seen(TOTAL + 1, 0);
    int distinct = 0;
    int sequences = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            int x;
            cin >> x;
            if (!seen[x]) {
                seen[x] = 1;
                distinct++;
            }
        }
        if (distinct == TOTAL) {
            sequences++;
            fill(seen.begin(), seen.end(), 0);
            distinct = 0;
        }
    }

    cout << sequences << "\n";
    return 0;
}
