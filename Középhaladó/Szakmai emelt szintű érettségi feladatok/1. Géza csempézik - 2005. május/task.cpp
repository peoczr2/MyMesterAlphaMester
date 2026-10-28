/*
Megoldás lényege:
A mester a felület 20%-kal nagyobb területét burkolja, vagyis a szükséges terület 1,2 · W · H. Mivel W · H 20%-a egész, a szorzat osztható 5-tel, így a szükséges terület egész számként is kiszámolható: 6 · (W · H / 5). A lapok számát úgy kapjuk, hogy ezt elosztjuk egy lap területével (bw · bh), és a hányadost felfelé kerekítjük, mert részlap nincs. A felfelé kerekítés egész osztással történik: (a + b - 1) / b. Az időigény konstans.
*/
/*
Hint 1: || A 20%-kal nagyobb felület kiszámolásához ne tört szorzót használj: a W · H szorzat 5-tel osztható, így az 1,2-szeres terület egész számokkal is pontosan megkapható. ||
Hint 2: || A lapok száma a szükséges terület és egy lap területének hányadosa, felfelé kerekítve. Egész számokkal a felfelé kerekítés: (a + b - 1) / b. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long w, h, bw, bh;
    cin >> w >> h >> bw >> bh;
    long long kell = w * h / 5 * 6;
    long long lap = bw * bh;
    cout << (kell + lap - 1) / lap << endl;
    return 0;
}
