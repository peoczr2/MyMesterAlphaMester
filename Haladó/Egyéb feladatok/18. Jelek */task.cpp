/*
Megoldás lényege:
Az A-nyelv páros hosszú szavai U a U b alakúak: a szó első fele U, utána egy a betű, majd ismét U,
végül a betű ellentéte (b). A bontás egyértelmű, mert |U| = (|w| - 2) / 2, így a felismerés egyetlen
útvonalon, rekurzívan ellenőrzi a szavakat, összesen O(|w|) munkával. A B-nyelv a nem üres, helyesen
zárójelezett szavak halmaza (0 = nyitó, 1 = záró), ezért elég a prefixumok egyensúlyát ellenőrizni:
sosem lehet negatív, és a végén nullának kell lennie. Egy szó mindkét nyelvbe tartozhat, ilyenkor AB.
*/
/*
Hint 1: || Vizsgáld meg az A-szavak hosszát: egy U-ból készült új szó hossza mindig 2|U| + 2. ||
Hint 2: || Egy páros hosszú w szó akkor A-beli, ha van olyan U, hogy w = U a U b, ahol a és b különböző, és U maga is A-beli. A rekurzió mélysége logaritmikus. ||
Hint 3: || A B-nyelvre: a 0 nyitó, az 1 záró zárójel. Nézd meg, hogy a prefixumokban sosem fordul-e elő több záró, mint nyitó, és a teljes szó végén a két szám egyenlő-e. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Igaz, ha a w szó benne van az A-nyelvben.
bool inA(const string& w) {
    int L = w.size();
    if (L == 1) return w == "0";
    if (L == 2) return w == "01";
    if (L < 4 || L % 2 == 1) return false;
    int m = (L - 2) / 2;                        // w = U a U b, |U| = m
    if (w[m] == w[2 * m + 1]) return false;     // a és b különbözik
    if (w.substr(0, m) != w.substr(m + 1, m)) return false;
    return inA(w.substr(0, m));
}

// Igaz, ha a w szó benne van a B-nyelvben (nem üres, helyes zárójelezés).
bool inB(const string& w) {
    if (w.empty()) return false;
    int egyenseg = 0;
    for (char ch : w) {
        egyenseg += (ch == '0') ? 1 : -1;
        if (egyenseg < 0) return false;
    }
    return egyenseg == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        bool a = inA(s);
        bool b = inB(s);
        if (a && b) cout << "AB\n";
        else if (a) cout << "A\n";
        else if (b) cout << "B\n";
        else cout << "C\n";
    }
    return 0;
}
