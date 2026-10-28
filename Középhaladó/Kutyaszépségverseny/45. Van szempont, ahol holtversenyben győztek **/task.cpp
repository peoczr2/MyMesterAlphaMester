/*
Megoldás lényege:
Kiesettnek számít az a kutya, amely valamelyik szempontban az alsó határ alatt maradt; a bentmaradók közül az összpontszámban legjobbak az összetett győztesek (holtverseny esetén mindegyik).
Szempontonként megkeressük a legnagyobb pontot, amelyet az adott szempontban értékelhető (az alsó határt elérő) kutya elért.
Ha ezt a pontot legalább két összetett győztes eléri, az adott szempontban holtverseny alakult ki a győztesek között, és a válasz VAN.
Ha ilyen szempont nincs, vagy nincs bentmaradó kutya, a válasz NINCS.
Az idő O(N · M), a memóriaigény O(N · M).
*/
/*
Hint 1: || Először szűrd ki a kiesett kutyákat: egy kutya akkor marad bent, ha minden szempontban eléri az alsó határt. Az összpontszámot csak a bentmaradókra számold. ||
Hint 2: || Az összetett győztesek a bentmaradók közül a legnagyobb összpontszámúak, holtverseny esetén többen is. Jelöld meg őket egy logikai tömbben. ||
Hint 3: || Szempontonként keresd meg a legnagyobb pontot az értékelhető kutyák között, akár kiesett kutyáról is van szó, ha az adott szempontban az alsó határt eléri. Utána számold meg, hány összetett győztes éri el ezt a pontot. ||
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

    vector<int> ossz(n, 0);
    vector<bool> bent(n, true);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            ossz[i] += p[i][j];
            if (p[i][j] < minPont[j]) bent[i] = false;
        }

    int legjobb = -1;
    for (int i = 0; i < n; i++)
        if (bent[i]) legjobb = max(legjobb, ossz[i]);

    vector<bool> gyoztes(n, false);
    for (int i = 0; i < n; i++)
        if (bent[i] && ossz[i] == legjobb) gyoztes[i] = true;

    bool van = false;
    for (int j = 0; j < m && !van; j++) {
        int legjobbPont = -1;
        for (int i = 0; i < n; i++)
            if (p[i][j] >= minPont[j]) legjobbPont = max(legjobbPont, p[i][j]);

        int db = 0;
        for (int i = 0; i < n; i++)
            if (gyoztes[i] && p[i][j] == legjobbPont) db++;
        if (db >= 2) van = true;
    }

    cout << (van ? "VAN" : "NINCS") << '\n';
    return 0;
}
