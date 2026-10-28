/*
Megoldás lényege:
Az ingánként adott fonálhosszt milliméterben kapjuk, a képlet viszont méterrel számol, ezért először 1000-rel osztunk. Egy inga lengési ideje T = 2 * pi * sqrt(l / g), a feladatban megadott pi = 3.14159 és g = 9.81 közelítésével. Az M másodperc alatt megtett teljes lengések száma az M / T hányados egész része, ezt double-lel számoljuk és lefelé kerekítjük. Mivel minden inga egy konstans idejű számítás, az időigény O(N).
*/
/*
Hint 1: || Számold ki egy lengés idejét a képlettel, majd nézd meg, hány ilyen lengésidő fér bele M másodpercbe. ||
Hint 2: || Figyelj a mértékegységre: a fonálhossz milliméterben van, a képlet méterben számol, ezért a fonálhosszat előbb el kell osztani 1000-rel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    const double PI = 3.14159;
    const double G = 9.81;

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        double lMm, m;
        cin >> lMm >> m;
        double l = lMm / 1000.0;
        double t = 2 * PI * sqrt(l / G);
        long long teljes = (long long)floor(m / t);
        cout << teljes << "\n";
    }
    return 0;
}
