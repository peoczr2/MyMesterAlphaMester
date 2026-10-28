/*
Megoldás lényege:
Minden állomásra külön megnézzük, volt-e leszálló (le > 0) és volt-e felszálló (fel > 0).
Az állomás akkor felel meg, ha ez a két logikai érték különbözik, vagyis pontosan az egyik fajta utas volt: vagy csak leszállók, vagy csak felszállók.
Ha egyik sem volt (0 0), az állomás nem számít, mert ott sem le-, sem felszálló nem volt.
Egy bejárással megszámoljuk a megfelelő állomásokat, így az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Egy állomáson a leszállók és a felszállók közül pontosan az egyiknek kell pozitívnak lennie. ||
Hint 2: || Hasonlítsd össze a „volt leszálló” és a „volt felszálló” logikai értékeket: az állomás akkor jó, ha ezek különböznek. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int count = 0;  // azon állomások száma, ahol csak leszállók vagy csak felszállók voltak
    for (int i = 0; i < n; i++) {
        int le, fel;
        cin >> le >> fel;
        bool hasOff = le > 0;  // volt leszálló
        bool hasOn = fel > 0;  // volt felszálló
        if (hasOff != hasOn) count++;
    }

    cout << count << "\n";
    return 0;
}
