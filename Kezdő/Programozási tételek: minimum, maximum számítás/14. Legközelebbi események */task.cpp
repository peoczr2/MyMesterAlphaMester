/*
Megoldás lényege:
Az események évei szigorúan monoton sorrendben érkeznek (lehet növekvő vagy csökkenő), ezért a legkisebb időkülönbség mindig két egymás utáni esemény között adódik. Beolvasás közben csak az előző év értékét tartjuk meg, és minden új eseménynél kiszámoljuk a távolságot az előzőtől. A szigorú összehasonlítás miatt egyenlő távolságnál az elsőként beolvasott pár marad. A kategóriákat és az évintervallumot a kérdés nem használja, ezeket nem dolgozzuk fel. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Az évek monoton sorrendben vannak, így a legkisebb távolságot egymás utáni események között kell keresni. ||
Hint 2: || Egyetlen menetben haladj végig az eseményeken, és csak az előző év értékét tartsd meg. A szöveges leírás szóközt tartalmazhat, ezért azt getline-nal olvasd be és dobd el. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, ksz;
    cin >> n >> ksz;

    string line;
    getline(cin, line);

    int prevYear = 0;
    int bestGap = INT_MAX;
    int bestLo = 0;
    int bestHi = 0;

    for (int i = 0; i < n; i++) {
        int year, category;
        cin >> year >> category;
        getline(cin, line);
        getline(cin, line);

        if (i > 0) {
            int gap = abs(year - prevYear);
            if (gap < bestGap) {
                bestGap = gap;
                bestLo = min(year, prevYear);
                bestHi = max(year, prevYear);
            }
        }
        prevYear = year;
    }

    cout << bestGap << " " << bestLo << " " << bestHi << "\n";

    return 0;
}
