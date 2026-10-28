/*
Megoldás lényege:
A mérési pontokhoz kiszámoljuk a készültségi fokot, majd a sorozatot maximális, azonos fokú folyószakaszokra bontjuk. Árvíz az egymás melletti, legalább elsőfokú szakaszok maximális sorozata, ezért egy bejárásban nyitunk és zárunk árvizeket. Közben minden árvízen belül megszámoljuk az 1., 2. és 3. fokú szakaszokat, és az egész sorozatra is összesítjük ugyanezeket. A legtöbb szakaszból álló fokozat az összesítésből választható ki; egyenlőség esetén a kisebb fokozat marad. Ha nincs árvíz, csak a 0 kerül a kimenetbe. Az egész egy bejárással, O(N) időben megoldható.
*/
/*
Hint 1: || Bontsd a mérési sort készültség szerinti szakaszokra, és gondold át, mikor kezdődik és mikor ér véget egy árvíz: az összefüggő, legalább elsőfokú szakaszokból álló sorozat. ||
Hint 2: || Egy bejárásban tartsd nyitva az aktuális árvizet: ha egy szakasz legalább elsőfokú, akkor vagy új árvizet nyitsz, vagy meghosszabbítod az előzőt, és a szakasz fokának megfelelő számlálót növeled. ||
Hint 3: || Az összesített darabszámok megegyeznek az árvizek számlálóinak összegével. A legnagyobb darabszámú fokozatnál egyenlőség esetén a kisebb fokozatot írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

// készültség: 0 = árvízmentes, 1, 2, 3 = az árvízvédelmi fokozat
int keszultseg(int a) {
    if (a <= 800) return 0;
    if (a <= 900) return 1;
    if (a <= 1000) return 2;
    return 3;
}

struct Arviz {
    int bal, jobb;
    array<int, 3> db;  // az árvízben levő 1., 2., 3. fokú szakaszok száma
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> fok(n + 1);
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        fok[i] = keszultseg(a);
    }

    vector<Arviz> arvizek;
    array<int, 3> osszes = {0, 0, 0};  // az összes 1., 2., 3. fokú szakasz
    bool nyitva = false;               // van-e éppen nyitott árvíz
    for (int i = 1; i <= n;) {
        int j = i;
        while (j < n && fok[j + 1] == fok[i]) j++;
        int f = fok[i];
        if (f >= 1) {
            if (!nyitva) {
                arvizek.push_back({i, j, {0, 0, 0}});
                nyitva = true;
            }
            arvizek.back().jobb = j;
            arvizek.back().db[f - 1]++;
            osszes[f - 1]++;
        } else {
            nyitva = false;
        }
        i = j + 1;
    }

    // 1. sor: az árvizek darabszáma; ha nincs, csak ez a sor marad
    cout << arvizek.size() << '\n';
    if (arvizek.empty()) return 0;

    // 2. sor: az árvizek kezdete és vége
    for (size_t i = 0; i < arvizek.size(); i++) {
        if (i) cout << ' ';
        cout << arvizek[i].bal << ' ' << arvizek[i].jobb;
    }
    cout << '\n';

    // 3. sor: árvizenként az 1., 2., 3. fokú szakaszok darabszáma
    for (size_t i = 0; i < arvizek.size(); i++) {
        for (int k = 0; k < 3; k++) {
            if (i || k) cout << ' ';
            cout << arvizek[i].db[k];
        }
    }
    cout << '\n';

    // 4. sor: az összes 1., 2., 3. fokú szakasz darabszáma
    cout << osszes[0] << ' ' << osszes[1] << ' ' << osszes[2] << '\n';

    // 5. sor: a legtöbb szakaszból álló fokozat (egyenlőségnél a kisebb)
    int legtobb = 0;
    for (int k = 1; k < 3; k++)
        if (osszes[k] > osszes[legtobb]) legtobb = k;
    cout << legtobb + 1 << '\n';
    return 0;
}
