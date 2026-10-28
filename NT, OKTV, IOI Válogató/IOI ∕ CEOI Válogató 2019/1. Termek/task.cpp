/*
Megoldás lényege:
A termek és az ajtók egy gyökeres fát alkotnak, amelynek gyökere az 1-es terem. Egy terem akkor érhető el, ha a gyökértől idáig vezető útvonal minden ajtaja nyitva van, a zárt ajtó mögötti termek pedig megmaradnak, csak elérhetetlenné válnak. Új terem csak akkor keletkezik, ha egy még soha nem nyitott ajtót nyitunk ki, így minden terem szülőjét és oldalát egyszer rögzítjük, később csak az ajtók állapota változik. A „bal kéz a falon” bejárás mélységi bejárás, ahol a bal oldali ajtón előbb megyünk, ezért két terem sorrendjét a legkisebb közös ős alatti ágak oldala dönti el (ha az egyik őse a másiknak, az van előbb). Mivel bármely útvonal legfeljebb 32 teremből áll, a gyökértől vezető utat és az elérhetőséget minden kérésnél végigkövetve egy kérés O(32) lépésben megválaszolható.
*/
/*
Hint 1: || A termek és az ajtók fát alkotnak az 1-es terem gyökérrel. Egy terem akkor érhető el, ha a gyökértől idáig vezető összes ajtó nyitva van. ||
Hint 2: || A bal kéz a falon bejárás mélységi bejárás, a bal oldali ajtón mindig előbb megyünk. Két terem sorrendjéhez keresd meg a legkisebb közös őst: ha az egyik őse a másiknak, az van előbb, különben az van előbb, amelyik a bal oldali ágon van. Mivel az útvonal legfeljebb 32 terem, a szülőkön felfelé lépkedés elég. ||
Hint 3: || Zárt ajtó mögül a terem nem törlődik, csak elérhetetlenné válik, így az ajtó újranyitása visszaadja. Tárold minden teremhez a szülőjét, azt, hogy melyik oldali ajtón érhető el, és hogy az ajtó nyitva van-e. Új terem akkor jön létre, ha az ajtó még soha nem volt nyitva és nincs mögötte terem. ||
*/
#include <bits/stdc++.h>
using namespace std;

// child[v][0] / child[v][1]: a v terem bal / jobb ajtaja mögötti terem (0, ha nincs ott terem)
vector<array<int, 2>> child;
vector<int> par;          // par[v]: a v termet tartalmazó szülőterem
vector<int> side;         // side[v]: a szülő melyik oldali ajtaján érhető el v (0 bal, 1 jobb)
vector<char> openDoor;    // openDoor[v]: a szülőtől v felé vezető ajtó nyitva van-e

// A gyökértől v-ig vezető termek sorozatát adja vissza (a gyökér az első).
// Visszatérési érték: elérhető-e v a gyökérből, azaz nyitva van-e minden ajtó az úton.
bool pathFromRoot(int v, vector<int> &path) {
    path.clear();
    bool ok = true;
    for (int u = v; u > 1; u = par[u]) {
        path.push_back(u);
        if (!openDoor[u]) ok = false;
    }
    path.push_back(1);
    reverse(path.begin(), path.end());
    return ok;
}

// 1, ha B érhető el előbb; -1, ha A; 0, ha egyik sem érhető el.
int compareRooms(int a, int b) {
    vector<int> pa, pb;
    bool ra = pathFromRoot(a, pa);
    bool rb = pathFromRoot(b, pb);
    if (!ra && !rb) return 0;
    if (ra && !rb) return -1;
    if (!ra && rb) return 1;

    size_t i = 0;
    while (i < pa.size() && i < pb.size() && pa[i] == pb[i]) ++i;
    if (i == pa.size()) return -1;  // A az ős (vagy egyenlő), így A van előbb
    if (i == pb.size()) return 1;   // B az ős, így B van előbb
    // pa[i] és pb[i] testvérek: a bal oldali ágat járjuk be előbb
    return side[pa[i]] == 0 ? -1 : 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    child.assign(n + 1, array<int, 2>{0, 0});
    par.assign(n + 1, 0);
    side.assign(n + 1, 0);
    openDoor.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int bal, jobb;
        cin >> bal >> jobb;
        child[i] = {bal, jobb};
        if (bal) {
            par[bal] = i;
            side[bal] = 0;
            openDoor[bal] = 1;
        }
        if (jobb) {
            par[jobb] = i;
            side[jobb] = 1;
            openDoor[jobb] = 1;
        }
    }

    int k;
    cin >> k;
    while (k--) {
        int t, a, x;
        cin >> t >> a >> x;
        if (t == 1) {
            cout << compareRooms(a, x) << '\n';
        } else {
            int s = x - 1;  // 0: bal, 1: jobb ajtó
            if (t == 2) {
                if (child[a][s] == 0) {
                    // még soha nem nyitott ajtó: új terem keletkezik
                    child.push_back(array<int, 2>{0, 0});
                    par.push_back(a);
                    side.push_back(s);
                    openDoor.push_back(1);
                    child[a][s] = (int)child.size() - 1;
                } else {
                    openDoor[child[a][s]] = 1;
                }
            } else {
                if (child[a][s] != 0) openDoor[child[a][s]] = 0;
            }
        }
    }
    return 0;
}
