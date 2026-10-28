/*
Megoldás lényege:
Egy verseny átlaga a verseny pontjainak összege osztva a résztvevők számával, az összes versenyen szerzett pontok átlaga pedig az összes pont összege osztva a pontok (bejegyzések) számával. Ezt a két törtet nem kell lebegőpontosan kiszámolni: a feltétel a_i / n_i > össz / db ekvivalens az a_i * db > össz * n_i alakkal, amely egész számokkal, pontosan ellenőrizhető. A bemenetet egyszer soronként beolvassuk, közben gyűjtjük a verseny-összegeket, a résztvevők számát és a teljes összeget, majd egyetlen ciklusban válogatjuk ki az átlagosnál erősebb versenyeket. A Mini értékek ebben a feladatban nem befolyásolják az eredményt, ezért csak beolvassuk őket. Az időigény O(N·M), ami a korlátok mellett nagyon gyors.
*/
/*
Hint 1: || Két átlagot kell összehasonlítani: minden verseny pontjainak átlagát, és az összes versenyen szerzett pontok átlagát. A Mini értékekre ebben a feladatban nincs szükség. ||
Hint 2: || Ne használj törtet: a verseny átlagának összegét és a résztvevők számát tárold, az összes pontnál pedig a teljes összeget és a bejegyzések számát. Az egyenlőtlenséget úgy írd át, hogy csak szorzás szerepeljen, így nem kell lebegőpontos számítás. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int minimum;  // ebben a feladatban nem kell
        cin >> minimum;
    }

    vector<long long> compSum(m, 0), compCnt(m, 0);
    long long totalSum = 0, totalCnt = 0;

    for (int i = 0; i < m; i++) {
        int ind;
        cin >> ind;
        for (int j = 0; j < ind; j++) {
            int s, p;
            cin >> s >> p;
            compSum[i] += p;
            compCnt[i]++;
            totalSum += p;
            totalCnt++;
        }
    }

    vector<int> ans;
    for (int i = 0; i < m; i++) {
        // compSum[i] / compCnt[i] > totalSum / totalCnt, szorzással
        if (compSum[i] * totalCnt > totalSum * compCnt[i]) {
            ans.push_back(i + 1);
        }
    }

    cout << ans.size();
    for (int x : ans) {
        cout << ' ' << x;
    }
    cout << '\n';
    return 0;
}
