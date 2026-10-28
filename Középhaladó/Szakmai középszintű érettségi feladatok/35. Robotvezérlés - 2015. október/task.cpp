/*
Megoldás lényege:
A robot mozgását koordinátákkal követjük: E az (0, 1), H az (0, -1), J az (1, 0), B az (-1, 0) irányú egységnyi elmozdulás. Az első részfeladatban azokat a kódsorozatokat számoljuk meg, amelyekben a négy megengedett betűn kívül más karakter is van. A hibátlan kódsorozatoknál az irányváltások száma a szomszédos, egymástól különböző karakterpárok száma. A harmadik részfeladatban minden hibátlan sorozat bejárása közben nyilvántartjuk a kiindulási ponttól mért legnagyobb négyzetes távolságot (x^2 + y^2), ami az euklideszi távolság összehasonlításához elegendő. A legnagyobb távolságú tanulók nevét a bemenet sorrendjében írjuk ki. Az időigény O(N * L), ahol L a kódsorozatok legnagyobb hossza, a memóriaigény O(N).
*/
/*
Hint 1: || Minden betűhöz tartozik egy elmozdulás: az E és a H a függőleges tengelyen mozdít, a J és a B a vízszintesen. Kezdd a robotot az (0, 0) pontból, és minden karakter után frissítsd a koordinátákat. ||
Hint 2: || Az irányváltásnál elég a kódsorozat minden karakterét az előzővel összehasonlítani: ha a két szomszédos betű különbözik, az irányváltások száma eggyel nő. Az érvénytelen karaktert tartalmazó sorozatokat az első részfeladatban már kiszűrtük, a többi részfeladatban őket nem kell figyelembe venni. ||
Hint 3: || Az euklideszi távolság összehasonlításához nem kell gyököt vonni: a négyzetösszeg ugyanabban a sorrendben nő, mint a távolság. Az egyes sorozatokra a bejárás közben tartsd nyilván a legnagyobb értéket, és a végén írd ki a neveket, amelyeknél ez a legnagyobb érték szerepel. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Igaz, ha a kódsorozat csak E, B, J, H betűket tartalmaz
bool hibatlan(const string& kod) {
    for (char c : kod) {
        if (c != 'E' && c != 'B' && c != 'J' && c != 'H') return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> nevek(n), kodok(n);
    for (int i = 0; i < n; i++) {
        cin >> nevek[i] >> kodok[i];
    }

    // 1. részfeladat: az érvénytelen karaktert tartalmazó kódsorozatok száma
    int hibasDarab = 0;
    for (int i = 0; i < n; i++) {
        if (!hibatlan(kodok[i])) hibasDarab++;
    }
    cout << "#\n";
    cout << hibasDarab << "\n";

    // A hibátlan sorozatok irányváltásai és legnagyobb távolságai
    vector<int> valtasok(n, 0);
    vector<long long> tavolsag(n, 0);
    for (int i = 0; i < n; i++) {
        const string& kod = kodok[i];
        if (!hibatlan(kod)) continue;

        long long x = 0, y = 0, legtavolabb = 0;
        int valtas = 0;
        for (size_t j = 0; j < kod.size(); j++) {
            if (j > 0 && kod[j] != kod[j - 1]) valtas++;

            if (kod[j] == 'E') y++;
            else if (kod[j] == 'H') y--;
            else if (kod[j] == 'J') x++;
            else x--;

            legtavolabb = max(legtavolabb, x * x + y * y);
        }
        valtasok[i] = valtas;
        tavolsag[i] = legtavolabb;
    }

    // 2. részfeladat: a hibátlan sorozatok neve és irányváltásainak száma
    cout << "#\n";
    for (int i = 0; i < n; i++) {
        if (hibatlan(kodok[i])) cout << nevek[i] << " " << valtasok[i] << "\n";
    }

    // 3. részfeladat: a kiindulási ponttól legmesszebbre jutó tanulók
    long long legnagyobb = -1;
    for (int i = 0; i < n; i++) {
        if (hibatlan(kodok[i])) legnagyobb = max(legnagyobb, tavolsag[i]);
    }
    cout << "#\n";
    bool elso = true;
    for (int i = 0; i < n; i++) {
        if (hibatlan(kodok[i]) && tavolsag[i] == legnagyobb) {
            if (!elso) cout << " ";
            cout << nevek[i];
            elso = false;
        }
    }
    cout << "\n";

    return 0;
}
