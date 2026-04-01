/*
 * Az A^k mod B maradékok ciklikusan ismétlődnek. Megkeressük az összes különböző
 * maradékot a szorzás ismételt alkalmazásával.
 
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
