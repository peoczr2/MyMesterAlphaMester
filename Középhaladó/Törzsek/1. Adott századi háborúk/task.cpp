/*
Megoldás lényege:
A század évtartományát a római szám alapján határozzuk meg: XVII. = 1601-1700, XVIII. = 1701-1800, XIX. = 1801-1900. Minden háborúnál megvizsgáljuk, hogy legalább részben beleesik-e a századba: ez akkor igaz, ha a kezdőév nem nagyobb a század utolsó événél, és a befejező év nem kisebb a század első événél. A feltételt teljesítő háborúk teljes időtartamát (befejező év − kezdő év + 1) összeadjuk, mert a feladat a háborúk összes idejét kéri, nem csak a századon belüli részt. Az időigény O(K), ami K ≤ 2000 mellett bőven belefér az időkorlátba, az összeg pedig 64 bites egészben fér el.
*/
/*
Hint 1: || A háború akkor esik legalább részben a századba, ha időintervallumuk átfedésben van a század évtartományával. Két intervallum átfed, ha az egyik kezdete nem későbbi a másik végénél, és fordítva. ||
Hint 2: || Ha a háború [s, e] és a század [a, b], akkor a feltétel: s ≤ b és e ≥ a. Egy megfelelő háború teljes hosszát, vagyis e − s + 1 évet adj az összeghez, és az összeget 64 bites egész tárolja. ||
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
    string sz;
    cin >> sz;
    auto [a, b] = evszazad(sz);

    long long ossz = 0;
    for (const auto &h : haboru) {
        int kezd = h[2], vege = h[3];
        if (kezd <= b && vege >= a)
            ossz += vege - kezd + 1;
    }
    cout << ossz << "\n";
    return 0;
}
