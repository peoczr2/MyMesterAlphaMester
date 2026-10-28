/*
Megoldás lényege:
Először kiszűrjük a kieseket: egy kutya akkor marad bent, ha minden szempontban eléri a szempont alsó ponthatárát. Ezután szempontonként összeadjuk a bent maradók pontjait. Mivel minden szempontban ugyanannyi bent maradó kutya van, az átlagok sorrendje megegyezik a pontösszegek sorrendjével, így tört nélkül, egész számokkal dolgozhatunk. A legkisebb összegű szempont sorszámát írjuk ki; egyenlőség esetén a kisebb sorszám marad, mert a minimumot csak szigorúan kisebb összeg írja felül. Ha nincs bent maradó kutya, a válasz 0. Az időigény O(N·M), a memóriaigény O(N·M).
*/
/*
Hint 1: || Egy kutya akkor esik ki, ha valamelyik szempontban a pontja kisebb a szempont alsó ponthatáránál. A kiesett kutya minden szempontban kimarad az átlagból, nem csak abban, ahol kiesett. ||
Hint 2: || Először jelöld meg a bent maradókat, majd szempontonként csak nekik add össze a pontjait. A bent maradók száma minden szempontban azonos, ezért az összegek összehasonlítása ugyanazt a sorrendet adja, mint az átlagoké. ||
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
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (p[i][j] < minPont[j]) bent[i] = false;

    if (count(bent.begin(), bent.end(), true) == 0) {
        cout << 0 << '\n';
        return 0;
    }

    int legkisebbSzempont = -1;
    int legkisebbOsszeg = 0;
    for (int j = 0; j < m; j++) {
        int osszeg = 0;
        for (int i = 0; i < n; i++)
            if (bent[i]) osszeg += p[i][j];
        if (legkisebbSzempont == -1 || osszeg < legkisebbOsszeg) {
            legkisebbOsszeg = osszeg;
            legkisebbSzempont = j;
        }
    }

    cout << legkisebbSzempont + 1 << '\n';
    return 0;
}
