/*
Megoldás lényege:
Egy év befektetése az előző két év befektetésének összege, így az évi befektetések 1, 1, 2, 3, 5, 8, ... Fibonacci-számok. Az A összeget úgy kell felírni, hogy a kiválasztott évek ne legyenek egymás mellett; erre a mohó, Zeckendorf-féle felbontás ad megoldást: mindig a legnagyobb, a maradéknál nem nagyobb Fibonacci-számot vesszük. Egy szám kiválasztása után a maradék kisebb a szomszédos Fibonacci-számnál, ezért a következő kiválasztott év legalább két évvel korábbi, így nincs két egymást követő év. A második sorban a kiválasztott években lévő befektetések összege szerepel, egy évvel későbbre tolva. A futás O(log A), mert A <= 10^8 esetén csak néhány tucat Fibonacci-szám van.
*/
/*
Hint 1: || Számold ki, mennyit fektet be az egyes években: az 1. és a 2. évben 1-et, utána minden év befektetése az előző két év befektetésének összege. ||
Hint 2: || Keresd meg a legnagyobb olyan Fibonacci-számot, amely nem nagyobb A-nál, vond le A-ból, és a maradékkal ismételd; a kiválasztott évek így nem lesznek egymás mellett. ||
Hint 3: || Az évek fordított sorrendben keletkeznek, ezért kiíráskor fordítsd meg a sorrendet. A második sorhoz minden kiválasztott évben a befektetést egy évvel később kell venni, azaz a következő Fibonacci-számot. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long A;
    if (!(cin >> A)) return 0;

    vector<long long> fib = {1, 1};
    while (fib.back() <= A) fib.push_back(fib[fib.size() - 1] + fib[fib.size() - 2]);

    long long rem = A;
    vector<int> years;
    long long shifted = 0;
    for (int i = (int)fib.size() - 2; i >= 0; --i) {
        if (fib[i] <= rem) {
            rem -= fib[i];
            years.push_back(i + 1);
            shifted += fib[i + 1];
        }
    }

    reverse(years.begin(), years.end());
    for (int i = 0; i < (int)years.size(); ++i) {
        if (i) cout << ' ';
        cout << years[i];
    }
    cout << '\n' << shifted << '\n';
    return 0;
}
