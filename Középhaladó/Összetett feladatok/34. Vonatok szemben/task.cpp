/*
Megoldás lényege:
Az időt percenként léptetjük, és minden percben előbb a Kukutyinból, majd a Piripócsról induló vonatot vizsgáljuk, így az azonos időpontban érkező indulások közül a Kukutyinból jövő kap elsőbbséget. Egy vonat a következő szakaszára akkor léphet be, ha a szakaszt a szembejövő vonat nem foglalja: a foglalás a belépéstől az érkezésig tart, és az érkezés pillanatában a szakasz már szabad. Ha a szakasz foglalt, a vonat az állomáson marad, és a kényszerű várakozás a tényleges indulás és a tervezett kész idő különbsége. A terv szerinti érkezések a tervezett várakozások összegzésével adódnak, a találkozó állomás a kényszerű várakozás helye, a leghosszabb megálló nélküli szakasz pedig vonatonként a tényleges megállások alapján keresendő. Az időlépések száma a bemeneti indulási időkkel és az utazási idők összegével arányos, ami néhány tízezer, így a futás bőven belefér az időkorlátba.
*/
/*
Hint 1: || Szimuláld az időt percenként: minden vonat csak akkor léphet be a következő szakaszra, ha a szembejövő vonat éppen nem foglalja azt, és a foglalás az érkezés pillanatában már véget ér. ||
Hint 2: || Egy szakaszon csak a szembe haladó vonat ütközhet, ezért elég minden szakasznál rögzíteni, mikor lépett be rá melyik vonat és mikor ért ki. Ha valamelyik vonat a foglalt szakasz miatt várakozik, a többletidő a belépés és a tervezett kész idő különbsége. ||
Hint 3: || Az 1. és a 2. részfeladatot a tervezett várakozásokkal számold, a 4. és 5. részfeladatot viszont a tényleges megállásokkal: kényszerű várakozás is megállás. Az 5. részfeladatnál vonatonként keresd a leghosszabb egymás utáni, egyik állomáson sem megálló állomássorozatot. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long kInd, pInd;
    int n;
    cin >> kInd >> pInd >> n;

    // d[i]: az (i-1). és az i. állomás közötti út ideje, i = 1..n+1
    // kw[i]: a Kukutyinból induló vonat tervezett várakozása az i. állomáson
    // pw[i]: a Piripócsról induló vonat tervezett várakozása az i. állomáson
    vector<long long> d(n + 2, 0), kw(n + 2, 0), pw(n + 2, 0);
    for (int i = 1; i <= n + 1; ++i) cin >> d[i];
    for (int i = 1; i <= n; ++i) cin >> kw[i];
    for (int k = 0; k < n; ++k) {
        long long v;
        cin >> v;
        pw[n - k] = v;
    }

    // 2. részfeladat: érkezési idők ütközés nélkül
    long long kIdeal = kInd;
    for (int i = 1; i <= n + 1; ++i) {
        kIdeal += d[i];
        if (i <= n) kIdeal += kw[i];
    }
    long long pIdeal = pInd;
    for (int s = n + 1; s >= 1; --s) {
        pIdeal += d[s];
        if (s - 1 >= 1) pIdeal += pw[s - 1];
    }

    // szimuláció: a szakaszok foglaltsága (belépés, érkezés), kényszerű várakozások,
    // és az állomásokon tartózkodás (érkezés, indulás)
    const long long INF = LLONG_MAX / 4;
    vector<long long> kEnter(n + 2, -1), kArr(n + 2, -1), pEnter(n + 2, -1), pArr(n + 2, -1);
    vector<long long> kF(n + 2, 0), pF(n + 2, 0);
    vector<long long> kA(n + 2, -1), kD(n + 2, INF), pA(n + 2, -1), pD(n + 2, INF);
    kA[0] = kInd;
    pA[n + 1] = pInd;

    int ks = 0, ps = n + 1;
    long long kReady = kInd, pReady = pInd;
    bool kDone = false, pDone = false;
    for (long long t = 0; !(kDone && pDone); ++t) {
        if (!kDone && t >= kReady) {
            int seg = ks + 1;
            bool blocked = pEnter[seg] >= 0 && pEnter[seg] <= t && t < pArr[seg];
            if (!blocked) {
                kEnter[seg] = t;
                kArr[seg] = t + d[seg];
                kF[ks] += t - kReady;
                kD[ks] = t;
                ks = seg;
                kA[ks] = kArr[seg];
                if (ks == n + 1) kDone = true;
                else kReady = kArr[seg] + kw[ks];
            }
        }
        if (!pDone && t >= pReady) {
            int seg = ps;
            bool blocked = kEnter[seg] >= 0 && kEnter[seg] <= t && t < kArr[seg];
            if (!blocked) {
                pEnter[seg] = t;
                pArr[seg] = t + d[seg];
                pF[ps] += t - pReady;
                pD[ps] = t;
                ps = ps - 1;
                pA[ps] = pArr[seg];
                if (ps == 0) pDone = true;
                else pReady = pArr[seg] + pw[ps];
            }
        }
    }

    // 1. részfeladat: állomások, ahol egyik vonat sem tervezett megállást
    int p1 = 0;
    for (int i = 1; i <= n; ++i)
        if (kw[i] == 0 && pw[i] == 0) p1++;

    // 3. részfeladat: a találkozás állomása (ahol a vonat kényszerűen várakozik)
    int meet = -1;
    for (int i = 0; i <= n + 1 && meet == -1; ++i)
        if (kF[i] > 0 || pF[i] > 0) meet = i;
    if (meet == -1) {
        meet = 0;
        for (int i = 1; i <= n; ++i)
            if (kA[i] <= pD[i] && pA[i] <= kD[i]) {
                meet = i;
                break;
            }
    }

    // 4. részfeladat: többlet várakozás és a várakozó vonat végállomásának kezdőbetűje
    long long sumK = 0, sumP = 0;
    for (int i = 0; i <= n + 1; ++i) {
        sumK += kF[i];
        sumP += pF[i];
    }
    string letter;
    if (sumK > 0) letter += 'K';
    if (sumP > 0) letter += 'P';

    // 5. részfeladat: leghosszabb szakasz, ahol valamelyik vonat egyik állomáson sem állt meg
    int bestLen = 0, bestA = 0, bestB = 0;
    for (int who = 0; who < 2; ++who) {
        vector<bool> stop(n + 2, false);
        for (int i = 1; i <= n; ++i)
            stop[i] = (who == 0) ? (kw[i] > 0 || kF[i] > 0) : (pw[i] > 0 || pF[i] > 0);
        int i = 1;
        while (i <= n) {
            if (stop[i]) {
                ++i;
                continue;
            }
            int a = i;
            while (i <= n && !stop[i]) ++i;
            int len = i - a;
            if (len > bestLen) {
                bestLen = len;
                bestA = a;
                bestB = i - 1;
            }
        }
    }

    cout << "#\n";
    cout << p1 << "\n";

    cout << "#\n";
    cout << kIdeal << " " << pIdeal << "\n";

    cout << "#\n";
    cout << meet << "\n";

    cout << "#\n";
    if (sumK + sumP == 0) cout << "0\n";
    else cout << (sumK + sumP) << " " << letter << "\n";

    cout << "#\n";
    if (bestLen == 0) cout << "0\n";
    else cout << bestA << " " << bestB << "\n";

    return 0;
}
