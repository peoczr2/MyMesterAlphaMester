/*
Megoldás lényege:
A feladat csak a felvett pénz összegét kérdezi, az események időpontjára nincs szükség. Az N eseményt egy ciklusban olvassuk be. Ha az esemény jellege -2 (pénzfelvétel), akkor a negyedik szám, vagyis a felvett összeg hozzáadódik az eredményhez. A belépés, a kilépés és a pénzbetét eseményei nem változtatják az összeget. Az összeg legfeljebb 100 · 10 000 000 = 10^9 lehet, ezért a biztonság kedvéért long long típust használunk. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Az időpontok és a belépés-kilépés események a kérdéshez nem kellenek: minden eseményt külön kell megvizsgálni, és csak a pénzfelvételeket kell figyelembe venni. ||
Hint 2: || Az esemény jellegét a harmadik szám adja: a -2 jelenti a pénzfelvételt. Ilyenkor a negyedik szám az összeg, amit egy összegző változóhoz kell adni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long total = 0;
    for (int i = 0; i < n; i++) {
        int hour, minute, type;
        long long value;
        cin >> hour >> minute >> type >> value;
        if (type == -2) {
            total += value;
        }
    }

    cout << total << "\n";
    return 0;
}
