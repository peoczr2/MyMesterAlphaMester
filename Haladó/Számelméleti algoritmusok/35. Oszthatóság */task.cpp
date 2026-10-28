/*
Megoldás lényege:
A 19-cel, 29-cel és 551-gyel való oszthatóságot a szám maradékából döntjük el, és a maradékot közvetlenül számoljuk ki.
A szám akár 1000 jegyű is lehet, ezért nem tároljuk egész típusban: a számjegyeken balról jobbra haladva a maradékot r = (10·r + számjegy) mod m szerint frissítjük.
A maradék mindig kisebb m-nél, így a számítás kis számokkal végezhető el.
A szövegben leírt 19-es és 29-es szabályok ugyanerre a döntésre vezetnek, de a maradék közvetlen kiszámítása nem igényli őket.
Mivel 551 = 19 · 29, a 551-gyel való oszthatóság ellenőrzése külön is megerősíti az eredményt.
A három eredménysort a bemenet sorrendjében gyűjtjük, és soronként írjuk ki.
Időigény: O(N · L), ahol N a számok száma, L a leghosszabb számjegysor.
*/
/*
Hint 1: || Nem kell a számot tényleges értékként tárolni: az oszthatóság csak a maradéktól függ, a maradékot pedig karakterenként lehet frissíteni. ||
Hint 2: || Mivel a szám nagyon hosszú lehet, karakterenként építsd a maradékot: `r = (10*r + digit) mod m`. ||
*/

#include "../common.hpp"

static int mod_string(const string& s, int mod) {
    int r = 0;
    for (char c : s) r = (r * 10 + (c - '0')) % mod;
    return r;
}

static void print_line(const vector<string>& v) {
    for (int i = 0; i < (int)v.size(); ++i) {
        if (i) cout << ' ';
        cout << v[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    vector<string> r19, r29, r551;
    for (int i = 0; i < t; ++i) {
        string s;
        cin >> s;
        r19.push_back(mod_string(s, 19) == 0 ? "IGEN" : "NEM");
        r29.push_back(mod_string(s, 29) == 0 ? "IGEN" : "NEM");
        r551.push_back(mod_string(s, 551) == 0 ? "IGEN" : "NEM");
    }
    print_line(r19);
    print_line(r29);
    print_line(r551);
    return 0;
}
