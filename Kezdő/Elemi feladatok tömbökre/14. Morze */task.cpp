/*
Megoldás lényege:
A kódtáblázatot egy 26 elemű tömbben tároljuk: az i. elem a (a + i) betű Morze-kódja. A bemeneti
sort karakterenként dolgozzuk fel: minden betű kódja után egy szóközt írunk, a bemeneti szóköz helyére
pedig két szóközt. Így a szavak között a kért három szóköz jön létre. A kódolás a bemenet hosszával
arányosan lineáris időben fut.
*/
/*
Hint 1: || A betűk kódjait egy 26 elemű string tömbben tárold, így a c betű indexe c - 'a' lesz. ||
Hint 2: || Egy betű kódja után egy szóköz kell, a bemeneti szóköz pedig a kimenetben két szóköz lesz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    const string code[26] = {
        ".-",   "-...", "-.-.", "-..",  ".",    "..-.", "--.",  "....", "..",   ".---",
        "-.-",  ".-..", "--",   "-.",   "---",  ".--.", "--.-", ".-.",  "...",  "-",
        "..-",  "...-", ".--",  "-..-", "-.--", "--.."
    };

    string s;
    getline(cin, s);

    string out;
    for (char c : s) {
        if (c == ' ') {
            out += "  ";
        } else if (c >= 'a' && c <= 'z') {
            out += code[c - 'a'];
            out += ' ';
        }
    }
    cout << out << '\n';
    return 0;
}
