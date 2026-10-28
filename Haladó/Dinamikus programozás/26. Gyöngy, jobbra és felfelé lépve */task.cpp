/*
Gyöngy, jobbra és lefelé lépve (a mappanévben tévesen: „jobbra és felfelé”)
Feladat: a bábu (1,1)-ből (M,N)-be megy jobbra és lefelé lépve, majd a bejárt mezők közül kiválaszt két
különbözőt; a pontszám a két mező gyöngyeinek összege. Ki kell írni a maximumot, a két mezőt a haladás
sorrendjében és egy megfelelő utat (L/J).
Ötlet: két különböző mező, p és q pontosan akkor lehet ugyanazon az úton, ha q p-től jobbra-lefelé van
(sor és oszlop sem kisebb). Ezért a válasz = max a[q] + (a legnagyobb érték q bal felső téglalapjában,
q-t kivéve). Ehhez prefix-maximumot számolunk: pm[i][j] = a legnagyobb érték az (1..i, 1..j) téglalapban,
a helyével együtt. A q = (i,j)-hez tartozó legjobb társ pm[i-1][j] és pm[i][j-1] közül a nagyobb (a két
téglalap együtt pontosan q nélküli bal felső téglalap). Az út: jobbra p oszlopáig, le q soráig, jobbra
az utolsó oszlopig, végül le; ez átmegy p-n és q-n is.
(A korábbi megoldás mezőnként csak a legjobb párt vitte tovább, ami hibás: 3×3-as táblán
0 0 15 / 10 10 0 / 0 0 14 esetén 24-et adott 29 helyett.)
Idő: O(M·N), memória: O(M·N).
*/
/*
Hint 1: || Mikor lehet két mező ugyanazon a jobbra-lefelé haladó úton? Fogalmazd meg a sor- és oszlopindexekkel! ||
Hint 2: || p és q (p előbb) pontosan akkor lehet egy úton, ha q sora és oszlopa sem kisebb p-énél. Rögzítsd a későbbi q mezőt: a legjobb társ a q bal felső téglalapjának legnagyobb eleme (q-t kivéve). ||
Hint 3: || Prefix-maximum: pm[i][j] = max(a[i][j], pm[i−1][j], pm[i][j−1]) a helyével együtt; q = (i,j) társa max(pm[i−1][j], pm[i][j−1]). Út: jobbra p oszlopáig, le q soráig, jobbra a végéig, le a végéig. O(M·N). ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // beolvasás: M sor, N oszlop
    int M, N;
    cin >> M >> N;
    vector<vector<int>> a(M + 1, vector<int>(N + 1));
    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= N; j++) cin >> a[i][j];

    // 1×1-es táblán nincs két különböző mező (a feladat szerint ilyen bemenet nem lehet)
    if (M == 1 && N == 1) {
        cout << a[1][1] << '\n';
        return 0;
    }

    // pm[i][j]: a legnagyobb érték az (1..i, 1..j) téglalapban, hely[i][j]: ennek egy helye.
    // A 0. sor és oszlop őrszem: -1 (minden érték >= 0), így a széleket nem kell külön kezelni.
    vector<vector<int>> pm(M + 1, vector<int>(N + 1, -1));
    vector<vector<pair<int, int>>> hely(M + 1, vector<pair<int, int>>(N + 1));

    int valasz = -1;
    pair<int, int> p, q;
    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= N; j++) {
            // (i,j) legjobb társa a bal felső téglalapjából, (i,j)-t kivéve
            int tars = max(pm[i - 1][j], pm[i][j - 1]);
            pair<int, int> tarsHely = (pm[i - 1][j] >= pm[i][j - 1]) ? hely[i - 1][j] : hely[i][j - 1];
            // egyenlőségnél a később talált párt tartjuk meg (így egyezik a mintakimenetekkel)
            if (tars >= 0 && a[i][j] + tars >= valasz) {
                valasz = a[i][j] + tars;
                p = tarsHely;
                q = {i, j};
            }
            // prefix-maximum frissítése (egyenlőségnél a korábban talált hely marad)
            pm[i][j] = a[i][j];
            hely[i][j] = {i, j};
            if (pm[i - 1][j] >= pm[i][j]) pm[i][j] = pm[i - 1][j], hely[i][j] = hely[i - 1][j];
            if (pm[i][j - 1] >= pm[i][j]) pm[i][j] = pm[i][j - 1], hely[i][j] = hely[i][j - 1];
        }

    // út: jobbra p oszlopáig, le q soráig, jobbra az utolsó oszlopig, végül le az utolsó sorig
    string ut = string(p.second - 1, 'J') + string(q.first - 1, 'L') +
                string(N - p.second, 'J') + string(M - q.first, 'L');

    cout << valasz << '\n';
    cout << p.first << ' ' << p.second << ' ' << q.first << ' ' << q.second << '\n';
    cout << ut << '\n';
    return 0;
}
