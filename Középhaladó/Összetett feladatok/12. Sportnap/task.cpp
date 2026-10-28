/*
Megoldás lényege:
Az első előfordulás sorrendjében tanulónként nyilvántartjuk, melyik sportágakra nevezett (logikai tömb). Ebből megkapjuk a pontosan egy sportágra nevezett tanulót, a legtöbb sportágban nevezett tanulót (döntetlennél az elsőt), és a sportágankénti létszámot.
Két sportág akkor rendezhető egyszerre, ha mindkettőre van nevezés, és nincs közös tanuló; az (a, b) párokat a < b feltétellel, növekvő sorrendben írjuk ki. Minden tanulóhoz azt számoljuk, hány másik tanulóval találkozhat legalább egy sportágon: ehhez két tanuló között akkor van kapcsolat, ha van közös sportáguk. Az időigény O(T^2 * S), ami a kis korlátok miatt bőven belefér.
*/
/*
Hint 1: || Tanulónként tárold, melyik sportágakra nevezett (például logikai tömbben), és az első előfordulásuk sorrendjét is jegyezd meg. A pontosan egy sportágra nevezett tanuló keresése ebből már egyszerű számlálás. ||
Hint 2: || Két tanuló akkor találkozhat egy versenyen, ha van közös sportágjuk. Ezt két egymásba ágyazott ciklussal, a sportágak mentén ellenőrizheted, és minden tanulóra külön összeszámolod a találkozható tanulókat. ||
Hint 3: || A sportágpárok kiírásánál egy (a, b) pár akkor kerül a listába, ha mindkettőre nevezett valaki, és nincs olyan tanuló, aki mindkettőre nevezett. A 0 fős sportágak ne szerepeljenek, ezért a létszámot előbb számold ki. ||
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

    int T = nevek.size();
    vector<int> sportagakSzama(T, 0);
    vector<int> letszam(S + 1, 0);
    for (int t = 0; t < T; t++)
        for (int s = 1; s <= S; s++)
            if (nevezett[t][s]) {
                sportagakSzama[t]++;
                letszam[s]++;
            }

    // 1. részfeladat: egy tanuló, aki pontosan egy sportágra nevezett
    cout << "#\n";
    int egy = -1;
    for (int t = 0; t < T; t++)
        if (sportagakSzama[t] == 1) {
            egy = t;
            break;
        }
    if (egy >= 0) cout << nevek[egy] << "\n";
    else cout << "\n";

    // 2. részfeladat: a legtöbb sportágban nevezett tanuló
    cout << "#\n";
    int legtobb = 0;
    for (int t = 1; t < T; t++)
        if (sportagakSzama[t] > sportagakSzama[legtobb]) legtobb = t;
    cout << nevek[legtobb] << "\n";

    // 3. részfeladat: sportáganként a nevezettek száma
    cout << "#\n";
    for (int s = 1; s <= S; s++)
        cout << letszam[s] << (s < S ? " " : "\n");

    // 4. részfeladat: egyidőben rendezhető sportág-párok (üres sportágak nélkül)
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

    // 5. részfeladat: tanulónként, hány tanulóval találkozhat valamelyik versenyen
    cout << "#\n";
    for (int t = 0; t < T; t++) {
        int talalkozik = 0;
        for (int u = 0; u < T; u++) {
            if (u == t) continue;
            for (int s = 1; s <= S; s++)
                if (nevezett[t][s] && nevezett[u][s]) {
                    talalkozik++;
                    break;
                }
        }
        cout << nevek[t] << " " << talalkozik << "\n";
    }

    return 0;
}
