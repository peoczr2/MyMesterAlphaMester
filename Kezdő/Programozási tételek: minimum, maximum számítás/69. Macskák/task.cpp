/*
Megoldás lényege:
Ha K-t változtatjuk, a rosszul besorolt házimacskák száma a K-nál nem kisebb házimacskák száma, a rosszul besorolt vadmacskák száma pedig a K-nál kisebb vadmacskák száma lesz. Az első érték csökken, a második nő K növelésével, ezért a két érték maximumának minimuma a lehetséges K-k között keresendő. A méretek előfordulási gyakoriságát tömbben tárolva, a K-nál kisebb darabszámokat növekvő K-val egy bejárásban frissítjük, így minden K értéket O(1) lépésben kiértékelünk. Ha több K is ugyanazt a minimumot adja, a bejárás során a nagyobbat írjuk felül. Az időigény O(MAXM + H + V).
*/
/*
Hint 1: || Egy K-t vizsgálva két hibaszám van: a K-nál nagyobb-egyenlő házimacskák és a K-nál kisebb vadmacskák száma. K változtatásakor az egyik csökken, a másik nő. ||
Hint 2: || Ha minden K-ra külön végigszámolnád a két értéket, az túl lassú lenne. A méretek előfordulási gyakoriságából prefix számlálóval egy lépésben megkapod mindkettőt, így K-t 1-től 100 000-ig végigpróbálhatod. ||
Hint 3: || A két érték maximumának minimumát keresed, és ha több K is ugyanazt a minimumot adja, a legnagyobbat kell kiírni. Az egyenlőséget is elfogadó összehasonlítással a bejárás során a későbbi, nagyobb K írja felül a korábbit. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    const int MAXM = 100000;

    int h;
    cin >> h;
    vector<int> hazi(h);
    for (auto &x : hazi) cin >> x;

    int v;
    cin >> v;
    vector<int> vad(v);
    for (auto &x : vad) cin >> x;

    vector<int> dbHazi(MAXM + 2, 0), dbVad(MAXM + 2, 0);
    for (int x : hazi) dbHazi[x]++;
    for (int x : vad) dbVad[x]++;

    // kisebbHazi: az aktuális K-nál kisebb házimacskák száma, kisebbVad: a K-nál kisebb vadmacskák száma
    int kisebbHazi = 0, kisebbVad = 0;
    int legjobb = INT_MAX, legjobbK = 1;
    for (int k = 1; k <= MAXM; k++) {
        int rosszHazi = h - kisebbHazi;  // K-nál nem kisebb házimacskák
        int rosszVad = kisebbVad;        // K-nál kisebb vadmacskák
        int rossz = max(rosszHazi, rosszVad);
        if (rossz <= legjobb) {
            legjobb = rossz;
            legjobbK = k;
        }
        kisebbHazi += dbHazi[k];
        kisebbVad += dbVad[k];
    }
    cout << legjobbK << "\n";
    return 0;
}
