/*
Megoldás lényege:
Egy kutya valamilyen szempont szerint tökéletes, ha valamelyik szempontban a pontszáma eléri a szempont maximumát.
Ehhez csak a pontszámokat és a maximumokat kell összevetni; a kiesés ezt nem befolyásolja, mert a kiesett kutya is értékelhető más szempontokból.
Minden kutyát egyszer végigvizsgálunk, és az első tökéletes szempont után abbahagyjuk a keresést, így a holtverseny nem okoz duplázást.
A kutyákat sorszám szerint járjuk be, ezért a kimenet is növekvő sorrendben lesz.
Az idő O(N · M), a memóriaigény O(N · M).
*/
/*
Hint 1: || Egy kutyánál elég olyan szempontot keresni, ahol a pontszám egyenlő a szempont maximumával. A kiesés itt nem számít. ||
Hint 2: || Minden kutya minden szempontjánál hasonlítsd össze a pontot a szempont maximumával. Ha valahol egyezik, tedd be a kutya sorszámát egy listába, és ugorj a következő kutyára. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> maxPont(m), minPont(m);
    for (int &x : maxPont) cin >> x;
    for (int &x : minPont) cin >> x;

    vector<vector<int>> p(n, vector<int>(m));
    for (auto &sor : p)
        for (int &x : sor) cin >> x;

    vector<int> tokeletes;
    for (int i = 0; i < n; i++) {
        bool van = false;
        for (int j = 0; j < m && !van; j++)
            if (p[i][j] == maxPont[j]) van = true;
        if (van) tokeletes.push_back(i + 1);
    }

    cout << tokeletes.size();
    for (int x : tokeletes) cout << ' ' << x;
    cout << '\n';
    return 0;
}
