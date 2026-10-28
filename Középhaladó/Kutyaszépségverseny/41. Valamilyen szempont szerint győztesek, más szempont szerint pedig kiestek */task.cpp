/*
Megoldás lényege:
Szempontonként megkeressük a legnagyobb pontot, de csak a szempont alsó ponthatárát elérő kutyák között. Az ezt a pontot elérő kutyák mindegyike (holtverseny esetén is) győzött az adott szempontban.
Kutyánként két jelölést vezetünk: volt-e legalább egy győzelme, és volt-e legalább egy olyan szempont, amelyben a pontja a ponthatár alatt maradt (kiesett). Az a kutya felel meg, amelyiknél mindkét jelölés igaz; ezek száma és sorszáma növekvő sorrendben kerül a kimenetbe.
Az időigény O(N·M), a memóriaigény O(N).
*/
/*
Hint 1: || Kutyánként két külön logikai jelölést tarts: volt-e legalább egy győzelme, és volt-e legalább egy szempont, ahol a pontja a ponthatár alatt maradt. ||
Hint 2: || A két jelölés különböző szempontokból származhat, ezért szempontonként külön ellenőrizd őket. A végén csak azokat írd ki, ahol mindkettő igaz. ||
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

    // nyert[i]: volt-e győzelme, kiesett[i]: volt-e olyan szempont, ahol a ponthatár alatt maradt
    vector<bool> nyert(n, false), kiesett(n, false);
    for (int j = 0; j < m; j++) {
        int legjobb = -1;
        for (int i = 0; i < n; i++)
            if (p[i][j] >= minPont[j]) legjobb = max(legjobb, p[i][j]);

        for (int i = 0; i < n; i++) {
            if (p[i][j] < minPont[j]) {
                kiesett[i] = true;
            } else if (p[i][j] == legjobb) {
                nyert[i] = true;
            }
        }
    }

    vector<int> valasz;
    for (int i = 0; i < n; i++)
        if (nyert[i] && kiesett[i]) valasz.push_back(i + 1);

    cout << valasz.size();
    for (int x : valasz) cout << " " << x;
    cout << "\n";
    return 0;
}
