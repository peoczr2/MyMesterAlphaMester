/*
Megoldás lényege:
Az időpontokat percre váltjuk (óra * 60 + perc), majd a vizsgázókat a kezdési idő szerint rendezzük.
A) A 60 perces ablak kezdete mindig valamelyik befejezési időpont lehet (az első vizsgázó pontosan
ekkor végez). Minden befejezési időpontra megszámoljuk, hány befejezés esik a [t, t+59] percekre, és
a legtöbbet adó (legkorábbi) t-t írjuk ki. B) A leghosszabb szünet a rendezett vizsgák közötti
legnagyobb „következő kezdés − előző befejezés” különbség. C) A foglalt időszakok összevonásával
(az egymást érintő vizsgák egy foglalt blokkot alkotnak) a leghosszabb összefüggő blokk hossza adja
a választ. Mivel N legfeljebb 100, a páronkénti számlálás is gyorsan lefut.
*/
/*
Hint 1: || Először minden időt alakíts át percre (óra * 60 + perc), így a kivonás és az összehasonlítás egyszerű. Az ablak kezdete biztosan valamelyik befejezési időpont, így csak ezeket kell kipróbálni. ||
Hint 2: || A szünet kérdésénél csak a vizsgák közötti rések számítanak: egy vizsga befejezése és a következő kezdése közötti különbség. Ha két vizsga egymásba ér (a kezdés nem későbbi, mint az előző befejezés), a bizottság nem tarthat szünetet, így ezek egy összefüggő foglalt blokkba tartoznak. ||
Hint 3: || Végigmenve a rendezett vizsgákon tartsd nyilván az aktuális foglalt blokk kezdetét és végét: ha a következő vizsga kezdete még a blokk végéig tart, nyújtsd a blokkot, különben zárd le és kezdj újat. A kiírás előtt a percek számát vissza kell alakítani órára és percre. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<int, int>> vizsga(n);   // (kezdés, befejezés) percben
    for (auto &[kezd, vege] : vizsga) {
        int oraK, percK, oraV, percV;
        cin >> oraK >> percK >> oraV >> percV;
        kezd = oraK * 60 + percK;
        vege = oraV * 60 + percV;
    }
    sort(vizsga.begin(), vizsga.end());

    // A) 60 perces ablak: a legtöbb befejezést tartalmazó, befejezéssel kezdődő ablak
    vector<int> befejezesek;
    for (auto &[kezd, vege] : vizsga) befejezesek.push_back(vege);
    sort(befejezesek.begin(), befejezesek.end());

    int legtobbDb = -1, legjobbKezd = 0;
    for (int t : befejezesek) {
        int db = 0;
        for (int v : befejezesek)
            if (v >= t && v <= t + 59) db++;
        if (db > legtobbDb) {
            legtobbDb = db;
            legjobbKezd = t;
        }
    }

    // B) leghosszabb szünet két vizsga között
    int legnagyobbSzunet = 0;
    for (int i = 0; i + 1 < n; i++) {
        legnagyobbSzunet = max(legnagyobbSzunet, vizsga[i + 1].first - vizsga[i].second);
    }

    // C) leghosszabb összefüggő foglalt időszak (az érintkező vizsgák összevonva)
    int legnagyobbFoglalt = 0;
    int blokkKezd = vizsga[0].first, blokkVege = vizsga[0].second;
    for (int i = 1; i < n; i++) {
        if (vizsga[i].first <= blokkVege) {
            blokkVege = max(blokkVege, vizsga[i].second);
        } else {
            legnagyobbFoglalt = max(legnagyobbFoglalt, blokkVege - blokkKezd);
            blokkKezd = vizsga[i].first;
            blokkVege = vizsga[i].second;
        }
    }
    legnagyobbFoglalt = max(legnagyobbFoglalt, blokkVege - blokkKezd);

    cout << legjobbKezd / 60 << ' ' << legjobbKezd % 60 << '\n';
    cout << legnagyobbSzunet / 60 << ' ' << legnagyobbSzunet % 60 << '\n';
    cout << legnagyobbFoglalt / 60 << ' ' << legnagyobbFoglalt % 60 << '\n';
    return 0;
}
