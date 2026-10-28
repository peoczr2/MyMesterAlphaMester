/*
Megoldás lényege: minden munkás pontosan egy munkát kap, és minden munka pontosan egy munkáshoz kerül, tehát teljes párosítást keresünk.
A munkásokat sorban osztjuk ki: az aktuális munkásnak a még szabad, általa vállalható munkák közül a legkisebb sorszámút próbáljuk, és ha az ág zsákutcának bizonyul, visszalépünk.
A zsákutcákat előre kiszűrjük: minden döntés után Kuhn-féle augmentáló utakkal ellenőrizzük, hogy a még kiosztatlan munkásokra van-e teljes párosítás a szabad munkákkal.
Ez a nyesés miatt a visszalépés gyakorlatilag nem fordul elő, és ha a teljes párosítás nem létezik, a gyökérnél minden próbálkozás elbukik, a válasz NINCS.
Így munkásonként mindig a lehető legkisebb munkasorszámot választjuk, amennyire a teljes kiosztás még folytatható.
Időigény: legfeljebb N döntési szint, szintenként N próbálkozás, mindegyik ellenőrzés O(N^3), ami N ≤ 30 mellett bőven belefér.
*/
/*
Hint 1: || Minden munkás pontosan egy munkát kap, és minden munkát pontosan egy munkás végez: keress teljes párosítást, és próbáld sorban a munkásokat. ||
Hint 2: || Egy részleges kiosztás csak akkor folytatható, ha a még ki nem osztott munkásokra van teljes párosítás a szabad munkákkal; ezt egy Kuhn-féle, augmentáló utakat kereső ellenőrzéssel dönthetjük el. ||
*/

#include "../common.hpp"

int n;
vector<vector<int>> tud;   // tud[i]: az i. munkás (0-tól) által vállalható munkák, növekvő sorrendben
vector<int> kiosztas;      // kiosztas[i]: az i. munkás munkája (0-tól)
vector<char> foglalt;      // foglalt[j]: a j. munka már ki van osztva

vector<int> parJob;        // parJob[j]: a j. munkához az ellenőrzésben rendelt munkás, -1 ha nincs
vector<char> latogatott;

bool utatKeres(int i) {
    for (int j : tud[i]) {
        if (foglalt[j] || latogatott[j]) continue;
        latogatott[j] = 1;
        if (parJob[j] < 0 || utatKeres(parJob[j])) {
            parJob[j] = i;
            return true;
        }
    }
    return false;
}

// Van-e teljes párosítás a from..n-1 munkásokra a még szabad munkákkal?
bool lehetseges(int from) {
    parJob.assign(n, -1);
    for (int i = from; i < n; ++i) {
        latogatott.assign(n, 0);
        if (!utatKeres(i)) return false;
    }
    return true;
}

bool visszalep(int i) {
    if (i == n) return true;
    for (int j : tud[i]) {
        if (foglalt[j]) continue;
        foglalt[j] = 1;
        kiosztas[i] = j;
        if (lehetseges(i + 1) && visszalep(i + 1)) return true;
        foglalt[j] = 0;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    tud.assign(n, {});
    for (int i = 0; i < n; ++i) {
        int db;
        cin >> db;
        for (int k = 0; k < db; ++k) {
            int munka;
            cin >> munka;
            tud[i].push_back(munka - 1);
        }
        sort(tud[i].begin(), tud[i].end());
        tud[i].erase(unique(tud[i].begin(), tud[i].end()), tud[i].end());
    }
    kiosztas.assign(n, -1);
    foglalt.assign(n, 0);
    if (!visszalep(0)) {
        cout << "NINCS\n";
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << kiosztas[i] + 1;
    }
    cout << '\n';
    return 0;
}
