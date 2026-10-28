/*
Megoldás lényege:
A játéktáblát és a lövéseket két 10x10-es logikai tömbben rögzítjük, majd mindhárom kimenetet ezekből állítjuk elő. A táblázatban minden mezőhöz kiírjuk a hajó jelét (0/1), és ha a mezőt lőtték, az x jelet; a megsebesített hajórészek számánál minden hajómezőt csak egyszer számolunk, akkor is, ha többször lőttek rá. A hajók kódolásához sorfolytonosan bejárjuk a táblát: az első még fel nem dolgozott hajómező mindig egy hajó bal felső eleme, és ha a jobb oldali szomszédja hajó, a hajó vízszintes (v), ha az alatta lévő, akkor függőleges (f), a hosszát pedig a folytatás számlálásával kapjuk. Mivel a hajók még átlósan sem érnek egymáshoz, ez a bejárás minden hajót pontosan egyszer talál meg. Az időigény a tábla méretével arányos, vagyis konstans.
*/
/*
Hint 1: || A hajók felismeréséhez nem kell összefüggőséget vizsgálni: a sorfolytonos bejárásban az első még fel nem dolgozott hajómező mindig egy hajó bal felső eleme, és a jobb vagy alsó szomszédja megmondja a hajó irányát. ||
Hint 2: || A táblát két 10x10-es logikai tömbben tárold: az egyik a hajókat, a másik a lövéseket. A lövés sorát a betű adja (A a 0. sor), oszlopát a szám eggyel csökkentve. ||
Hint 3: || A hajó kódja a kezdőmező, majd a többcellás hajóknál a v vagy f betű és a hossz. A megsebesített hajórészek számához minden hajómezőt csak egyszer számolj, akkor is, ha többször is lőttek rá. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    bool ship[10][10] = {}, shot[10][10] = {}, vis[10][10] = {};
    for (int i = 0; i < 10; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < 10; j++) ship[i][j] = (s[j] == '1');
    }
    string t;
    while (cin >> t) {
        int r = t[0] - 'A';
        int c = stoi(t.substr(1)) - 1;
        shot[r][c] = true;
    }

    // 1. részfeladat: a játékállás táblázata
    cout << "#\n";
    cout << "  ";
    for (int k = 1; k <= 10; k++) {
        cout << k;
        if (k < 10) cout << "  ";
    }
    cout << '\n';
    for (int i = 0; i < 10; i++) {
        cout << char('A' + i) << ' ';
        for (int j = 0; j < 10; j++) {
            cout << (ship[i][j] ? '1' : '0') << (shot[i][j] ? 'x' : ' ');
            if (j < 9) cout << ' ';
        }
        cout << '\n';
    }

    // 2. részfeladat: a megsebesített hajórészek száma (mezőnként egyszer)
    int hitCells = 0;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (ship[i][j] && shot[i][j]) hitCells++;
    cout << "#\n" << hitCells << '\n';

    // 3. részfeladat: a pálya kódja
    cout << "#\n";
    vector<string> codes;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) {
            if (!ship[i][j] || vis[i][j]) continue;
            string name = string(1, char('A' + i)) + to_string(j + 1);
            if (j + 1 < 10 && ship[i][j + 1]) {
                int len = 0;
                while (j + len < 10 && ship[i][j + len]) {
                    vis[i][j + len] = true;
                    len++;
                }
                codes.push_back(name + "v" + to_string(len));
            } else if (i + 1 < 10 && ship[i + 1][j]) {
                int len = 0;
                while (i + len < 10 && ship[i + len][j]) {
                    vis[i + len][j] = true;
                    len++;
                }
                codes.push_back(name + "f" + to_string(len));
            } else {
                vis[i][j] = true;
                codes.push_back(name);
            }
        }
    for (size_t k = 0; k < codes.size(); k++) {
        if (k) cout << '-';
        cout << codes[k];
    }
    cout << '\n';
    return 0;
}
