/*
Megoldás lényege:
Az egyes lakások alapterületét (T) egy halmazba (set) gyűjtjük, az árat a kérdés nem használja fel.
A halmazban minden alapterület csak egyszer szerepel, így a végén a halmaz mérete adja a különböző alapterületű lakások számát.
Az idő O(N log N), N ≤ 100 esetén ez bőven belefér a korlátokba.
*/
/*
Hint 1: || Az ár a kérdésre nincs hatással: csak az alapterületek különbözősége számít. ||
Hint 2: || Használj olyan adatszerkezetet, amely minden értéket csak egyszer tárol (pl. set), és a végén kérdezd le az elemszámát. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    set<int> teruletek;
    for (int i = 0; i < n; i++) {
        int terulet, ar;
        cin >> terulet >> ar;
        teruletek.insert(terulet);
    }
    cout << teruletek.size() << "\n";
    return 0;
}
