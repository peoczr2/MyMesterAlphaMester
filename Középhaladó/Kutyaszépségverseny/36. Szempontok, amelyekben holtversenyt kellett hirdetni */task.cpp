/*
Megoldás lényege:
Szempontonként először megkeressük a legnagyobb pontot azok között a kutyák között, akik elérik az adott szempont alsó ponthatárát, mert a többi kutya ebből a szempontból nem értékelhető. Ha ezt a pontot legalább két kutya eléri, a szempontban holtverseny volt, és a sorszámát a válaszba írjuk. Ha egyetlen kutya sem éri el az alsó határt, nincs első hely, így nincs holtverseny. Az időigény O(N·M), a memóriaigény O(N·M).
*/
/*
Hint 1: || Egy szempontban a győztes pontot csak az alsó ponthatárt elérő kutyák között keresd. Ha ezen belül a legnagyobb pontot legalább két kutya eléri, az holtverseny. ||
Hint 2: || Szempontonként számold meg, hány kutya kapta a legnagyobb pontot, és csak azokat a szempontokat írd ki, ahol ez a szám legalább kettő. A darabszámot írd ki elsőnek. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> maxPont(m), minPont(m);
    for (int &x : maxPont) cin >> x;
    for (int &x : minPont) cin >> x;

    vector<vector<int>> p(n, vector<int>(m));
    for (auto &sor : p)
        for (int &x : sor) cin >> x;

    vector<int> valasz;
    for (int j = 0; j < m; j++) {
        int legjobb = -1;
        for (int i = 0; i < n; i++)
            if (p[i][j] >= minPont[j]) legjobb = max(legjobb, p[i][j]);
        if (legjobb < 0) continue;

        int db = 0;
        for (int i = 0; i < n; i++)
            if (p[i][j] == legjobb) db++;
        if (db >= 2) valasz.push_back(j + 1);
    }

    cout << valasz.size();
    for (int x : valasz) cout << ' ' << x;
    cout << '\n';
    return 0;
}
