/*
Megoldás lényege: az utasításokat balról jobbra egyszer végigjárva követjük a robot helyzetét két koordinátával: az E és D az ED (észak-dél), a K és N a KN (kelet-nyugat) tengelyen mozdít el. Az egyszerűsíthetőséget a szomszédos ED, DE, KN, NK párok keresése adja. A kiindulási pontba való visszajutáshoz az ED tengelyen |y|, a KN tengelyen |x| lépés kell, ahol (x, y) a végpont. A legnagyobb távolságot a négyzetes euklideszi távolsággal számoljuk, és az első előfordulás lépéssorszámát írjuk ki. Az energia: 2 az indulásra, 1 minden lépésre, 2 minden irányváltásra. A rövid alak kibontása és a rövidítés futamonként történik. Az időigény a programok hosszának összege, vagyis legfeljebb 600 * 200 lépés.
*/
/*
Hint 1: || Kövesd végig az utasításokat sorban, és közben tartsd nyilván a robot két koordinátáját: az ED tengely (észak-dél) és a KN tengely (kelet-nyugat) szerint. ||
Hint 2: || Az energiához a kiindulás 2 egysége mellett minden lépés 1 egység, és minden olyan hely, ahol két egymás utáni betű különbözik, 2 egység. A rövid alaknál egy betű futamát darabszám és betű alakban írd, de az 1 hosszú futamnál csak a betűt. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Az U rövid alakját kibontja, például "2D3N" -> "DDNNN".
string kibont(const string& u) {
    string r;
    int szam = 0;
    bool van_szam = false;
    for (char c : u) {
        if (isdigit((unsigned char)c)) {
            szam = szam * 10 + (c - '0');
            van_szam = true;
        } else {
            r.append(van_szam ? szam : 1, c);
            szam = 0;
            van_szam = false;
        }
    }
    return r;
}

// Az utasítássor rövidített alakja: a betűk futamai darabszám és betű alakban.
string roviditett(const string& p) {
    string r;
    size_t i = 0;
    while (i < p.size()) {
        size_t j = i;
        while (j < p.size() && p[j] == p[i]) j++;
        if (j - i > 1) r += to_string(j - i);
        r += p[i];
        i = j;
    }
    return r;
}

// Igaz, ha van két szomszédos, ellentétes irányú utasítás.
bool egyszerusitheto(const string& p) {
    for (size_t i = 0; i + 1 < p.size(); i++) {
        char a = p[i], b = p[i + 1];
        if ((a == 'E' && b == 'D') || (a == 'D' && b == 'E') ||
            (a == 'K' && b == 'N') || (a == 'N' && b == 'K'))
            return true;
    }
    return false;
}

// Az utasítássor energiaigénye: indulás 2, minden lépés 1, minden irányváltás 2.
int energia(const string& p) {
    int e = 2 + (int)p.size();
    for (size_t i = 1; i < p.size(); i++)
        if (p[i] != p[i - 1]) e += 2;
    return e;
}

int main() {
    int n, x, e;
    string u;
    cin >> n >> x >> e >> u;
    vector<string> p(n + 1);
    for (int i = 1; i <= n; i++) cin >> p[i];

    // 1. részfeladat: egyszerűsíthető-e az X. program
    cout << "#\n" << (egyszerusitheto(p[x]) ? 1 : 0) << "\n";

    // 2. részfeladat: visszajutás az ED és a KN tengelyen az X. program után
    int ey = 0, kx = 0;
    for (char c : p[x]) {
        if (c == 'E') ey++;
        else if (c == 'D') ey--;
        else if (c == 'K') kx++;
        else if (c == 'N') kx--;
    }
    cout << "#\n" << abs(ey) << " " << abs(kx) << "\n";

    // 3. részfeladat: a legnagyobb távolság első előfordulásának lépéssorszáma
    int ax = 0, ay = 0, legnagyobb = -1, lepes_szam = 0;
    int lepes = 0;
    for (char c : p[x]) {
        lepes++;
        if (c == 'E') ay++;
        else if (c == 'D') ay--;
        else if (c == 'K') ax++;
        else if (c == 'N') ax--;
        int tav = ax * ax + ay * ay;
        if (tav > legnagyobb) {
            legnagyobb = tav;
            lepes_szam = lepes;
        }
    }
    cout << "#\n" << lepes_szam << "\n";

    // 4. részfeladat: a legfeljebb E energiával végrehajtható programok
    vector<int> jo;
    for (int i = 1; i <= n; i++)
        if (energia(p[i]) <= e) jo.push_back(i);
    cout << "#\n" << jo.size();
    for (int i : jo) cout << " " << i;
    cout << "\n";

    // 5. részfeladat: az U rövid alakú program kibontott alakja
    cout << "#\n" << kibont(u) << "\n";

    // 6. részfeladat: az összes program rövid alakja
    cout << "#\n";
    for (int i = 1; i <= n; i++) cout << roviditett(p[i]) << "\n";

    return 0;
}
