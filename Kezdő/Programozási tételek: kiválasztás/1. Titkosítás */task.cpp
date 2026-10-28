/*
Megoldás lényege:
A táblázat belsejében minden betű pontosan egyszer szerepel, a sorát és az oszlopát pedig a táblázat szélén lévő betűk jelölik. A bemenet karaktereit balról jobbra haladva egyesével vizsgáljuk: minden karakterhez megkeressük a helyét a táblázat belsejében (sor és oszlop), a kódba pedig előbb a sor betűjét, majd az oszlop betűjét írjuk. A szóköz a táblázat üres cellájába, a c sor i oszlopába esik, ezért a kódja „ci”. Egy karakter keresése állandó számú lépés, így a program a szó hosszával arányos időben fut.
*/
/*
Hint 1: || Egy betű helyét két adat adja meg: melyik sorban (a, b vagy c) és melyik oszlopban (a–i) áll a táblázat belsejében. ||
Hint 2: || A táblázat belsejét tárold kétdimenziós karaktertömbben, és az üres cellába is tedd bele a szóközt, így a szóközre ugyanaz a keresés működik. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    // A táblázat belseje: 3 sor (a, b, c) és 9 oszlop (a..i). Az utolsó cella üres, az a szóköz.
    const char table[3][9] = {
        {'i', 'o', 'q', 'h', 'b', 'f', 'y', 'l', 'w'},
        {'n', 'r', 'a', 'g', 's', 'k', 't', 'e', 'z'},
        {'d', 'u', 'p', 'x', 'c', 'j', 'v', 'm', ' '}
    };

    string word;
    getline(cin, word);

    string code;
    for (char ch : word) {
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (table[row][col] == ch) {
                    code += char('a' + row);
                    code += char('a' + col);
                }
            }
        }
    }

    cout << code << '\n';
    return 0;
}
