/*
Megoldás lényege:
Szempontonként megkeressük a legnagyobb pontot, de csak a szempont alsó ponthatárát elérő kutyák között. Az ezt a pontot elérő kutyák mindegyike (holtverseny esetén is) győzött az adott szempontban.
Azt a kutyát, amely legalább egy szempontban győzött, egyszer jelöljük meg egy logikai tömbben, így akkor is csak egyszer kerül a kimenetbe, ha többször nyert. A végén a megjelölt kutyák darabszámát és sorszámait írjuk ki növekvő sorrendben.
Az időigény O(N·M), a memóriaigény O(N).
*/
/*
Hint 1: || Egy szempontban a győztes pont a ponthatárt elérő kutyák közül a legnagyobb. Ha többen is elérik, mindegyikük győzött. ||
Hint 2: || Elég egy logikai tömb: ha egy kutya egy szempontban győzött, állítsd igazra. A kiírásnál ne számold a győzelmeket, csak azt nézd, igaz-e a jelölés. ||
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

    // nyert[i]: az i. kutya nyert-e legalább egy szempontban
    vector<bool> nyert(n, false);
    for (int j = 0; j < m; j++) {
        int legjobb = -1;
        for (int i = 0; i < n; i++)
            if (p[i][j] >= minPont[j]) legjobb = max(legjobb, p[i][j]);

        for (int i = 0; i < n; i++)
            if (p[i][j] >= minPont[j] && p[i][j] == legjobb) nyert[i] = true;
    }

    vector<int> valasz;
    for (int i = 0; i < n; i++)
        if (nyert[i]) valasz.push_back(i + 1);

    cout << valasz.size();
    for (int x : valasz) cout << " " << x;
    cout << "\n";
    return 0;
}
