/*
Megoldás lényege:
Minden tanulót az első előfordulása sorrendjében számozunk, és tárolunk egy logikai tömböt arról, hogy melyik sportágra nevezett. Ebből egyszerűen megkapjuk a Nev nevű tanuló nevezéseinek számát, a sportágankénti létszámot, a legtöbb sportágban nevezett tanulót és a pontosan egy sportágra nevezett tanulót.
Két sportág akkor rendezhető egyszerre, ha mindkettőre van nevezés, és nincs olyan tanuló, aki mindkettőre nevezett. Ezt minden (a, b) párra, a < b feltétellel ellenőrizzük, így a párok már lexikografikus sorrendben kerülnek kiírásra. Az időigény O(S^2 * N), ami a kis korlátok miatt bőven belefér.
*/
/*
Hint 1: || Minden tanulóhoz tárold, hogy melyik sportágakra nevezett (például egy logikai tömbben, amelynek mérete S+1). A tanulókat az első előfordulásuk sorrendjében érdemes nyilvántartani. ||
Hint 2: || A nevezések száma és a sportágankénti létszám egyszerű számlálás a tárolt tömbökből. Egy tanuló ugyanarra a sportágra csak egyszer nevezhet, így a számlálás nem tartalmaz duplát. ||
Hint 3: || Egy (a, b) sportágpárt akkor írj ki, ha mindkettőre nevezett valaki, és nincs olyan tanuló, aki mindkettőre nevezett. Két egymásba ágyazott ciklussal, a < b feltétellel végigmehetsz az összes páron. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int S, N;
    cin >> S >> N;

    map<string, int> azonosito;     // tanuló neve -> sorszám (első előfordulás sorrendjében)
    vector<string> nevek;
    vector<vector<bool>> nevezett;  // nevezett[t][s]: a t. tanuló nevezett-e az s. sportágra

    for (int i = 0; i < N; i++) {
        string nev;
        int x;
        cin >> nev >> x;
        if (!azonosito.count(nev)) {
            azonosito[nev] = nevek.size();
            nevek.push_back(nev);
            nevezett.push_back(vector<bool>(S + 1, false));
        }
        nevezett[azonosito[nev]][x] = true;
    }

    string kerdes;
    cin >> kerdes;

    int T = nevek.size();
    vector<int> nevezesekSzama(T, 0);
    vector<int> letszam(S + 1, 0);
    for (int t = 0; t < T; t++)
        for (int s = 1; s <= S; s++)
            if (nevezett[t][s]) {
                nevezesekSzama[t]++;
                letszam[s]++;
            }

    // 1. részfeladat: a Nev nevű tanuló nevezéseinek száma
    cout << "#\n";
    int darab = 0;
    if (azonosito.count(kerdes)) darab = nevezesekSzama[azonosito[kerdes]];
    cout << darab << "\n";

    // 2. részfeladat: egy tanuló, aki pontosan egy sportágra nevezett
    cout << "#\n";
    int egySportag = -1;
    for (int t = 0; t < T; t++)
        if (nevezesekSzama[t] == 1) {
            egySportag = t;
            break;
        }
    if (egySportag >= 0) cout << nevek[egySportag] << "\n";
    else cout << "\n";

    // 3. részfeladat: a legtöbb sportágban nevezett tanuló
    cout << "#\n";
    int legtobb = 0;
    for (int t = 1; t < T; t++)
        if (nevezesekSzama[t] > nevezesekSzama[legtobb]) legtobb = t;
    cout << nevek[legtobb] << "\n";

    // 4. részfeladat: sportáganként a nevezettek száma
    cout << "#\n";
    for (int s = 1; s <= S; s++)
        cout << letszam[s] << (s < S ? " " : "\n");

    // 5. részfeladat: egyidőben rendezhető sportág-párok (üres sportágak nélkül)
    cout << "#\n";
    for (int a = 1; a <= S; a++)
        for (int b = a + 1; b <= S; b++) {
            if (letszam[a] == 0 || letszam[b] == 0) continue;
            bool kozos = false;
            for (int t = 0; t < T; t++)
                if (nevezett[t][a] && nevezett[t][b]) {
                    kozos = true;
                    break;
                }
            if (!kozos) cout << a << " " << b << "\n";
        }

    return 0;
}
