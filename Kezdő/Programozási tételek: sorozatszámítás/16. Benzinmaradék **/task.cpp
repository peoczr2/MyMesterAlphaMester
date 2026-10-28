/*
Megoldás lényege:
Az út végén az autóban levő benzin a kezdeti mennyiség, plusz az összes tankolt mennyiség, mínusz az út teljes fogyasztása. A tankolások helye és sorrendje nem befolyásolja a végeredményt, csak az összmennyiség számít, ezért elég a tankolt mennyiségeket összegezni. A teljes fogyasztás 100 kilométerenként L liter, így K kilométeren (K · L) / 100 liter, ez egész szám, mert a távolságok 100-zal oszthatók. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Nem kell az utat szakaszonként szimulálni: a tankolások helye most nem számít, csak az összes benzin és az összes fogyasztás. ||
Hint 2: || Összegezd a kezdeti benzint és a tankolt mennyiségeket, majd vond le a K kilométer fogyasztását, ami (K · L) / 100 liter. Nagy számoknál a szorzást végezd el az osztás előtt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long k, b, l;
    int n;
    cin >> k >> n >> b >> l;

    long long fuel = b;
    for (int i = 0; i < n; i++) {
        long long dist, amount;
        cin >> dist >> amount;
        fuel += amount;
    }

    fuel -= k * l / 100;

    cout << fuel << "\n";
    return 0;
}
