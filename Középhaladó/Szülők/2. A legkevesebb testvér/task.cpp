/*
Megoldás ötlete:
Minden emberhez eltároljuk, kik a szülei, és minden szülőhöz, kik a gyerekei.
Egy ember testvérei azok a különböző emberek, akik vele legalább egy szülőt
megosztanak, ezért elég a saját szüleihez tartozó gyereklistákat bejárni.
Minden embernél egy jelölő tömbbel megszámoljuk a különböző másik gyerekeket,
így a féltestvérek is beleszámítanak, de az illető saját magát kihagyjuk.
A pozitív testvérszámok közül a legkisebbet keressük, holtversenyben a kisebb
sorszám marad meg, mert növekvő sorrendben járjuk be az embereket.
*/
/*
Hint 1: || Készíts két listát: szulok[ember] és gyerekek[szulo]. A bemeneti pár
          beolvasásakor mindkettőt töltsd. ||
Hint 2: || Egy ember testvérszáma úgy számolható, hogy minden szülőjének
          gyerekei közül megjelölöd a még nem látott, tőle különböző embereket. ||
Hint 3: || Az eredményhez csak azokat az embereket nézd, akiknek a testvérszáma
          legalább 1; a minimumot strict kisebb esetén frissítsd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<vector<int>> szulok(n + 1), gyerekek(n + 1);
    for (int i = 0; i < k; ++i) {
        int szulo, gyerek;
        cin >> szulo >> gyerek;
        gyerekek[szulo].push_back(gyerek);
        szulok[gyerek].push_back(szulo);
    }

    int legkisebb = INT_MAX;
    int valasz = -1;

    for (int ember = 1; ember <= n; ++ember) {
        vector<char> latott(n + 1, false);
        int testverek = 0;

        for (int szulo : szulok[ember]) {
            for (int masik : gyerekek[szulo]) {
                if (masik != ember && !latott[masik]) {
                    latott[masik] = true;
                    ++testverek;
                }
            }
        }

        if (testverek > 0 && testverek < legkisebb) {
            legkisebb = testverek;
            valasz = ember;
        }
    }

    cout << valasz << '\n';
    return 0;
}
