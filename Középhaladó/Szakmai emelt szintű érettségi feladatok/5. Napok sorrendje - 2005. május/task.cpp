/*
Megoldás lényege: minden napra (oszlopra) külön összegezzük a mért hőmérsékleteket. Mivel minden napra ugyanannyi mérés van, az átlagok sorrendje megegyezik az összegek sorrendjével, ezért az osztást el is hagyhatjuk, és egész számokkal dolgozunk. Az (összeg, napnév) párokat rendezzük: az összeg szerint növekvően, egyenlőség esetén a párok alapértelmezett rendezése a nevek ábécé-sorrendje szerint dönt. A beolvasás O(7N) = O(N) időben fut, a rendezés már csak 7 elemű, így a teljes idő O(N).
*/
/*
Hint 1: || Nem kell az átlagokat külön kiszámolni: mivel minden napra ugyanannyi mérés van, az átlagok sorrendje ugyanaz, mint az összegeké. ||
Hint 2: || Tarts egy 7 elemű tömböt az oszlopösszegeknek, a napok neveit pedig ugyanebben a sorrendben (Hétfőtől Vasárnapig). A rendezéshez használj (összeg, név) párokat: az egyenlő összegeknél a név dönt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    long long sum[7] = {0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 7; j++) {
            long long t;
            cin >> t;
            sum[j] += t;
        }
    }

    const string names[7] = {"Hetfo", "Kedd", "Szerda", "Csutortok", "Pentek", "Szombat", "Vasarnap"};

    vector<pair<long long, string>> days;
    for (int j = 0; j < 7; j++) {
        days.push_back({sum[j], names[j]});
    }
    sort(days.begin(), days.end());

    for (const auto& d : days) {
        cout << d.second << '\n';
    }
    return 0;
}
