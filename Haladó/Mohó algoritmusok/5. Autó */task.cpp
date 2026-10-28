/*
Feladat: Egy K km-es úton B liter benzinnel indulunk, a fogyasztás 100 km-enként L liter. Útközben N helyen
tankoltunk (a kút távolsága a kiindulástól Ti, a tankolt mennyiség Mi), a tankolások sorrendjében megadva.
Hány tankolás lett volna minimálisan elég ahhoz, hogy az autó eljusson a célig?

Értelmezés (a hivatalos tesztek alapján): a tankolásokat a megadott sorrendben vesszük igénybe, tehát az
első j tankolást tartjuk meg, és a legkisebb olyan j a válasz, amellyel az autó minden kúthoz és a célig is
eljut. (Ha a kutakat szabadon válogathatnánk, a 2. minta válasza 455 lenne, a tesztek viszont 466-ot várnak,
ami pontosan ennek az értelmezésnek felel meg. A feladat példájára mindkét értelmezés 2-t ad.)

Ötlet (mohó szimuláció): sorban haladunk a kutakon, végül a célon. Ha a benzin nem elég a következő pontig,
akkor a még fel nem használt tankolások közül a legkorábbit (a következőt a sorban) is felhasználjuk, és ezt
addig ismételjük, amíg elég nem lesz. Ha egy rövidebb előtag elég lenne, akkor egyszer sem akadnánk el úgy,
hogy a következő tankolásra szükség legyen, ezért a felhasznált tankolások száma pontosan a legkisebb jó j.
Benzin helyett "liter*100" egységben számolunk, így a d km megtételéhez d*L egység kell, nincs tört.
Lépésszám: O(N).
*/
/*
Hint 1: || A benzint számold liter*100 egységben: így d km megtételéhez pontosan d*L egység kell, nem lesz tört szám. ||
Hint 2: || Haladj sorban a kutakon és végül a célon. Ha a meglévő benzin nem elég a következő pontig, vond be a következő még fel nem használt tankolást. ||
Hint 3: || A tankolásokat csak a megadott sorrendben lehet bevonni, és csak olyat, amelynek a kútjához már eljutottál. Ha ez is kevés, az út nem tehető meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    // beolvasás
    int k, n, b, l;
    cin >> k >> n >> b >> l;
    vector<int> t(n), m(n);
    for (int i = 0; i < n; i++) cin >> t[i] >> m[i];

    // a megállási pontok: a K-nál nem távolabbi kutak, végül maga a cél
    vector<int> pont;
    for (int i = 0; i < n && t[i] <= k; i++) pont.push_back(t[i]);
    int kutak = (int)pont.size();
    pont.push_back(k);

    long long benzin = (long long)b * 100;  // eddig összesen kapott benzin, liter*100 egységben
    int felhasznalt = 0;                    // az első ennyi tankolást használjuk fel
    for (int i = 0; i <= kutak; i++) {
        // a pont[i]-ig összesen pont[i]*L egység kell; ha kevés, jöhet a következő tankolás
        while (benzin < (long long)pont[i] * l) {
            if (felhasznalt >= i) {  // csak már elért kútnál lehet tankolni
                cout << -1 << '\n';  // nem lehet eljutni (a feladat szerint nem fordul elő)
                return 0;
            }
            benzin += (long long)m[felhasznalt] * 100;
            felhasznalt++;
        }
    }

    // kiírás
    cout << felhasznalt << '\n';
    return 0;
}
