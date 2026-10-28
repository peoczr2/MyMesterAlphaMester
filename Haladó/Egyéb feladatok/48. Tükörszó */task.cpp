/*
Megoldás lényege:
A magyar ábécé betűi állhatnak több karakterből is (cs, dz, dzs, gy, ly, ny, sz, ty, zs), és a hosszú, megkettőzött mássalhangzók (ccs, ddz, ddzs, ggy, lly, nny, ssz, tty, zzs) is egy betűt adnak, például a hosszú szóban az ssz. A szöveget balról jobbra bontjuk betűkre úgy, hogy mindig a leghosszabb illeszkedő betűt vesszük, így a dzs nem dz és s. A betűk sorrendjét megfordítjuk, de egy betű belső karakterei megmaradnak. Az ékezetes magánhangzók kétbájtos UTF-8 karakterek, ezeket egy betűnek tekintjük, így a bájtonkénti bejárás is helyes. Az eljárás lineáris, O(n).
*/
/*
Hint 1: || Nem a karaktereket, hanem a betűket kell megfordítani: előbb bontsd fel a szót betűkre, és csak utána fordíts. Balról jobbra haladva mindig a leghosszabb betűt vedd, például a dzs három karakter, nem dz és s. ||
Hint 2: || Ne a szöveget fordítsd meg karakterenként: tárold a betűk kezdő pozícióit, majd fordított sorrendben írd ki a betűket, mindegyiket a saját kezdő pozíciójától a következőig. Az ékezetes betűk több bájtosak, ezért a betű hosszát az első bájtjából határozd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    size_t n = s.size();

    // start[k]: a k-edik betű első bájtjának indexe; az utolsó elem n
    vector<unsigned> start;
    start.reserve(n + 1);
    size_t i = 0;
    while (i < n) {
        start.push_back((unsigned)i);
        unsigned char c = (unsigned char)s[i];
        size_t len = 1;
        if (c < 0x80) {
            char c1 = i + 1 < n ? s[i + 1] : 0;
            char c2 = i + 2 < n ? s[i + 2] : 0;
            char c3 = i + 3 < n ? s[i + 3] : 0;
            // a leghosszabb illeszkedés: előbb a négy, majd a három, végül a két karakteres betűk
            if (c == 'd' && c1 == 'd' && c2 == 'z' && c3 == 's') len = 4;
            else if (c == 'd' && c1 == 'z' && c2 == 's') len = 3;
            else if (c == 'c' && c1 == 'c' && c2 == 's') len = 3;
            else if (c == 'd' && c1 == 'd' && c2 == 'z') len = 3;
            else if (c == 'g' && c1 == 'g' && c2 == 'y') len = 3;
            else if (c == 'l' && c1 == 'l' && c2 == 'y') len = 3;
            else if (c == 'n' && c1 == 'n' && c2 == 'y') len = 3;
            else if (c == 's' && c1 == 's' && c2 == 'z') len = 3;
            else if (c == 't' && c1 == 't' && c2 == 'y') len = 3;
            else if (c == 'z' && c1 == 'z' && c2 == 's') len = 3;
            else if (c == 'c' && c1 == 's') len = 2;
            else if (c == 'd' && c1 == 'z') len = 2;
            else if (c == 'g' && c1 == 'y') len = 2;
            else if (c == 'l' && c1 == 'y') len = 2;
            else if (c == 'n' && c1 == 'y') len = 2;
            else if (c == 's' && c1 == 'z') len = 2;
            else if (c == 't' && c1 == 'y') len = 2;
            else if (c == 'z' && c1 == 's') len = 2;
        } else {
            // ékezetes magánhangzó: UTF-8 több bájt
            len = c >= 0xF0 ? 4 : (c >= 0xE0 ? 3 : 2);
            if (i + len > n) len = n - i;
        }
        i += len;
    }
    start.push_back((unsigned)n);

    // a betűk fordított sorrendben, mindegyik a saját bájtjaival
    string out;
    out.reserve(n + 1);
    for (size_t k = start.size() - 1; k-- > 0;)
        out.append(s, start[k], start[k + 1] - start[k]);
    cout << out << '\n';
    return 0;
}
