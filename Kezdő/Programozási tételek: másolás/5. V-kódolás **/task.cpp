/*
Megoldás lényege:
A V-alakban minden karakter egy sorba kerül, és a sorindex a karakter sorszámával együtt periodikusan változik: 0, 1, …, V−1, majd vissza V−2, …, 1, aztán újra 0. Ennek a periódusa 2·(V−1) hosszú. Ezért minden i-edik karakterhez kiszámoljuk, melyik sorba esik a maradék alapján: ha a maradék kisebb V-nél, a sor a maradék, különben 2·(V−1) mínusz a maradék. A karaktereket ilyen módon V darab sorba gyűjtjük, majd a sorokat felülről lefelé egymás után fűzzük. Minden karaktert egyszer dolgozunk fel, ezért az időigény O(N), a memóriaigény szintén O(N).
*/
/*
Hint 1: || Ne a betűk alakját kövesd, hanem azt figyeld, hogy minden karakter sorszámához melyik sor tartozik. A sorindex a sorszámmal együtt ismétlődő mintát követ. ||
Hint 2: || Az ismétlődés hossza 2·(V−1). Számold ki a sorszám maradékát ezzel a hosszal osztva: ha a maradék kisebb V-nél, az a sorindex, egyébként a hosszból kivonva kapod meg. Tarts V darab szöveget, és a végén fűzd össze őket sorrendben. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, v;
    cin >> n >> v;
    string s;
    cin >> s;

    int period = 2 * (v - 1);
    vector<string> rows(v);
    for (int i = 0; i < n; i++) {
        int k = i % period;
        int row = (k < v) ? k : period - k;
        rows[row] += s[i];
    }

    string result;
    for (const string& r : rows) {
        result += r;
    }
    cout << result << "\n";
    return 0;
}
