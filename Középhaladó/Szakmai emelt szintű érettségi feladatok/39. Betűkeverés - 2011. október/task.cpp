/*
Megoldás lényege:
A szöveget egy sorban olvassuk be, majd végigmegyünk rajta, és a betűkből álló összefüggő szakaszokat (szavakat) keressük meg. Betűnek tekintjük az angol ábécé betűit és a 128 feletti bájtokat is, mert a magyar ékezetes betűk egybájtos kódolással szerepelnek. A szóköz és a többi karakter szóhatárként működik, ezeket változatlanul hagyjuk. Egy szó első és utolsó betűje helyben marad, a belső részt std::reverse fordítja meg, de csak akkor, ha a szónak legalább három betűje van. Minden karaktert legfeljebb kétszer érintünk, ezért az időigény O(N), ahol N a szöveg hossza (legfeljebb 1 000 000 karakter).
*/
/*
Hint 1: || Szavaknak a betűk összefüggő szakaszait tekintsd, a szóköz és a többi nem betű karakter szóhatár. A minta egybájtos magyar kódolású, az ékezetes betű egy bájt és a szó részeként viselkedik, ezért a 128 feletti bájtokat is betűnek számold. Csak olyan szónak van belseje, amelynek legalább három betűje van. ||
Hint 2: || Két indexszel dolgozz: az egyik a szó elejét jelöli, a másik a végét, amit addig növelsz, amíg betű van. A belső rész a kezdőindex+1-től a végindex-1-ig tart (a végindex kizárólagos), és ezt a tartományt fordítsd meg a std::reverse függvénnyel. ||
*/
#include <bits/stdc++.h>
using namespace std;

// betű: az angol ábécé betűi, és a 128 feletti (egybájtos magyar) karakterek
bool isLetter(char c) {
    unsigned char u = (unsigned char)c;
    return (u >= 'a' && u <= 'z') || (u >= 'A' && u <= 'Z') || u >= 128;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    getline(cin, s);
    int n = s.size();
    int i = 0;
    while (i < n) {
        if (!isLetter(s[i])) {
            i++;
            continue;
        }
        int j = i;
        while (j < n && isLetter(s[j])) j++;
        // a szó: s[i..j-1], a belső rész: s[i+1..j-2]
        if (j - i >= 3) reverse(s.begin() + i + 1, s.begin() + j - 1);
        i = j;
    }
    cout << s << "\n";
    return 0;
}
