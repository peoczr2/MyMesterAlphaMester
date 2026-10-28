/*
Megoldás lényege:
Minden település sorát egyszer olvassuk be: a Kukutyintól mért K és a Piripócstól mért P távolságot hasonlítjuk össze.
Ha K < P, a település közelebb van Kukutyinhoz, ezért egy számlálót növelünk. Egyenlő távolságnál nem számolunk, mert a feladat szigorúan „közelebb”-t kér.
A távolságokat nem kell eltárolni, így a memóriaigény állandó, az időigény O(N), ami N ≤ 100 mellett bőven belefér a limitbe.
*/
/*
Hint 1: || Nem kell a távolságokat tömbben tárolni: minden sor beolvasása után azonnal döntsd el, melyik település van közelebb Kukutyinhoz. ||
Hint 2: || Használj egy számlálót, amely kezdetben 0. Növeld, ha a Kukutyintól mért távolság kisebb a Piripócstól mértnél. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int db = 0;
    for (int i = 0; i < n; i++) {
        int k, p;
        cin >> k >> p;
        if (k < p) {
            db++;
        }
    }
    cout << db << endl;
    return 0;
}
