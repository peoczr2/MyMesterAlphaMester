/*
Megoldás lényege:
Egy háború akkor esik a megadott századba, ha legalább egy évben átfedi a század évtartományát. A századok évtartománya: XVII. = 1601-1700, XVIII. = 1701-1800, XIX. = 1801-1900. Egy [kezdőév, befejező év] háború pontosan akkor fedi át az [lo, hi] tartományt, ha a kezdőéve nem nagyobb hi-nél, és a befejező éve nem kisebb lo-nál. Egyetlen végigmenéssel megszámoljuk az ilyen háborúkat, az időigény O(K).
*/
/*
Hint 1: || Nem kell minden évet végigvizsgálni: elég két feltételt nézni egy háborúra, hogy az átfedi-e a századot. ||
Hint 2: || A század évtartománya XVII. esetén 1601-1700, XVIII. esetén 1701-1800, XIX. esetén 1801-1900. A háború kezdőéve legyen legfeljebb a tartomány utolsó éve, a befejező éve pedig legalább a tartomány első éve. ||
*/
#include <bits/stdc++.h>
using namespace std;

// A század első és utolsó éve
pair<int, int> evszazad(const string &r) {
    if (r == "XVII") return {1601, 1700};
    if (r == "XVIII") return {1701, 1800};
    return {1801, 1900};
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<array<int, 4>> haboru(k);
    for (auto &h : haboru)
        cin >> h[0] >> h[1] >> h[2] >> h[3];

    string szoveg;
    cin >> szoveg;
    // A római szám után álló pontot kihagyjuk
    string r;
    for (char c : szoveg)
        if (isalpha((unsigned char)c)) r += c;
    auto [lo, hi] = evszazad(r);

    int db = 0;
    for (const auto &h : haboru)
        if (h[2] <= hi && h[3] >= lo) db++;
    cout << db << "\n";
    return 0;
}
