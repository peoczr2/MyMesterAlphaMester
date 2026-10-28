/*
Megoldás lényege:
Egy állomáson nőtt a vonaton utazók száma, ha több ember szállt fel, mint ahányan leszálltak, vagyis a felszállók száma nagyobb a leszállókénál. Minden állomást egyszer beolvasunk, megvizsgáljuk ezt a feltételt, és a teljesülő állomásokat számoljuk. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Az állomáson nőtt az utazók száma, ha többen szálltak fel, mint ahányan leszálltak. ||
Hint 2: || Minden állomásnál hasonlítsd össze közvetlenül a felszállók és a leszállók számát, és számold azokat az állomásokat, ahol a felszállók száma a nagyobb. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int count = 0;
    for (int i = 0; i < n; i++) {
        int le, fel;
        cin >> le >> fel;
        if (fel > le) count++;
    }

    cout << count << "\n";
    return 0;
}
