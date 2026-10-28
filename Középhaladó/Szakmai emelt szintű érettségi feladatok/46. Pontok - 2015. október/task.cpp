/*
Megoldás lényege:
Az első részfeladatban az x tengelyen azok a pontok vannak, amelyeknek y koordinátája 0, az y tengelyen azok, amelyeknek x koordinátája 0; ezeket egyetlen bejárással megszámoljuk. A második részfeladatban a pontokat egy map-be tesszük, ahol a kulcs a koordinátapár, az érték a pontok sorszámainak listája; a map a kulcsokat rendezve tárolja, így a kiírás már x, majd y szerint növekvő sorrendben történik. A harmadik részfeladatban minden i<j pontpárt egyszer vizsgálunk meg (N legfeljebb 200), a távolságnégyzetet egész számmal számoljuk, és nyilvántartjuk az eddigi maximumot és az ezt elérő párok számát. Az időigény O(N^2), a memóriaigény O(N).
*/
/*
Hint 1: || Az 1. részfeladathoz elég külön megszámolni, hány pontnak y=0, illetve x=0 a koordinátája; a 2. részfeladathoz a koordinátapárt használd kulcsként egy map-ben, amely már rendezve tárolja a kulcsokat. ||
Hint 2: || A 3. részfeladatnál két pont távolságnégyzete dx*dx + dy*dy; minden i<j párt pontosan egyszer vizsgálj meg, és közben tartsd nyilván az eddigi maximumot és a rá illeszkedő párok számát. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    // 1. részfeladat: x tengelyen (y = 0), y tengelyen (x = 0) lévő pontok
    int tengelyX = 0, tengelyY = 0;
    for (int i = 0; i < n; i++) {
        if (y[i] == 0) tengelyX++;
        if (x[i] == 0) tengelyY++;
    }
    cout << "#\n" << tengelyX << " " << tengelyY << "\n";

    // 2. részfeladat: azonos koordinátájú pontok
    map<pair<int, int>, vector<int>> hely;
    for (int i = 0; i < n; i++) {
        hely[{x[i], y[i]}].push_back(i + 1);
    }
    cout << "#\n";
    bool van = false;
    for (const auto &[p, idx] : hely) {
        if (idx.size() >= 2) {
            van = true;
            cout << p.first << " " << p.second << ":";
            for (int s : idx) {
                cout << " " << s;
            }
            cout << "\n";
        }
    }
    if (!van) {
        cout << "-1\n";
    }

    // 3. részfeladat: legnagyobb távolságnégyzet és a ilyen pontpárok száma
    int maxd = -1;
    long long db = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dx = x[i] - x[j], dy = y[i] - y[j];
            int d = dx * dx + dy * dy;
            if (d > maxd) {
                maxd = d;
                db = 1;
            } else if (d == maxd) {
                db++;
            }
        }
    }
    cout << "#\n" << maxd << " " << db << "\n";
    return 0;
}
