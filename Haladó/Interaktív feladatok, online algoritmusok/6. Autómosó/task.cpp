/*
Megoldás lényege:
Mosónként tároljuk az oda beállt autók befejezési idejét. A sor sorrendben működik, és egy autó mosása csak az előző befejezése után kezdődhet, ezért ez a lista nemcsökkenő. Egy mosónál akkor áll K-nál kevesebb autó, ha az utolsó K befejezési idő közül a legkisebb (a K-adik utolsó) már nem nagyobb x-nél. Így minden mosóra közvetlenül kiszámolható, mikortól van benne szabad hely: T = max(e, K-adik utolsó befejezés). Ha minden mosó tele van, az autó a legkorábbi T időpontig vár, és azok közül a mosók közül, amelyek ekkor szabadok, a legkorábban befejezőt választja: a befejezés max(T, utolsó befejezés) + t. Autónként O(L) munka, a teljes idő O(N · L).
*/
/*
Hint 1: || Az autó a legkorábbi befejezést keresi, ezért mosónként elég az utolsó befejezési időket ismerni. A kérdés az, hogy melyik mosónál és mikor lesz K-nál kevesebb autó. ||
Hint 2: || Mosónként a befejezési idők növekvő sorrendben vannak. Egy mosónál akkor van K-nál kevesebb autó, ha a K-adik utolsó befejezési idő már nem nagyobb a vizsgált időpontnál, így ez az időpont közvetlenül kiszámolható. ||
Hint 3: || Ha minden mosó tele van, az autó a legkorábbi szabad időpontig vár. Ekkor a szabad mosók közül azt válaszd, amelynél a befejezés a legkorábbi: ez a mosó utolsó befejezési ideje és a várakozás vége közül a nagyobbhoz adja hozzá a mosási időt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int L, K;
    cin >> L >> K;

    // fin[j]: a j. mosóba beállt autók befejezési idői, nemcsökkenő sorrendben.
    vector<vector<long long>> fin(L);
    vector<long long> freeAt(L);

    long long e, t;
    while (cin >> e >> t) {
        if (e == 0 && t == 0) break;

        // freeAt[j]: az első időpont (e-től), amikor a j. mosónál K-nál kevesebb autó áll.
        long long x = LLONG_MAX;
        for (int j = 0; j < L; ++j) {
            long long m = fin[j].size();
            freeAt[j] = (m >= K) ? max(e, fin[j][m - K]) : e;
            x = min(x, freeAt[j]);
        }

        // Az x időpontban szabad mosók közül a legkorábban befejezőt választjuk.
        int best = -1;
        long long bestFin = 0;
        for (int j = 0; j < L; ++j) {
            if (freeAt[j] != x) continue;
            long long last = fin[j].empty() ? 0 : fin[j].back();
            long long f = max(x, last) + t;
            if (best < 0 || f < bestFin) {
                best = j;
                bestFin = f;
            }
        }

        fin[best].push_back(bestFin);
        cout << bestFin << '\n';
    }
    return 0;
}
