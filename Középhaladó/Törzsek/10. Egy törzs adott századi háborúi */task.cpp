/*
Megoldás lényege:
A keresett törzs háborúi közül azokat számoljuk meg, amelyekben a törzs részt vesz (akár a háborúzó, akár az ellenséges fél), és amelyek legalább részben beleesnek a megadott századba. A század évtartományát a római szám alapján határozzuk meg: XVII. = 1601-1700, XVIII. = 1701-1800, XIX. = 1801-1900. Egy háború akkor esik a századba, ha a kezdőév nem nagyobb a század utolsó événél, és a befejező év nem kisebb a század első événél. Egyetlen végigmenés az összes háborún elég, így az időigény O(K), ami K ≤ 2000 mellett messze az időkorlát alatt marad.
*/
/*
Hint 1: || Két feltételt kell egyszerre teljesíteni: a törzs az egyik fél a háborúban, és a háború legalább részben beleesik a megadott századba. ||
Hint 2: || A század évtartománya: XVII. = 1601-1700, XVIII. = 1701-1800, XIX. = 1801-1900. Egy háború akkor esik bele, ha a kezdőév nem nagyobb a század utolsó événél, és a befejező év nem kisebb a század első événél. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Az évszázad első és utolsó éve (XVII., XVIII., XIX.)
pair<int, int> evszazad(const string &sz) {
    string t;
    for (char c : sz)
        if (isalpha((unsigned char)c)) t += c;
    if (t == "XVII") return {1601, 1700};
    if (t == "XVIII") return {1701, 1800};
    return {1801, 1900};
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<array<int, 4>> haboru(k);
    for (auto &h : haboru)
        cin >> h[0] >> h[1] >> h[2] >> h[3];
    int s;
    string sz;
    cin >> s >> sz;
    auto [a, b] = evszazad(sz);

    int db = 0;
    for (const auto &h : haboru) {
        bool resztvevo = h[0] == s || h[1] == s;
        bool beleesik = h[2] <= b && h[3] >= a;
        if (resztvevo && beleesik) db++;
    }
    cout << db << "\n";
    return 0;
}
