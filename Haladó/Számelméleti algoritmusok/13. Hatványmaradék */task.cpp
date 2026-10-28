/*
Megoldás lényege:
Az A^k mod B sorozat legfeljebb B különböző értéket vehet fel, ezért egy idő után szükségszerűen ismétlődni kezd. A bejárást az 1 mod B értékből indítjuk (ez az A^0 maradéka, és a minta is tartalmazza), és minden lépésben A-val szorzunk modulo B. Amint egy maradék másodszor kerül elő, megállunk, mert ettől kezdve már csak korábban látott értékek jönnének. Az összegyűjtött, különböző maradékokat rendezve, szóközzel elválasztva írjuk ki. A bejárás legfeljebb B lépés, a rendezés miatt az összidő O(B log B), a memória O(B).
*/
/*
Hint 1: || Az A hatványainak B szerinti maradékai előbb-utóbb ismétlődni kezdenek, mert csak B darab maradék létezik. ||
Hint 2: || Indulj 1 mod B-ből, mindig szorozz A-val mod B szerint, és állj meg, amikor egy maradék másodszor is előjön. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;
    vector<bool> seen(b);
    vector<int> residues;
    int cur = 1 % b;
    while (!seen[cur]) {
        seen[cur] = true;
        residues.push_back(cur);
        cur = int(1LL * cur * a % b);
    }
    sort(residues.begin(), residues.end());
    for (int i = 0; i < (int)residues.size(); ++i) {
        if (i) cout << ' ';
        cout << residues[i];
    }
    cout << '\n';
    return 0;
}
