/*
Megoldás lényege:
A megfejtés akkor az e heti feladványra érkezett, ha a tornyok helye és száma minden mezőn megegyezik a feladvány mezőivel. A hajók számát a 11-es mezők megszámlálásával kapjuk. A szomszédsági szabály ellenőrzéséhez minden hajó 8 szomszédos mezőjét megnézzük: ha ott másik hajó vagy torony áll, a megfejtés szabálytalan. Mivel a hajók nem takarják ki egymást, egy torony száma a tornyot tartalmazó sorban és oszlopban lévő hajók összege, ezt minden toronynál külön ellenőrizzük. A 10x10-es mező és legfeljebb 20 megfejtés miatt az egész program néhány tízezer lépésben lefut.
*/
/*
Hint 1: || A feladvány és a megfejtések mezőit egy az egyben össze lehet vetni. A megfejtésben a torony helyén az 1 és 9 közötti szám áll, a hajó helyén pedig 11. ||
Hint 2: || Egy torony számának ellenőrzéséhez számold meg a hajókat a torony sorában és oszlopában. Érdemes ezt előre kiszámolni soronként és oszloponként egy tömbbe. ||
Hint 3: || A szomszédsági szabályhoz minden hajó köré nézd meg a 8 szomszédos mezőt: ha ott másik hajó vagy torony van, a megfejtés nem megfelelő. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int MERET = 10;
const int HAJO = 11;

struct Megfejtes {
    string nev;
    int mezo[MERET][MERET];
};

// Igaz, ha a megfejtés tornyai pontosan a feladvány tornyai (hely és szám).
bool eHeti(const Megfejtes& m, const int feladvany[MERET][MERET]) {
    for (int r = 0; r < MERET; r++) {
        for (int c = 0; c < MERET; c++) {
            int torony = (m.mezo[r][c] >= 1 && m.mezo[r][c] <= 9) ? m.mezo[r][c] : 0;
            if (torony != feladvany[r][c]) return false;
        }
    }
    return true;
}

int hajokSzama(const Megfejtes& m) {
    int db = 0;
    for (int r = 0; r < MERET; r++) {
        for (int c = 0; c < MERET; c++) {
            if (m.mezo[r][c] == HAJO) db++;
        }
    }
    return db;
}

// Igaz, ha valamelyik hajó közvetlen (átlós irányt is beleértve) szomszédságában másik hajó vagy torony van.
bool szomszedsagiHiba(const Megfejtes& m) {
    for (int r = 0; r < MERET; r++) {
        for (int c = 0; c < MERET; c++) {
            if (m.mezo[r][c] != HAJO) continue;
            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    if (dr == 0 && dc == 0) continue;
                    int nr = r + dr, nc = c + dc;
                    if (nr < 0 || nr >= MERET || nc < 0 || nc >= MERET) continue;
                    int ertek = m.mezo[nr][nc];
                    if (ertek == HAJO || (ertek >= 1 && ertek <= 9)) return true;
                }
            }
        }
    }
    return false;
}

// Igaz, ha minden torony száma megegyezik a sorában és oszlopában lévő hajók számával.
bool toronySzamokOk(const Megfejtes& m, const int feladvany[MERET][MERET]) {
    int sorHajo[MERET] = {0};
    int oszlopHajo[MERET] = {0};
    for (int r = 0; r < MERET; r++) {
        for (int c = 0; c < MERET; c++) {
            if (m.mezo[r][c] == HAJO) {
                sorHajo[r]++;
                oszlopHajo[c]++;
            }
        }
    }
    for (int r = 0; r < MERET; r++) {
        for (int c = 0; c < MERET; c++) {
            if (feladvany[r][c] == 0) continue;
            if (sorHajo[r] + oszlopHajo[c] != feladvany[r][c]) return false;
        }
    }
    return true;
}

// A sorban lévő nem üres sor (a név), a sor végi \r és szóközök nélkül.
string nevetOlvas() {
    string sor;
    while (getline(cin, sor)) {
        while (!sor.empty() && isspace((unsigned char)sor.back())) sor.pop_back();
        size_t kezdet = sor.find_first_not_of(" \t");
        if (kezdet != string::npos) return sor.substr(kezdet);
    }
    return "";
}

void nevekKiir(const vector<string>& nevek) {
    cout << nevek.size() << "\n";
    for (size_t i = 0; i < nevek.size(); i++) {
        if (i > 0) cout << ' ';
        cout << nevek[i];
    }
    if (!nevek.empty()) cout << "\n";
}

int main() {
    int n, k;
    cin >> n >> k;

    int feladvany[MERET][MERET];
    for (int r = 0; r < MERET; r++) {
        for (int c = 0; c < MERET; c++) {
            cin >> feladvany[r][c];
        }
    }

    vector<Megfejtes> megfejtesek(n);
    for (Megfejtes& m : megfejtesek) {
        m.nev = nevetOlvas();
        for (int r = 0; r < MERET; r++) {
            for (int c = 0; c < MERET; c++) {
                cin >> m.mezo[r][c];
            }
        }
    }

    // 1. részfeladat: akiknek a megfejtés nem az e heti feladványra érkezett
    vector<string> nemHeti;
    for (const Megfejtes& m : megfejtesek) {
        if (!eHeti(m, feladvany)) nemHeti.push_back(m.nev);
    }
    cout << "#\n";
    nevekKiir(nemHeti);

    // 2. részfeladat: az e heti megfejtések közül hányban van a hajók száma K-tól eltérő
    int eltero = 0;
    for (const Megfejtes& m : megfejtesek) {
        if (eHeti(m, feladvany) && hajokSzama(m) != k) eltero++;
    }
    cout << "#\n" << eltero << "\n";

    // 3. részfeladat: a hajók száma K, de szomszédsági szabálysértés van
    int szabalytalan = 0;
    for (const Megfejtes& m : megfejtesek) {
        if (eHeti(m, feladvany) && hajokSzama(m) == k && szomszedsagiHiba(m)) szabalytalan++;
    }
    cout << "#\n" << szabalytalan << "\n";

    // 4. részfeladat: akik helyesen oldották meg a rejtvényt
    vector<string> helyesek;
    for (const Megfejtes& m : megfejtesek) {
        if (eHeti(m, feladvany) && hajokSzama(m) == k && !szomszedsagiHiba(m) &&
            toronySzamokOk(m, feladvany)) {
            helyesek.push_back(m.nev);
        }
    }
    cout << "#\n";
    nevekKiir(helyesek);

    return 0;
}
