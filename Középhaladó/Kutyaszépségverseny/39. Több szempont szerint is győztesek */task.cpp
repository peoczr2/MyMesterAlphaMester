/*
Megoldás lényege:
Szempontonként megkeressük a legnagyobb pontot, de csak a szempont alsó ponthatárát elérő kutyák között. Az ezt a pontot elérő kutyák mindegyike (holtverseny esetén is) győzött az adott szempontban.
Kutyánként számoljuk, hány szempontban nyert, és azokat írjuk ki, akiknek legalább két győzelmük van. A kiírásban először a darabszám áll, utána a sorszámok növekvő sorrendben.
Az időigény O(N·M), a memóriaigény O(N).
*/
/*
Hint 1: || Egy szempontban a győztes pont a ponthatárt elérő kutyák közül a legnagyobb. Ha többen is elérik, mindegyikük győzött. ||
Hint 2: || Tarts kutyánként egy számlálót: minden olyan szempontban növeld, ahol a kutya győzött. A végén a legalább kettes számlálójú kutyákat írd ki. ||
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

    // gyozelem[i]: hány szempontban győzött az i. kutya
    vector<int> gyozelem(n, 0);
    for (int j = 0; j < m; j++) {
        int legjobb = -1;
        for (int i = 0; i < n; i++)
            if (p[i][j] >= minPont[j]) legjobb = max(legjobb, p[i][j]);

        for (int i = 0; i < n; i++)
            if (p[i][j] >= minPont[j] && p[i][j] == legjobb) gyozelem[i]++;
    }

    vector<int> valasz;
    for (int i = 0; i < n; i++)
        if (gyozelem[i] >= 2) valasz.push_back(i + 1);

    cout << valasz.size();
    for (int x : valasz) cout << " " << x;
    cout << "\n";
    return 0;
}
