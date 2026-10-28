/*
Megoldás lényege:
Két egymásba ágyazott ciklussal minden i < j sorszámpárt megvizsgálunk, és az első olyan párt keressük, amelynek születési éve megegyezik. A külső ciklus adja az első, a belső a második sorszámot, így az első találat automatikusan a legkisebb első sorszámú pár, és ehhez a legkisebb második sorszám tartozik. Ha nincs egyezés, a "0 0" kerül a kimenetre. Mivel N ≤ 100, az O(N²) időigény 0.1 másodperc alatt bőven belefér.
*/
/*
Hint 1: || Nem kell rendezni vagy bonyolult adatszerkezet: elég a két ember évszámát összehasonlítani, de minden párt csak egyszer vizsgálj meg. ||
Hint 2: || Ha a belső ciklus az első sorszám utánról indul, a kiírt sorszámok automatikusan növekvő sorrendben lesznek, és az első találat a helyes válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> year(n);
    for (int i = 0; i < n; i++) {
        cin >> year[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (year[i] == year[j]) {
                cout << i + 1 << " " << j + 1 << "\n";
                return 0;
            }
        }
    }
    cout << "0 0\n";
    return 0;
}
