/*
Megoldás lényege:
A beszerzéseket egyetlen bejárással összegezzük: évenként, könyvkódonként és témakódonként külön összeget vezetünk. Az évekre rendezett map miatt a beszerzési évek növekvő sorrendben állnak, így az 1. és a 2. részfeladat közvetlenül adódik. A 4. részfeladatban két egymást követő beszerzési év között a kihagyott évek száma a különbség mínusz egy, ezek közül a leghosszabbat keressük. A döntetlen eseteket a sorrend dönti el: a korábbi év, illetve a bemeneten először előforduló kód vagy témakód nyer, ezért a szigorú összehasonlítást használjuk. Az időigény O(N log N), a tárigény O(N).
*/
/*
Hint 1: || Készíts három összegző szerkezetet: év szerint, könyvkód szerint és témakód szerint a darabszámok összegét. Az 1., 2. és 4. részfeladat az évenkénti, a 3. a könyvkódonkénti, az 5. a témakódonkénti összegeket használja. ||
Hint 2: || A 4. részfeladatban a szomszédos beszerzési évek közti kihagyott évek száma b - a - 1, és ezek közül a leghosszabbat kell megtartani, döntetlennél az elsőt. Az 5. részfeladatban a témakódokat az első előfordulásuk szerinti sorrendben egy külön listába tedd, mert a kiírás sorrendje ebből adódik. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> kod(n), tk(n), ev(n), db(n);
    for (int i = 0; i < n; i++) cin >> kod[i] >> tk[i] >> ev[i] >> db[i];

    map<int, int> evSum, konyvSum, temaSum;
    vector<int> temaSorrend;
    for (int i = 0; i < n; i++) {
        evSum[ev[i]] += db[i];
        konyvSum[kod[i]] += db[i];
        if (!temaSum.count(tk[i])) temaSorrend.push_back(tk[i]);
        temaSum[tk[i]] += db[i];
    }

    // 1. részfeladat: a legkevesebb, de legalább 1 könyvet szerző év (döntetlennél a korábbi)
    int legk_ev = -1, legk_db = INT_MAX;
    for (const auto &p : evSum) {
        if (p.second >= 1 && p.second < legk_db) {
            legk_db = p.second;
            legk_ev = p.first;
        }
    }
    cout << "#\n" << legk_ev << "\n";

    // 2. részfeladat: a beszerzési évek száma, majd az évek növekvő sorrendben
    vector<int> evek;
    for (const auto &p : evSum) evek.push_back(p.first);
    cout << "#\n" << evek.size() << "\n";
    for (size_t i = 0; i < evek.size(); i++) {
        if (i) cout << ' ';
        cout << evek[i];
    }
    cout << "\n";

    // 3. részfeladat: a legtöbb darabot összegyűjtő könyvkód (döntetlennél az elsőként előfordulló)
    int legt_kod = -1, max_db = -1;
    for (int i = 0; i < n; i++) {
        if (konyvSum[kod[i]] > max_db) {
            max_db = konyvSum[kod[i]];
            legt_kod = kod[i];
        }
    }
    cout << "#\n" << legt_kod << "\n";

    // 4. részfeladat: a leghosszabb beszerzés nélküli időszak az első és az utolsó év között
    int hos_kezd = -1, hos_veg = -1, hos_len = 0;
    for (size_t i = 1; i < evek.size(); i++) {
        int kihagyott = evek[i] - evek[i - 1] - 1;
        if (kihagyott > hos_len) {
            hos_len = kihagyott;
            hos_kezd = evek[i - 1] + 1;
            hos_veg = evek[i] - 1;
        }
    }
    cout << "#\n";
    if (hos_len == 0)
        cout << "-1 -1\n";
    else
        cout << hos_kezd << ' ' << hos_veg << "\n";

    // 5. részfeladat: témakódonkénti darabszám-összeg, az első előfordulás sorrendjében
    cout << "#\n" << temaSorrend.size() << "\n";
    for (int t : temaSorrend) cout << t << ' ' << temaSum[t] << "\n";

    return 0;
}
