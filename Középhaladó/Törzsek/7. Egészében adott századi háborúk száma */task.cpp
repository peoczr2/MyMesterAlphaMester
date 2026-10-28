/*
Megoldás lényege:
Egy háború akkor esik teljes egészében a századba, ha a kezdő éve nem korábbi a század első événél, és a befejező éve nem későbbi a század utolsó événél. A századok határai: XVII. = 1601–1700, XVIII. = 1701–1800, XIX. = 1801–1900. A bemenet végén álló római számot a záró pont levágása után pontos egyezéssel dolgozzuk fel, majd egyetlen végigmenéssel megszámoljuk a feltételnek megfelelő háborúkat. Az idő O(K), ami K ≤ 2000 mellett azonnali.
*/
/*
Hint 1: || A háború akkor van teljesen a században, ha a kezdő év nem a század előtt kezdődik, a befejező év pedig nem a század után ér véget. Ehhez a századnak két határ, egy első és egy utolsó éve kell. ||
Hint 2: || Az utolsó sor szövegét (pl. XIX.) először alakítsd át két évszámmá, és a záró pontot vágd le, mielőtt összehasonlítod. Utána egy végigmenéssel számold meg a két feltételnek megfelelő háborúkat. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<array<int, 4>> haboru(k);
    for (auto &h : haboru)
        cin >> h[0] >> h[1] >> h[2] >> h[3];

    string szazad;
    cin >> szazad;
    while (!szazad.empty() && szazad.back() == '.')
        szazad.pop_back();

    int elso, utolso;
    if (szazad == "XVII") {
        elso = 1601, utolso = 1700;
    } else if (szazad == "XVIII") {
        elso = 1701, utolso = 1800;
    } else {
        elso = 1801, utolso = 1900;
    }

    int db = 0;
    for (const auto &h : haboru)
        if (h[2] >= elso && h[3] <= utolso) db++;
    cout << db << "\n";
    return 0;
}
