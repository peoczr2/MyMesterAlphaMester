/*
Megoldás lényege:
Először beolvassuk az összes napi értéket, és közben kiszámoljuk az esti értékek összegét. Az esti értékek átlaga összeg / N, de nem kell törtként számolni: az E > összeg / N feltétel egyenértékű az E * N > összeg egész számú egyenlőtlenséggel, így nincs lebegőpontos pontatlanság. Egy második menetben a feltételt teljesítő napok sorszámait növekvő sorrendben gyűjtjük, majd az első sorba a darabszám, utána a napok sorszámai kerülnek. Az idő O(N).
*/
/*
Hint 1: || Az átlagot nem kell törtként kiszámolni: a napok száma és az esti értékek összege is egész, így az összehasonlítás szorzással, egész számokkal elvégezhető. ||
Hint 2: || Először olvasd be az összes adatot, és gyűjtsd össze az esti értékek összegét. Második menetben vizsgáld meg minden napra, hogy az esti érték szorozva N-nel nagyobb-e az összegnél. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> reggel(n), este(n);
    long long osszeg = 0;
    for (int i = 0; i < n; i++) {
        cin >> reggel[i] >> este[i];
        osszeg += este[i];
    }

    vector<int> napok;
    for (int i = 0; i < n; i++) {
        if ((long long)este[i] * n > osszeg) {
            napok.push_back(i + 1);
        }
    }

    cout << napok.size();
    for (int nap : napok) {
        cout << " " << nap;
    }
    cout << "\n";
    return 0;
}
