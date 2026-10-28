/*
Megoldás lényege:
Kiesik az a kutya, amely valamelyik szempontban nem érte el az alsó határt; a többi kutya bennmarad.
Az összpontszámot csak a bennmaradók között számoljuk, az abszolút győztes ezek közül a legtöbb összpontot elérő kutya (holtverseny esetén mindegyik).
Szempontonként megkeressük a bennmaradók legnagyobb pontszámát: ha a győztes valamelyik szempontban eléri ezt (akár holtversenyben), ott győzött.
A válasz VAN, ha van olyan abszolút győztes, amely egyik szempontban sem győzött, vagyis minden szempontban van nála jobb bennmaradó kutya; egyébként NINCS.
Az idő O(N · M), a memóriaigény O(N · M).
*/
/*
Hint 1: || Előbb szűrd ki a kiesett kutyákat: egy kutya akkor marad bent, ha minden szempontban eléri az alsó ponthatárt. A további számításokat csak a bennmaradókkal végezd. ||
Hint 2: || Számold ki a bennmaradók összpontszámát és keresd meg a legnagyobbat. Szempontonként külön keresd meg a bennmaradók legnagyobb pontszámát; egy győztes kutyánál elég megnézni, hogy valamelyik szempontban egyezik-e ezzel a maximummal. ||
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

    vector<bool> bent(n, true);
    for (int j = 0; j < n; j++)
        for (int i = 0; i < m; i++)
            if (p[j][i] < minPont[i]) bent[j] = false;

    vector<int> szempontMax(m, -1);
    vector<int> ossz(n, 0);
    int legjobbOssz = -1;
    for (int j = 0; j < n; j++) {
        if (!bent[j]) continue;
        for (int i = 0; i < m; i++) {
            ossz[j] += p[j][i];
            szempontMax[i] = max(szempontMax[i], p[j][i]);
        }
        legjobbOssz = max(legjobbOssz, ossz[j]);
    }

    bool van = false;
    for (int j = 0; j < n && !van; j++) {
        if (!bent[j] || ossz[j] != legjobbOssz) continue;
        bool seholNemGyozott = true;
        for (int i = 0; i < m; i++)
            if (p[j][i] == szempontMax[i]) {
                seholNemGyozott = false;
                break;
            }
        if (seholNemGyozott) van = true;
    }

    cout << (van ? "VAN" : "NINCS") << '\n';
    return 0;
}
