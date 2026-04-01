/*
A megoldás lényege, hogy minden emberhez eltároljuk a szüleit és a gyerekeit is. Először megkeressük
Y összes testvérét: ezek pontosan azok a személyek, akik Y valamelyik szülőjének más gyerekei. Ezután
a megtalált testvérek összes szülőjét megjelöljük, majd a megjelölt sorszámokat növekvő sorrendben
kiírjuk.
*/
/*
Hint 1: || Y testvéreit úgy kapod meg, hogy végignézed Y szüleinek összes gyerekét, és Y-t kihagyod. ||
Hint 2: || Ha megvan egy testvér, az ő összes szülőjét be kell tenni az eredménybe. ||
Hint 3: || A végén egy logikai jelölő tömbből 1-től N-ig könnyen kiírható a növekvő sorrend. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<vector<int>> szulok(N + 1), gyerekek(N + 1);
    for (int i = 0; i < K; ++i) {
        int szulo, gyerek;
        cin >> szulo >> gyerek;
        gyerekek[szulo].push_back(gyerek);
        szulok[gyerek].push_back(szulo);
    }

    int Y;
    cin >> Y;

    vector<char> testver(N + 1, false);
    for (int szulo : szulok[Y]) {
        for (int gyerek : gyerekek[szulo]) {
            if (gyerek != Y) testver[gyerek] = true;
        }
    }

    vector<char> jelolt(N + 1, false);
    for (int szemely = 1; szemely <= N; ++szemely) {
        if (!testver[szemely]) continue;
        for (int szulo : szulok[szemely]) {
            jelolt[szulo] = true;
        }
    }

    vector<int> eredmeny;
    for (int i = 1; i <= N; ++i) {
        if (jelolt[i]) eredmeny.push_back(i);
    }

    cout << eredmeny.size() << '\n';
    for (size_t i = 0; i < eredmeny.size(); ++i) {
        if (i) cout << ' ';
        cout << eredmeny[i];
    }
    cout << '\n';

    return 0;
}
