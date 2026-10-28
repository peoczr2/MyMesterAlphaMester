/*
Megoldás lényege:
A Gazdagsor telkei adottak, a Jólétsor telkeinek hossza viszont a szemben fekvő telkekből számolható ki: a két utca 80 m-re van egymástól, ebből a telkek között legalább 10 m marad, így a szemben álló telkek hosszának összege legfeljebb 70 m lehet.
A telkek az utca elejétől a házszám szerinti sorrendben, egymás után helyezkednek el, így egy telek kezdőpontja az előtte lévő telkek szélességeinek összege.
Két telek akkor áll szemben, ha a kezdő- és végpontjaik által meghatározott zárt intervallumaik metszik egymást, ezt N <= 100 mellett egyszerű páros ellenőrzéssel vizsgáljuk.
Az adót telkenként számoljuk: az első 700 m²-re 51, 700 és 1000 m² között 39 Fabatka jár négyzetméterenként, 1000 m² fölött csak 200 Fabatka átalány, majd a 20%-os kedvezmény és a 100-as kerekítés után összegezünk.
A körbejárás hossza az utcák összes szélességének kétszerese, plusz a két híd 2 * 80 m-e.
*/
/*
Hint 1: || Az utcák 80 m-re vannak egymástól, és a szemben lévő határvonalak között legalább 10 m marad, így két szemben lévő telek hosszának összege legfeljebb 70 m. A Jólétsor telkének hossza tehát 70 mínusz a vele szemben fekvő Gazdagsor-telkek hosszának maximuma. ||
Hint 2: || Számold ki az utca elejétől mért kezdőpontokat: egy telek kezdete az előtte lévő telkek szélességeinek összege. Két telek akkor áll szemben, ha az intervallumaik metszik egymást, és az érintkező szélek is számítanak. ||
Hint 3: || Az adónál az első 700 m²-re 51, a 700 és 1000 m² közötti részre 39 Fabatka jár négyzetméterenként, az 1000 m² feletti részért csak 200 Fabatka az átalány. A kedvezmény utáni összeget kerekítsd 100-zal, és csak utána összegezz. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Egy telek adója Fabatkában, 100-as kerekítéssel
long long ado(long long terulet, long long szeles, long long hosszu) {
    long long alap;
    if (terulet <= 700) alap = 51 * terulet;
    else if (terulet <= 1000) alap = 51 * 700 + 39 * (terulet - 700);
    else alap = 51 * 700 + 39 * 300 + 200;
    bool kedvezmeny = (szeles <= 15) || (hosszu <= 25);
    // alap * 4/5 (kedvezménnyel) vagy alap * 5/5, majd a legközelebbi 100-as többszörösre kerekítve
    long long x = alap * (kedvezmeny ? 4 : 5);
    return (x + 250) / 500 * 100;
}

int main() {
    int n;
    cin >> n;
    int m = n / 2;  // telkek száma utcánként
    vector<int> szel(n + 1, 0), hossz(n + 1, 0);
    for (int i = 0; i < n; i++) {
        int h, sz, hs;
        cin >> h >> sz >> hs;
        szel[h] = sz;
        hossz[h] = hs;
    }

    // Gazdagsor: 2k-1, Jólétsor: 2k házszámú telkek, k = 1..m
    vector<long long> gSzel(m + 1), gHossz(m + 1), gA(m + 1), gB(m + 1);
    vector<long long> jSzel(m + 1), jHossz(m + 1), jA(m + 1), jB(m + 1);
    for (int k = 1; k <= m; k++) {
        gSzel[k] = szel[2 * k - 1];
        gHossz[k] = hossz[2 * k - 1];
        jSzel[k] = szel[2 * k];
    }
    long long s = 0;
    for (int k = 1; k <= m; k++) {
        gA[k] = s;
        s += gSzel[k];
        gB[k] = s;
    }
    long long gossz = s;
    s = 0;
    for (int k = 1; k <= m; k++) {
        jA[k] = s;
        s += jSzel[k];
        jB[k] = s;
    }
    long long jossz = s;

    // A Jólétsor telkeinek hossza: 70 mínusz a szemben lévő Gazdagsor-telkek legnagyobb hossza
    for (int k = 1; k <= m; k++) {
        long long maxG = 0;
        for (int g = 1; g <= m; g++)
            if (gA[g] <= jB[k] && jA[k] <= gB[g]) maxG = max(maxG, gHossz[g]);
        jHossz[k] = 70 - maxG;
    }

    // 1. részfeladat: körbejárás a két utca körül
    cout << "#\n";
    cout << gossz + jossz + 160 << "\n";

    // 2. részfeladat: Jólétsor, legfeljebb 20 m széles telkek
    int keskeny = 0;
    for (int k = 1; k <= m; k++)
        if (jSzel[k] <= 20) keskeny++;
    cout << "#\n";
    cout << keskeny << "\n";

    // 3. részfeladat: Gazdagsor legnagyobb és legkisebb területű telke
    int kmax = 1, kmin = 1;
    for (int k = 2; k <= m; k++) {
        if (gSzel[k] * gHossz[k] > gSzel[kmax] * gHossz[kmax]) kmax = k;
        if (gSzel[k] * gHossz[k] < gSzel[kmin] * gHossz[kmin]) kmin = k;
    }
    long long amax = gSzel[kmax] * gHossz[kmax];
    long long amin = gSzel[kmin] * gHossz[kmin];
    int koztes = max(0, abs(kmax - kmin) - 1);
    cout << "#\n";
    cout << koztes << " " << 2 * kmax - 1 << " " << 2 * kmin - 1 << " " << amax << " " << amin << "\n";

    // 4. részfeladat: adóbevétel a Gazdagsor után
    long long adobevetel = 0;
    for (int k = 1; k <= m; k++)
        adobevetel += ado(gSzel[k] * gHossz[k], gSzel[k], gHossz[k]);
    cout << "#\n";
    cout << adobevetel << "\n";

    // 5. részfeladat: a Jólétsor utolsó három telke, házszám és kezdőpont szerint csökkenő sorrendben
    cout << "#\n";
    if (m < 3) {
        cout << -1 << "\n";
    } else {
        for (int k = m; k >= m - 2; k--) cout << 2 * k << " " << jA[k] << "\n";
    }

    // 6. részfeladat: a Jólétsor telkeinek adatai
    cout << "#\n";
    for (int k = 1; k <= m; k++)
        cout << 2 * k << ";" << jSzel[k] << ";" << jHossz[k] << "\n";

    return 0;
}
