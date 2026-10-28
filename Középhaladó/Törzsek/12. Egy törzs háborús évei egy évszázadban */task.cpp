/*
Megoldás lényege:
A törzs háborúiból azt kell megszámolni, hány olyan év van, amely a megadott századba esik, és amelyben a törzs háborúban állt. A század évtartományát a római szám alapján határozzuk meg: XVII. = 1601-1700, XVIII. = 1701-1800, XIX. = 1801-1900. Minden olyan háborúnál, amelyben a törzs részt vesz, a háború és a század közös éveit jelöljük meg egy logikai tömbben, amelynek mérete legfeljebb 100. Mivel több háború is átfedhet, a közös évek egyszer számítanak, a végén pedig a megjelölt évek számát írjuk ki. Az időigény O(K * 100), ami K ≤ 2000 mellett messze az időkorlát alatt marad.
*/
/*
Hint 1: || A kérdés az, hogy a törzs háborúi a megadott századon belül hány különböző évben voltak aktívak. Egy év csak egyszer számít, akkor is, ha két háború ugyanabban az évben átfedésben van. ||
Hint 2: || Készíts jelölőtömböt a század éveire, és minden olyan háborúnál, amelyben a törzs részt vesz, jelöld meg a háború és a század közös éveit. A megjelölt évek száma a válasz. ||
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

    vector<bool> volt(b - a + 1, false);
    for (const auto &h : haboru) {
        if (h[0] != s && h[1] != s) continue;
        int from = max(h[2], a), to = min(h[3], b);
        for (int ev = from; ev <= to; ev++)
            volt[ev - a] = true;
    }
    int db = count(volt.begin(), volt.end(), true);
    cout << db << "\n";
    return 0;
}
