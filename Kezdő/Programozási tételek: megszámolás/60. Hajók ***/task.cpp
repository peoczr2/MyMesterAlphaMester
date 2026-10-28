/*
Megoldás lényege:
Városonként megszámoljuk a konténereket egy map segítségével. Ha egy városba c konténer megy, akkor ceil(c/K) hajó indul, és az utolsó hajón K·ceil(c/K) − c hely marad szabadon. A városokat a szabad hely szerint csökkenően, azonos szabad hely esetén a hajók száma szerint csökkenően rendezzük, majd kiírjuk az első három várost (vagy kevesebbet, ha kevesebb város van). Az időigény O(N log N), a memóriaigény O(N).
*/
/*
Hint 1: || Egy városra nézve a hajók száma és a szabad helyek száma a konténerek darabszámából kiszámolható, nem kell hajónként szimulálni. ||
Hint 2: || Számold meg városonként a konténereket egy map<string, int> segítségével. A hajók száma és a szabad hely a darabszámból és K-ból egyetlen osztással és maradékos számítással adódik. ||
Hint 3: || Az eredményeket egy vektorban tárold, rendezd szabad hely szerint csökkenően, egyenlőség esetén hajók száma szerint csökkenően, és írd ki az első legfeljebb három elemet. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    map<string, int> db;
    for (int i = 0; i < n; i++) {
        string varos;
        cin >> varos;
        db[varos]++;
    }
    // (szabad hely, hajók száma, város)
    vector<tuple<int, int, string>> v;
    for (const auto &[varos, c] : db) {
        int hajok = (c + k - 1) / k;
        int szabad = hajok * k - c;
        v.emplace_back(szabad, hajok, varos);
    }
    sort(v.begin(), v.end(), greater<>());
    int lim = min<int>(3, (int)v.size());
    for (int i = 0; i < lim; i++) {
        auto [szabad, hajok, varos] = v[i];
        cout << varos << " " << hajok << " " << szabad << "\n";
    }
    return 0;
}
