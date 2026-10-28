/*
Megoldás lényege:
Az orgonasíp-elrendezés csak a sorozat alakját írja le, a párok száma szempontjából a számok értéke és az indexük számít.
Balról jobbra haladunk, és minden elemnél megnézzük, hány korábbi elem értéke egészíti ki K-ra az aktuális elemet (a K - aktuális érték),
ezt a darabszámot hozzáadjuk az eredményhez, majd az aktuális értéket beírjuk egy gyakorisági táblába (map).
Így minden {i, j} (i < j) pár pontosan egyszer kerül számlálásra. Az eredmény akár kb. 5·10^9 is lehet, ezért 64 bites egész kell.
Az időigény O(N log N), a memóriaigény O(N).
*/
/*
Hint 1: || Nem kell kihasználni a sorozat alakját: egy pár akkor jó, ha a két elem összege K, és az indexük különböző. Elég minden elemhez megszámolni, hány korábbi elem lehet a párja. ||
Hint 2: || Haladj balról jobbra, és tartsd nyilván egy gyakorisági táblázatban (például map), melyik értékből hányat láttál már. Az aktuális x elemhez a K - x értékű korábbi elemek száma adja a párok számát. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    cin >> n >> k;
    map<long long, long long> cnt;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        long long s;
        cin >> s;
        auto it = cnt.find(k - s);
        if (it != cnt.end()) ans += it->second;
        cnt[s]++;
    }
    cout << ans << "\n";
    return 0;
}
