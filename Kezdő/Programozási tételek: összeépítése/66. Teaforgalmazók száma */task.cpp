/*
Megoldás lényege:
A kérdés azt, hogy hány különböző cég teáját lehet kapni, ezért a vásárlások mennyiségei a megoldáshoz nem kellenek. Minden vásárlásnál beolvassuk a teafajta nevét, a mennyiséget pedig a következő sorból átugorjuk. A neveket halmazba (set) gyűjtjük, mert a halmazban minden név csak egyszer szerepel. A végén a halmaz mérete adja a választ. Az időigény O(N log N), N legfeljebb 100 esetén ez bőven elég.
*/
/*
Hint 1: || A vásárlások mennyisége nem fontos, csak az, hogy a bemenetben hány különböző cégnév fordul elő. ||
Hint 2: || Egy halmazba (set) tedd be a neveket: a halmazban minden név csak egyszer szerepel, így a halmaz mérete adja a választ. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Beolvas egy nem üres sort, a széleiről levágja a szóközöket és a sorvégi \r-t.
bool olvasSor(string& s) {
    while (getline(cin, s)) {
        size_t a = s.find_first_not_of(" \t\r");
        if (a == string::npos) continue;
        size_t b = s.find_last_not_of(" \t\r");
        s = s.substr(a, b - a + 1);
        return true;
    }
    return false;
}

int main() {
    string sor;
    olvasSor(sor);
    int n = stoi(sor);

    set<string> cegek;
    for (int i = 0; i < n; i++) {
        string nev, mennyiseg;
        olvasSor(nev);       // a teafajta (cég) neve
        cegek.insert(nev);
        olvasSor(mennyiseg); // a mennyiség, a megoldáshoz nem kell
    }

    cout << cegek.size() << "\n";
    return 0;
}
