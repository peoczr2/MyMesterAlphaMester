/*
Megoldás lényege:
A napok halszámait sorban olvassuk be, és közben követjük az aktuális nap sorszámát (1-től kezdve).
Az első olyan napot jegyezzük meg, amelyen nulla hal volt, a későbbi nullás napok már nem írják felül az eredményt.
Ha nincs ilyen nap, a kimenet -1. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Nem kell rendezés vagy bonyolult adatszerkezet: csak azt kell eldönteni, melyik az első olyan nap, ahol a fogott halak száma 0. ||
Hint 2: || Olvasd be a napokat sorban, és az első nullás napnál tárold el a sorszámát; a kezdeti értéke -1 legyen, hogy ha nincs ilyen nap, az maradjon meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int ans = -1;
    for (int i = 1; i <= n; i++) {
        int fish;
        cin >> fish;
        if (fish == 0 && ans == -1) {
            ans = i;
        }
    }

    cout << ans << endl;
    return 0;
}
