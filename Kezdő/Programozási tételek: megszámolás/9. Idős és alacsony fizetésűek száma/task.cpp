/*
Megoldás lényege:
Egyetlen bejárással végigmegyünk a dolgozókon, és mindegyiknél megnézzük, hogy a kora nagyobb-e L-nél és a fizetése kisebb-e M-nél. Ha mindkét feltétel teljesül, növeljük a számlálót. A határok szigorúak: az L évesek nem számítanak az L év felettiek közé, és az M forintos fizetés sem kisebb M-nél. A futásidő O(N), a tárigény O(1), mert a dolgozókat nem kell eltárolni.
*/
/*
Hint 1: || Nem kell eltárolni a dolgozókat: minden sor beolvasása után azonnal el lehet dönteni, hogy beleszámít-e az eredménybe. ||
Hint 2: || A két feltétel: a kor szigorúan nagyobb L-nél, a fizetés szigorúan kisebb M-nél. Számoljuk azokat a dolgozókat, akikre mindkettő igaz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, l, m;
    cin >> n >> l >> m;
    int db = 0;
    for (int i = 0; i < n; i++) {
        int k, f;
        cin >> k >> f;
        if (k > l && f < m) {
            db++;
        }
    }
    cout << db << "\n";
    return 0;
}
