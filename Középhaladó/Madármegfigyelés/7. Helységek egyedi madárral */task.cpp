/*
Megoldás lényege:
Fajonként megszámoljuk, hány helységben fordult elő legalább egy megfigyelés.
Ha egy faj csak egyetlen helységben fordult elő, akkor az a helység látott olyan
madarat, amilyet máshol nem. Ezeket a helységeket megjelöljük, majd a megjelölt
helységek sorszámait növekvő sorrendben írjuk ki. Az idő O(M*N), ami 50 helységnél
és 200 fajnál bőven belefér a 0,1 mp-es időlimitbe.
*/
/*
Hint 1: || Egy faj akkor "egyedi", ha az összes helység közül csak egyben fordul elő. Ezért először fajonként számold meg, hány helységben láttad legalább egyszer. ||
Hint 2: || Ha egy faj darabszáma 1, akkor azt is tudod, melyik helységben volt: menet közben jegyezd fel minden fajhoz az utolsó olyan helységet, ahol előfordult. Ez egyetlen helység lesz, ha a darabszám 1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;

    vector<vector<int>> e(m, vector<int>(n));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> e[i][j];

    // fajonként: hány helységben fordult elő, és melyikben (ha csak egyben)
    vector<int> db(n, 0), hely(n, 0);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (e[i][j] > 0) {
                db[j]++;
                hely[j] = i;
            }

    // az egyedi fajhoz tartozó helységek megjelölése
    vector<bool> egyedi(m, false);
    for (int j = 0; j < n; j++)
        if (db[j] == 1)
            egyedi[hely[j]] = true;

    vector<int> lista;
    for (int i = 0; i < m; i++)
        if (egyedi[i])
            lista.push_back(i + 1);

    cout << lista.size() << "\n";
    if (!lista.empty()) {
        for (size_t k = 0; k < lista.size(); k++) {
            if (k > 0) cout << " ";
            cout << lista[k];
        }
        cout << "\n";
    }
    return 0;
}
