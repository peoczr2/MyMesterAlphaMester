/*
Gyöngy, jobbra, lefelé és felfelé lépve
Feladat: M×N-es táblán a bal felső sarokból a jobb alsóba kell eljutni jobbra / lefelé / felfelé
lépésekkel, csapdára és már érintett mezőre nem léphetünk. A csapdák és a gyöngyös mezők listaként
érkeznek (a többi mező üres). Ki kell írni a maximális gyöngyszámot és egy ilyen lépéssort (J/L/F).
Ötlet: a ritka bemenetből előbb teljes táblát építünk (-1 = csapda). Balra nem léphetünk, mezőt sem
ismételhetünk, ezért egy oszlopon belül az út egyetlen függőleges szakasz: balról belépünk valamelyik
sorba, egyenesen le- vagy felmegyünk, majd jobbra kilépünk. Oszloponként haladunk: legjobb[r] = a legtöbb
gyöngy, ha az aktuális oszlop r. sorában állunk, és innen lépünk jobbra. Ezt az előző oszlopból egy lefelé
és egy felfelé söpréssel kapjuk, és minden mezőre eltároljuk, melyik sorban léptünk be az oszlopba;
ebből visszafejthető az út.
A feladat nem garantálja, hogy a cél elérhető (a csapdák elzárhatják, akár a kezdőmező is csapda lehet);
ilyenkor -1-et írunk ki. A kimenet betűit a mintafájlokhoz igazodva szóköz nélkül írjuk.
Idő: O(M·N + U + V), memória: O(M·N).
*/
/*
Hint 1: || Balra nem léphetsz, és mezőre sem léphetsz kétszer. Mit csinálhat a bábu egy oszlopon belül? Megfordulhat-e benne? ||
Hint 2: || Készíts a listákból teljes táblát (csapda: -1, gyöngy: Z, egyébként 0). Egy oszlopba a bábu balról lép be valamelyik sorban, onnan egyenesen lefelé vagy egyenesen felfelé megy, aztán jobbra kilép: best[r] = a legjobb érték, ha az aktuális oszlop r. sorában áll, és innen lép jobbra. ||
Hint 3: || Oszloponként két söprés: lefelé down[r] = a[r][c] + max(prev[r], down[r−1]), felfelé up[r] = a[r][c] + max(prev[r], up[r+1]), majd best[r] = max(down[r], up[r]), csapdán −∞. Az út kiírásához tárold, melyik sorban lépett be a bábu az oszlopba. O(M·N). ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // beolvasás: n sor, m oszlop, u csapda, v gyöngyös mező; teljes táblát építünk (-1 = csapda)
    int n, m, u, v;
    cin >> n >> m >> u >> v;
    vector<vector<int>> a(n, vector<int>(m, 0));
    for (int i = 0; i < u; i++) {
        int x, y;
        cin >> x >> y;
        a[x - 1][y - 1] = -1;
    }
    for (int i = 0; i < v; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        if (a[x - 1][y - 1] != -1) a[x - 1][y - 1] = z;  // csapdára nem írunk gyöngyöt
    }

    // -∞: ide nem lehet eljutni. long long a biztonság kedvéért (10^6 mező · akár 10^3 gyöngy)
    const long long NINCS = LLONG_MIN / 4;

    // belep[c][r]: ha a c. oszlop r. sorában állunk, melyik sorban léptünk be ebbe az oszlopba
    vector<vector<int>> belep(m, vector<int>(n, 0));
    vector<long long> elozo(n), le(n), fel(n), legjobb(n);
    vector<int> beLe(n), beFel(n);

    // 1. oszlop: (0,0)-ból csak lefelé mehetünk, az első csapdáig (ha (0,0) csapda, semmi sem érhető el)
    long long osszeg = 0;
    for (int r = 0; r < n; r++) {
        if (osszeg == NINCS || a[r][0] == -1) osszeg = NINCS;
        else osszeg += a[r][0];
        elozo[r] = osszeg;
    }

    for (int c = 1; c < m; c++) {
        // lefelé söprés: (r,c)-be vagy balról lépünk be, vagy a fölötte levő mezőről jövünk
        for (int r = 0; r < n; r++) {
            le[r] = NINCS;
            if (a[r][c] == -1) continue;
            if (elozo[r] != NINCS) {
                le[r] = elozo[r] + a[r][c];
                beLe[r] = r;
            }
            if (r > 0 && le[r - 1] != NINCS && le[r - 1] + a[r][c] > le[r]) {
                le[r] = le[r - 1] + a[r][c];
                beLe[r] = beLe[r - 1];
            }
        }
        // felfelé söprés: ugyanez, csak alulról jövünk
        for (int r = n - 1; r >= 0; r--) {
            fel[r] = NINCS;
            if (a[r][c] == -1) continue;
            if (elozo[r] != NINCS) {
                fel[r] = elozo[r] + a[r][c];
                beFel[r] = r;
            }
            if (r < n - 1 && fel[r + 1] != NINCS && fel[r + 1] + a[r][c] > fel[r]) {
                fel[r] = fel[r + 1] + a[r][c];
                beFel[r] = beFel[r + 1];
            }
        }
        // a két irány közül a jobbat tartjuk meg
        for (int r = 0; r < n; r++) {
            if (le[r] >= fel[r]) {
                legjobb[r] = le[r];
                belep[c][r] = beLe[r];
            } else {
                legjobb[r] = fel[r];
                belep[c][r] = beFel[r];
            }
        }
        swap(elozo, legjobb);
    }

    // a cél nem érhető el (a csapdák elzárják, vagy a kezdő- / célmező csapda): -1
    if (elozo[n - 1] == NINCS) {
        cout << -1 << '\n';
        return 0;
    }

    // visszafejtés: kisor[c] = az a sor, ahol a c. oszlopot elhagyjuk (az utolsóban: a cél sora)
    vector<int> kisor(m);
    kisor[m - 1] = n - 1;
    for (int c = m - 1; c >= 1; c--) kisor[c - 1] = belep[c][kisor[c]];

    string ut(kisor[0], 'L');  // az 1. oszlopban lefelé a kilépési sorig
    for (int c = 1; c < m; c++) {
        ut += 'J';
        int honnan = kisor[c - 1], hova = kisor[c];
        if (hova > honnan) ut += string(hova - honnan, 'L');
        else ut += string(honnan - hova, 'F');
    }

    cout << elozo[n - 1] << '\n' << ut << '\n';
    return 0;
}
