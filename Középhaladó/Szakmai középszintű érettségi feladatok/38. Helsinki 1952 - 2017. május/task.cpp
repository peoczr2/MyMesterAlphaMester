/*
Megoldás lényege:
A helyezések N sorát egy menetben olvassuk be, és soronként frissítjük a számlálókat. Az 1–6. helyezés pontot ér: a pontot egy táblázatból (tömbből) vesszük, a többi helyezés nulla pontot ér. Az 1., 2. és 3. helyezés érmet jelent, egy csapat egy érmet kap, függetlenül a létszámától, ezért az arany, ezüst és bronz számlálóit soronként egyszer növeljük. Az uszas és a torna sportágban szerzett érmeket külön számláljuk, és a két szám összehasonlításával döntünk az 4. részfeladatról. A legnagyobb létszámot az első menetben határozzuk meg, a 5. részfeladat sorait pedig a bemenet sorrendjében, második menetben írjuk ki. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || A helyezésből két dolgot kell meghatároznod: a pontot, amelyet 1–6 közötti helyezésért kapsz, és az érmet, amelyet az 1., 2. és 3. helyezés ad. Egy sor egy csapat eredménye, így a csapat létszámától függetlenül csak egy érmet számolsz. ||
Hint 2: || A második részfeladathoz három számlálót tarts, és csak akkor növeld őket, ha a helyezés 1, 2 vagy 3. A negyedik részfeladatban ugyanezt a szűrést alkalmazd az uszas és a torna sportágra, és a két számláló összehasonlításával döntsd el a kimenetet. ||
Hint 3: || Az utolsó részfeladatban először határozd meg a legnagyobb létszámot, majd a bemenet sorait másodszor bejárva írd ki azokat, amelyek létszáma ezzel egyenlő. Ehhez a sorokat tárold el vektorokban, így a második bejárás a bemenet sorrendjét adja. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> helyezes(n), letszam(n);
    vector<string> sportag(n), versenyszam(n);
    for (int i = 0; i < n; i++) {
        cin >> helyezes[i] >> letszam[i] >> sportag[i] >> versenyszam[i];
    }

    // Olimpiai pontok helyezésenként: 1. hely 7 pont, ..., 6. hely 1 pont, a többi 0
    const int pont[] = {0, 7, 5, 4, 3, 2, 1};

    int pontszerzoDb = 0;
    long long osszPont = 0;
    int arany = 0, ezust = 0, bronz = 0;
    int uszasErem = 0, tornaErem = 0;
    int legnagyobbLetszam = 0;

    for (int i = 0; i < n; i++) {
        int h = helyezes[i];

        if (h <= 6) {
            pontszerzoDb++;
            osszPont += pont[h];
        }

        if (h == 1) arany++;
        else if (h == 2) ezust++;
        else if (h == 3) bronz++;

        if (h <= 3) {
            if (sportag[i] == "uszas") uszasErem++;
            if (sportag[i] == "torna") tornaErem++;
        }

        legnagyobbLetszam = max(legnagyobbLetszam, letszam[i]);
    }

    // 1. részfeladat: a pontszerző helyezések száma
    cout << "#\n";
    cout << pontszerzoDb << "\n";

    // 2. részfeladat: az arany, ezüst és bronzérmek száma
    cout << "#\n";
    cout << arany << " " << ezust << " " << bronz << "\n";

    // 3. részfeladat: az elért olimpiai pontok összege
    cout << "#\n";
    cout << osszPont << "\n";

    // 4. részfeladat: az uszas vagy a torna sportágban több érem született
    cout << "#\n";
    if (uszasErem > tornaErem) cout << "uszas\n";
    else if (tornaErem > uszasErem) cout << "torna\n";
    else cout << "egyenlo\n";

    // 5. részfeladat: a legnagyobb létszámú csapatok helyezése, létszáma, sportága és versenyszáma
    cout << "#\n";
    for (int i = 0; i < n; i++) {
        if (letszam[i] == legnagyobbLetszam) {
            cout << helyezes[i] << " " << letszam[i] << " " << sportag[i] << " " << versenyszam[i] << "\n";
        }
    }

    return 0;
}
