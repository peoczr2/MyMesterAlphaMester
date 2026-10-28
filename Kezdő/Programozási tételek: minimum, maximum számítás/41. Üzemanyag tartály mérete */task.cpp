/*
Megoldás lényege:
Az üzemanyag-szintet a megtett úton követjük: két kút között a fogyasztás a megtett távolságból számolható, a kutaknál pedig a tankolt mennyiség hozzáadódik. A távolságok 100-zal oszthatók, így a fogyasztás egész szám. A tartályban a legnagyobb szint a kezdeti B literből vagy valamelyik tankolás utáni szintből adódik, mert két tankolás között a szint csak csökken. Ezért a tartály minimális mérete ezek maximuma, és elegendő a kutakon sorrendben végigmenni. Az időigény O(N), a tárigény O(1).
*/
/*
Hint 1: || Az üzemanyag-szint csak a kutaknál nő, két kút között csak fogy. Vezesd végig a szintet az indulástól kezdve, sorrendben a kutakon, és közben figyeld, mikor a legnagyobb. ||
Hint 2: || Egy szakasz fogyasztása a távolság és L szorzata osztva 100-zal; a távolság 100-zal osztható, így ez egész szám. A kezdeti B és a tankolások utáni szintek közül kell a maximumot venni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long K, B, L;
    int N;
    cin >> K >> N >> B >> L;
    long long fuel = B;
    long long best = B;
    long long pos = 0;
    for (int i = 0; i < N; i++) {
        long long h, m;
        cin >> h >> m;
        fuel -= (h - pos) * L / 100;
        fuel += m;
        pos = h;
        best = max(best, fuel);
    }
    cout << best << "\n";
    return 0;
}
