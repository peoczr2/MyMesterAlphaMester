/*
Megoldás lényege:
Szempontonként csak azok a kutyák értékelhetők, akik elérik az adott szempont alsó ponthatárát. Ezek között keressük a legnagyobb és a legkisebb pontot; a maximumot elérők mindegyike győztes, a minimumot elérők mindegyike utolsó (holtverseny esetén is).
Egy kutya akkor jó, ha egyik szempontban sem győztes és sem utolsó. Ahol a kutya nem értékelhető, ott nem lehet sem győztes, sem utolsó, ezért az ilyen szempont nem zárja ki. A jó kutyák sorszámát a darabszámmal együtt, növekvő sorrendben írjuk ki.
Az időigény O(N·M), a memóriaigény O(N·M).
*/
/*
Hint 1: || Szempontonként először csak azokat a pontokat vedd figyelembe, amelyek elérik a szempont alsó ponthatárát, és ezek között keresd a legnagyobb és a legkisebb értéket. ||
Hint 2: || Kutyánként nézd végig a szempontokat: ahol a pontja eléri a ponthatárt, de egyezik a szempont maximumával vagy minimumával, a kutya nem lehet jó. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // a maximális pontokra a számításhoz nincs szükség, csak beolvassuk őket
    vector<int> maxPont(m);
    for (int &x : maxPont) cin >> x;

    vector<int> minPont(m);
    for (int &x : minPont) cin >> x;

    vector<vector<int>> p(n, vector<int>(m));
    for (auto &sor : p)
        for (int &x : sor) cin >> x;

    // szempontonként a legnagyobb és a legkisebb pont, csak az értékelhető kutyák között
    vector<int> legjobb(m, -1), legrosszabb(m, INT_MAX);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (p[i][j] >= minPont[j]) {
                legjobb[j] = max(legjobb[j], p[i][j]);
                legrosszabb[j] = min(legrosszabb[j], p[i][j]);
            }

    vector<int> valasz;
    for (int i = 0; i < n; i++) {
        bool jo = true;
        for (int j = 0; j < m && jo; j++) {
            if (p[i][j] < minPont[j]) continue;  // ebben a szempontban nem értékelhető
            if (p[i][j] == legjobb[j] || p[i][j] == legrosszabb[j]) jo = false;
        }
        if (jo) valasz.push_back(i + 1);
    }

    cout << valasz.size();
    for (int x : valasz) cout << " " << x;
    cout << "\n";
    return 0;
}
