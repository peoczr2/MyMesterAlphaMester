/*
Először megtisztítjuk a szöveget és a kulcsot: a nem angol ábécébeli karaktereket kihagyjuk, a kisbetűket nagybetűvé alakítjuk. A kulcsot annyiszor ismételjük, hogy hossza megegyezzen a szöveg hosszával. A Vigenère-tábla sor és oszlop metszéspontjában álló betű sorszáma a két betű sorszámának összege modulo 26, így a titkosított karakter (szöveg + kulcs) mod 26 alapján kiszámolható. Az időigény a szöveg hosszával arányos, ami 10 000 karakterig bőven elég.
*/
/*
Hint 1: || A tábla metszéspontja a két betű sorszámának összege modulo 26. Ha az A betű sorszáma 0, a B-é 1, és így tovább a Z-ig 25, akkor a titkosított betű sorszáma (szöveg betűje + kulcs betűje) mod 26. ||
Hint 2: || Nem kell előre összefűzni a kulcsot: az i-edik szövegkarakterhez a kulcs (i mod kulcshossz)-adik karaktere tartozik. A tisztítás után mindkét sor csak nagybetűket tartalmaz. ||
*/

#include <bits/stdc++.h>
using namespace std;

// Csak az angol ábécé betűit tartja meg, a kisbetűket nagybetűvé alakítja.
string tisztit(const string &s) {
    string r;
    for (char c : s) {
        if ('a' <= c && c <= 'z') r += (char)(c - 'a' + 'A');
        else if ('A' <= c && c <= 'Z') r += c;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string szoveg, kulcs;
    getline(cin, szoveg);
    getline(cin, kulcs);
    szoveg = tisztit(szoveg);
    kulcs = tisztit(kulcs);

    // A kulcs ismétlésével kapott sorozat hossza megegyezik a szöveg hosszával.
    string kulcs_sor(szoveg.size(), 'A');
    for (size_t i = 0; i < szoveg.size(); i++)
        kulcs_sor[i] = kulcs[i % kulcs.size()];

    string titkos(szoveg.size(), 'A');
    for (size_t i = 0; i < szoveg.size(); i++)
        titkos[i] = (char)('A' + (szoveg[i] - 'A' + kulcs_sor[i] - 'A') % 26);

    cout << "#\n" << szoveg << "\n";
    cout << "#\n" << kulcs << "\n";
    cout << "#\n" << titkos << "\n";

    return 0;
}
