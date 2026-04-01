/*
Pontosan S osszsulyu penzhalmazt keresunk ugy, hogy az ertekosszeg a leheto legkisebb legyen, es
egy cimletbol tetszoleges sok darab lehet. Ez klasszikus korlatlan hatizsak-feladat minimumra:
dp[w] legyen a w osszsuly eloallitasahoz szukseges legkisebb ertek. Kezdetben dp[0]=0, mas
allapot vegtelen. Minden cimletnel ujra felhasznalhato ugyanaz a cimlet, ezert a sulyokat novekvo
sorrendben frissitjuk. A valasz dp[S], ha S egyaltalan eloallithato.
*/
/*
Hint 1: || A suly az "kapacitas", az ertek pedig most koltseg, amit minimalizalni kell. ||
Hint 2: || Egy cimletbol tobb is lehet, tehat korlatlan hatizsak kell, nem 0-1. ||
Hint 3: || A dp[w] allapot azt mondja meg, mennyi a legkisebb ertek pontosan w osszsulyra. ||
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, target_weight;
    cin >> n >> target_weight;

    const int inf = numeric_limits<int>::max() / 4;
    vector<int> dp(target_weight + 1, inf);
    dp[0] = 0;

    for (int i = 0; i < n; ++i) {
        int value, weight;
        cin >> value >> weight;
        for (int current = weight; current <= target_weight; ++current) {
            dp[current] = min(dp[current], dp[current - weight] + value);
        }
    }

    if (dp[target_weight] >= inf) {
        cout << -1 << '\n';
    } else {
        cout << dp[target_weight] << '\n';
    }
    return 0;
}