/*
Feladat: a banda gyökeres fa (főnök: 1, az i. tag közvetlen főnöke S[i] < i). Mindenki csak a
közvetlen főnökét és a közvetlen beosztottjait ismeri. A tagok legnagyobb olyan részhalmaza kell,
amelyben senki sem ismer senkit, a tagok növekvő sorrendjében.

Megoldási ötlet: maximális független halmaz fán, két állapottal csúcsonként:
- dp1[v]: a legjobb halmaz mérete v részfájában, ha v benne van;
- dp0[v]: ugyanez, ha v nincs benne.
dp1[v] = 1 + Σ dp0[c], dp0[v] = Σ max(dp0[c], dp1[c]) (c: v közvetlen beosztottjai).
Mivel S[i] < i, az i = N..2 sorrendben minden gyerek a szülője előtt kerül sorra, így rekurzió
(és mély fán veremtúlcsordulás) nélkül számolhatunk. A visszaépítés i = 1..N sorrendben megy:
v bekerül, ha a főnöke nincs bent és dp1[v] > dp0[v]. A szigorú > (egyenlőségnél kihagyjuk v-t)
pontosan a hivatalos kimeneteket adja; a feladat nem írja, hogy bármely optimális halmaz elfogadott.

Idő: O(N), memória: O(N).
*/
/*
Hint 1: || Ha egy tagot beveszel, a főnöke és a közvetlen beosztottjai kimaradnak. Elég csúcsonként egyetlen szám, vagy azt is tudnod kell, hogy maga a tag bent van-e? ||
Hint 2: || Két állapot tagonként: dp1[v] = a legjobb halmaz v részfájában, ha v bent van, dp0[v] = ha nincs bent. A beosztottak részfái függetlenek, az értékeik összeadódnak. ||
Hint 3: || dp1[v] = 1 + Σ dp0[c], dp0[v] = Σ max(dp0[c], dp1[c]). Mivel S[i] < i, az i = N..2 sorrend jó, nem kell rekurzió. Visszaépítés i = 1..N sorrendben: v bekerül, ha a főnöke nincs bent és dp1[v] > dp0[v]. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Beolvasás: S[i] az i. tag főnöke (i = 2..N)
    int n;
    cin >> n;
    vector<int> S(n + 1, 0);
    for (int i = 2; i <= n; i++) cin >> S[i];

    // Kezdőértékek: egy tag magában: dp0 = 0, dp1 = 1
    vector<int> dp0(n + 1, 0), dp1(n + 1, 1);

    // Átmenet: i csökkenő sorrendben i már kész, amikor hozzáadjuk a főnökéhez
    for (int i = n; i >= 2; i--) {
        dp1[S[i]] += dp0[i];
        dp0[S[i]] += max(dp0[i], dp1[i]);
    }

    // Rekonstrukció felülről lefelé (i növekvő: a főnökről már döntöttünk).
    // Szigorú >: egyenlőségnél kihagyjuk v-t, így pontosan a hivatalos kimenetet kapjuk.
    vector<bool> bent(n + 1, false);
    int db = 0;
    for (int v = 1; v <= n; v++) {
        bool fonokBent = (v > 1 && bent[S[v]]);
        bent[v] = !fonokBent && dp1[v] > dp0[v];
        if (bent[v]) db++;
    }

    // Kiírás: darabszám (= max(dp0[1], dp1[1])), majd a tagok növekvő sorrendben
    cout << db << '\n';
    bool elso = true;
    for (int v = 1; v <= n; v++) {
        if (!bent[v]) continue;
        if (!elso) cout << ' ';
        cout << v;
        elso = false;
    }
    cout << '\n';
    return 0;
}
