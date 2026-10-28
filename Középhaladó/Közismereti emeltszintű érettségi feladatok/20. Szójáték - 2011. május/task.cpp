/*
Megoldás lényege:
A magánhangzókat (a, e, i, o, u) betűnként számoljuk, a mássalhangzók száma pedig a szóhossz és a magánhangzók számának különbsége. A leghosszabb szavakat egy menetben gyűjtjük, majd ábécé szerint rendezzük. A létraszó pontosan az X szórészlet elé és mögé írt egy-egy betűből áll, ezért egy szó akkor tartozik X-hez, ha hossza |X|+2, és a belső része (az első és az utolsó betű nélkül) egyenlő X-szel. A szólétrákat ugyanezzel a belső résszel csoportosítjuk: egy csoport egy szólétra, és csak a legalább két szóból álló csoportok kellenek. Mivel N legfeljebb 1000 és a szavak hossza legfeljebb 100, minden részfeladat gyorsan lefut.
*/
/*
Hint 1: || Az első három részfeladat a betűk és a szavak hosszának egyszerű végigvizsgálásával megoldható. A létraszavaknál figyelj arra, hogy a szó hossza pontosan X hossza plusz kettő legyen. ||
Hint 2: || A szólétráknál minden szóhoz vedd a belső részét, vagyis az első és az utolsó betű nélküli részt. Ezek szerinti csoportosítással megkapod az egyes fokokat, és csak a legalább két szavas csoportokat kell kiírni. ||
*/
#include <bits/stdc++.h>
using namespace std;

bool maganhangzo(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main() {
    string a, x;
    cin >> a >> x;
    int n;
    cin >> n;
    vector<string> szavak(n);
    for (string& s : szavak) {
        cin >> s;
    }

    // 1. részfeladat: a magánhangzók száma az A szóban
    int k = 0;
    for (char c : a) {
        if (maganhangzo(c)) k++;
    }
    cout << "#\n" << k << "\n";

    // 2. részfeladat: a leghosszabb szavak, ábécé sorrendben
    size_t maxHossz = 0;
    for (const string& s : szavak) {
        maxHossz = max(maxHossz, s.size());
    }
    vector<string> leghosszabbak;
    for (const string& s : szavak) {
        if (s.size() == maxHossz) leghosszabbak.push_back(s);
    }
    sort(leghosszabbak.begin(), leghosszabbak.end());
    cout << "#\n";
    for (size_t i = 0; i < leghosszabbak.size(); i++) {
        if (i > 0) cout << ' ';
        cout << leghosszabbak[i];
    }
    cout << "\n";

    // 3. részfeladat: több magánhangzó, mint mássalhangzó
    int m = 0;
    for (const string& s : szavak) {
        int magan = 0;
        for (char c : s) {
            if (maganhangzo(c)) magan++;
        }
        int massal = (int)s.size() - magan;
        if (magan > massal) m++;
    }
    cout << "#\n" << m << "\n";

    // 4. részfeladat: az X szórészlet létraszavai
    vector<string> letra;
    for (const string& s : szavak) {
        if (s.size() == x.size() + 2 && s.compare(1, x.size(), x) == 0) {
            letra.push_back(s);
        }
    }
    cout << "#\n" << letra.size() << "\n";
    for (size_t i = 0; i < letra.size(); i++) {
        if (i > 0) cout << ' ';
        cout << letra[i];
    }
    cout << "\n";

    // 5. részfeladat: szólétrák, azaz a legalább két szavas fokok
    map<string, vector<string>> fokok;
    for (const string& s : szavak) {
        if (s.size() < 3) continue;
        fokok[s.substr(1, s.size() - 2)].push_back(s);
    }
    vector<vector<string>> letrak;
    for (const auto& [fok, szavakFokon] : fokok) {
        if (szavakFokon.size() >= 2) letrak.push_back(szavakFokon);
    }
    cout << "#\n" << letrak.size() << "\n";
    for (const auto& letraSor : letrak) {
        for (size_t i = 0; i < letraSor.size(); i++) {
            if (i > 0) cout << ' ';
            cout << letraSor[i];
        }
        cout << "\n";
    }

    return 0;
}
