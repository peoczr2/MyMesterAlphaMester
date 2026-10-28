/*
Megoldás lényege:
Minden állomáshoz csak a leszállók és a felszállók száma tartozik, a vonat menetét nem kell szimulálni. Egy állomáson akkor szálltak le többen, mint fel, ha le > fel.
Egy bejárásban minden állomást ezzel a feltétellel vizsgálunk, és a teljesítő állomások számát növeljük. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Minden állomásra két szám van: a leszállók és a felszállók száma. Ezeket kell egymással összehasonlítani. ||
Hint 2: || Egy bejárásban olvasd be az állomásokat, és számold meg azokat, ahol a leszállók száma nagyobb a felszállókénál. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        long long le, fel;
        cin >> le >> fel;
        if (le > fel) cnt++;
    }

    cout << cnt << "\n";
    return 0;
}
