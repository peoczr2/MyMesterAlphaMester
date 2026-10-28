/*
Megoldás lényege:
A szigetek a 0-tól különböző mérések maximális összefüggő szakaszai, amelyek előtt és után is 0 áll. Az első és az utolsó mérés kontinens fölött van, így a hozzájuk érő szakaszok nem szigetek, ezeket kihagyjuk. Egy bejárással megkeressük a szigeteket, és mindegyik szélességét (a mérések számát) összevetjük az előző sziget szélességével. A válasz 1, ha van legalább egy sziget, és a szélességek szigorúan nőnek; ha nincs sziget, a válasz 0. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || A sziget a pozitív mérések olyan összefüggő szakasza, amelynek előtte és utána is 0 áll. Az első és az utolsó mérésen kezdődő vagy végződő szakasz kontinens, nem sziget. ||
Hint 2: || Egy bejárásban szakaszonként számold ki a szélességet, és tartsd meg az előző sziget szélességét. A szélességeknek szigorúan növekedniük kell, a nincs sziget esetet pedig külön kezeld. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> m(n);
    for (auto &x : m) cin >> x;

    int szigetek = 0;               // eddig talált szigetek száma
    int elozo = 0;                  // az előző sziget szélessége
    bool egyre_szelesebb = true;    // minden eddigi sziget szigorúan szélesebb-e az előzőnél

    int i = 0;
    while (i < n) {
        if (m[i] == 0) {
            i++;
            continue;
        }
        int l = i;
        while (i < n && m[i] > 0) i++;
        int r = i - 1;  // a szakasz [l..r] indexeken van (0-tól számozva)

        if (l == 0 || r == n - 1) continue;  // a kontinenshez érő szakasz nem sziget

        int szelesseg = r - l + 1;
        if (szigetek > 0 && szelesseg <= elozo) egyre_szelesebb = false;
        elozo = szelesseg;
        szigetek++;
    }

    cout << ((szigetek >= 1 && egyre_szelesebb) ? 1 : 0) << "\n";
    return 0;
}
