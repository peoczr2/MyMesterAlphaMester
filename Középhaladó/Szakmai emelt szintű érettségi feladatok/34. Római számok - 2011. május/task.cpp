/*
Megoldás lényege: mohó átváltás. Egy táblázatban felsoroljuk a római jelek összes lehetséges értékét csökkenő sorrendben, a 4, 9, 40, 90, 400 és 900 értékekre is a külön jelpárokkal (IV, IX, XL, XC, CD, CM). Minden számot a táblázat elejétől haladva vizsgálunk: amíg az aktuális érték nem nagyobb a maradéknál, hozzáfűzzük a jelet és levonjuk az értékét. Ez helyes, mert a római jelölésben a csoportok csökkenő értékben követik egymást, így a legnagyobb lehető csoport mindig az első lépésben kiválasztható. Egy szám átváltása legfeljebb 13 lépés, így az egész program O(N) időben fut, N ≤ 10^5 esetén bőven időben van.
*/
/*
Hint 1: || A római számjegyek többsége csökkenő értékben, egymás után adódik össze. Érdemes a legnagyobb értéktől indulni, és minden lépésben a lehető legnagyobb jelet levonni a számból. ||
Hint 2: || A 4, 9, 40, 90, 400 és 900 esetén nem egyetlen jel áll, hanem két jel (például CM a 900). Ezeket is vedd fel a táblázatba érték–jel párként, így egy egyszerű ciklus minden számot kezel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const string symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const int count = 13;

    int n;
    cin >> n;
    while (n--) {
        int x;
        cin >> x;
        string roman;
        for (int i = 0; i < count; i++) {
            while (x >= values[i]) {
                roman += symbols[i];
                x -= values[i];
            }
        }
        cout << roman << '\n';
    }
    return 0;
}
