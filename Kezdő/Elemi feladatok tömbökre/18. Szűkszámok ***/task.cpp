/*
Megoldás lényege:
A szűkszám jegyeinek értéke a hét hatványai (A = 1, E = 7, O = 49, K = 343, T = 2401, H = 16807, M = 117649). A szabály szerint a nagyobb jegy előtt álló kisebb, egyforma jegyek értékét ki kell vonni a nagyobb jegy értékéből, minden más jegy értéke összeadódik. Ezért a szöveget egyforma jegyek futamaira bontjuk: egy futam értéke a jegy értékének és a futam hosszának szorzata. Ha a futam után nagyobb jegy következik, a futam értékét kivonjuk, különben hozzáadjuk. Így a teljes összeg egyetlen balról jobbra haladó bejárással, lineáris időben kiszámítható. A nem minimális alakok (például az EOAE) is ugyanazt az értéket adják, mert a szabály ugyanígy összegez és von ki.
*/
/*
Hint 1: || Minden jegyhez tartozik egy fix érték: A = 1, E = 7, O = 49, K = 343, T = 2401, H = 16807, M = 117649, ezeket egy táblázatban tárold. ||
Hint 2: || Az egymás után álló, azonos jegyeket fogd össze futamokba, és a futam után álló jegy értékét hasonlítsd a futam jegyének értékéhez: ha az nagyobb, a futamot vond ki, különben add hozzá. ||
Hint 3: || Balról jobbra egy ciklus elég: a futam végét az első eltérő jegy adja meg, a futam hosszát a két index különbsége, az összeget long long típusban tartsd. ||
*/
#include <bits/stdc++.h>
using namespace std;

// A szűkszámjegy értéke: a hét hatványai (A = 7^0, E = 7^1, ..., M = 7^6)
long long ertek(char c) {
    switch (c) {
        case 'A': return 1;
        case 'E': return 7;
        case 'O': return 49;
        case 'K': return 343;
        case 'T': return 2401;
        case 'H': return 16807;
        case 'M': return 117649;
        default: return 0;
    }
}

int main() {
    string s;
    cin >> s;

    long long osszeg = 0;
    size_t i = 0;
    while (i < s.size()) {
        // Az egyforma jegyek futama: i és j közötti rész
        size_t j = i;
        while (j < s.size() && s[j] == s[i]) j++;

        long long darab = (long long)(j - i);
        long long v = ertek(s[i]);
        bool kivonando = j < s.size() && ertek(s[j]) > v;
        osszeg += kivonando ? -darab * v : darab * v;
        i = j;
    }

    cout << osszeg << "\n";
    return 0;
}
