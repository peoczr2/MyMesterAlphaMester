/*
Megoldás lényege:
Egy törzs akkor békés, ha egyik háborúban sem szerepel, sem háborúzóként, sem ellenségként. Feljegyezzük az összes háborúban részt vevő törzset egy halmazba, majd sorszám szerint növekvően végignézve az 1-től N-ig tartó sorszámokon megkeressük az első olyan törzset, amely nincs a halmazban. Ha minden törzs szerepel valamelyik háborúban, a válasz 0. Az időigény O(K log K + N).
*/
/*
Hint 1: || Elég azt megnézni, mely törzsek szerepelnek valamelyik háborúban; a többi törzs békés. ||
Hint 2: || A legkisebb sorszámú békés törzset kell kiírni, ezért 1-től N-ig növekvően haladva az első olyan szám a jó, amelyet nem jegyeztél fel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    set<int> reszt; // a háborúkban szereplő törzsek
    for (int i = 0; i < k; i++) {
        int a, b, kezd, veg;
        cin >> a >> b >> kezd >> veg;
        reszt.insert(a);
        reszt.insert(b);
    }
    for (int t = 1; t <= n; t++) {
        if (!reszt.count(t)) {
            cout << t << "\n";
            return 0;
        }
    }
    cout << 0 << "\n";
    return 0;
}
