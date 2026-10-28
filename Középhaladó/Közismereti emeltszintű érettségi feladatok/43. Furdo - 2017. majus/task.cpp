/*
Megoldás lényege:
A bemeneti rekordokat vendégenként csoportosítjuk: az azonos kódú, egymás után következő sorok egy vendéget jelentenek.
Vendégenként gyűjtjük az öltözőből való kilépés és az öltözőbe való visszalépés idejét, valamint részlegenként a belépések számát és a ott töltött időt (belépés és kilépés különbsége).
A fürdőben töltött idő az öltözőből való kilépés és a visszalépés különbsége, és ebből minden részfeladat egyszerű számlálással vagy összegzéssel adódik.
Az időket másodpercre váltjuk, így az összehasonlítás és az összeadás egyszerű, a kiírásnál óra:perc:másodperc alakra visszabontjuk.
Az időigény O(N), ami a 0.1 mp-es korláton belül bőven marad.
*/
/*
Hint 1: || A lista vendégenként csoportosított, ezért egy vendég adatait a kódja változásáig gyűjtsd össze; a 0-s részleg az öltöző, ott a kilépés a fürdőbe lépést jelenti. ||
Hint 2: || Az időpontot másodpercre váltva kezeld: idő = óra·3600 + perc·60 + másodperc, és a kiíráskor ezt bontsd vissza óra:perc:másodperc alakra, a számjegyeket nullával nem kell kitölteni (pl. 6:30:0). ||
Hint 3: || Egy részlegen töltött idő a belépés és a hozzá tartozó kilépés különbsége; egy vendég többször is járhat ugyanott, ezért a statisztikában (6. részfeladat) vendégenként részlegenként csak egyszer számolj. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Rec {
    string code;
    int f;
    int dir;
    long long t;
};

struct Guest {
    string code;
    long long exitBath = -1;     // öltözőből való kilépés ideje (másodperc)
    long long enterChange = -1;  // öltözőbe való visszalépés ideje (másodperc)
    long long entries[5] = {0, 0, 0, 0, 0};
    long long spent[5] = {0, 0, 0, 0, 0};
};

string fmtHms(long long t) {
    return to_string(t / 3600) + ":" + to_string((t % 3600) / 60) + ":" + to_string(t % 60);
}

string fmtSpaced(long long t) {
    return to_string(t / 3600) + " " + to_string((t % 3600) / 60) + " " + to_string(t % 60);
}

int main() {
    int n;
    cin >> n;
    vector<Rec> recs(n);
    for (auto &r : recs) {
        int h, m, s;
        cin >> r.code >> r.f >> r.dir >> h >> m >> s;
        r.t = h * 3600LL + m * 60LL + s;
    }

    vector<Guest> guests;
    for (int i = 0; i < n;) {
        Guest g;
        g.code = recs[i].code;
        long long start[5] = {-1, -1, -1, -1, -1};
        int j = i;
        for (; j < n && recs[j].code == g.code; j++) {
            const Rec &r = recs[j];
            if (r.f == 0) {
                if (r.dir == 1) {
                    if (g.exitBath < 0) g.exitBath = r.t;
                } else {
                    g.enterChange = r.t;
                }
            } else if (r.dir == 0) {
                start[r.f] = r.t;
                g.entries[r.f]++;
            } else if (start[r.f] >= 0) {
                g.spent[r.f] += r.t - start[r.f];
                start[r.f] = -1;
            }
        }
        guests.push_back(g);
        i = j;
    }

    // 1. részfeladat: a lista első és utolsó vendégének öltözőből való kilépése
    cout << "#\n";
    cout << fmtSpaced(guests.front().exitBath) << "\n";
    cout << fmtSpaced(guests.back().exitBath) << "\n";

    // 2. részfeladat: egy részlegen, egyszer járt vendégek száma
    int single = 0;
    for (const Guest &g : guests) {
        int used = 0;
        long long visits = 0;
        for (int f = 1; f <= 4; f++) {
            if (g.entries[f] > 0) {
                used++;
                visits = g.entries[f];
            }
        }
        if (used == 1 && visits == 1) single++;
    }
    cout << "#\n" << single << "\n";

    // 3. részfeladat: az első vendég, aki a legtöbb időt töltötte a fürdőben
    int best = -1;
    long long bestT = -1;
    for (int i = 0; i < (int)guests.size(); i++) {
        long long bt = guests[i].enterChange - guests[i].exitBath;
        if (bt > bestT) {
            bestT = bt;
            best = i;
        }
    }
    cout << "#\n" << guests[best].code << " " << fmtHms(bestT) << "\n";

    // 4. részfeladat: érkezések száma a három idősávban
    long long band[3] = {0, 0, 0};
    for (const Guest &g : guests) {
        if (g.exitBath < 9 * 3600LL) band[0]++;
        else if (g.exitBath < 16 * 3600LL) band[1]++;
        else band[2]++;
    }
    cout << "#\n" << band[0] << " " << band[1] << " " << band[2] << "\n";

    // 5. részfeladat: a szaunában járt vendégek és a ott töltött idejük
    cout << "#\n";
    for (const Guest &g : guests)
        if (g.entries[2] > 0) cout << g.code << " " << fmtHms(g.spent[2]) << "\n";

    // 6. részfeladat: részlegenként hány vendég használta (öltözőn kívül)
    cout << "#\n";
    for (int f = 1; f <= 4; f++) {
        int c = 0;
        for (const Guest &g : guests)
            if (g.entries[f] > 0) c++;
        cout << f << " " << c << "\n";
    }
    return 0;
}
