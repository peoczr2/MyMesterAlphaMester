/*
Megoldás lényege: a két vonat útját egy közös idővonalon, percenként szimuláljuk. Minden szakasz egyszerre csak egy vonatot engedhet át, egy vonat a szakasz indulásától az érkezéséig foglalja; a szakaszon álló vonat pontosan akkor indul, amikor a szakasz szabad, és azonos percben az innen indulók közül a Kukutyinból jövő vonatnak van elsőbbsége. Az érkezési és indulási időkből kiolvasható, melyik állomáson járnak egy időben, így a találkozás állomása is megkapható, a várakozás pedig a menetrend szerinti továbbindulás és a tényleges indulás különbsége. Az időigény a percek számával arányos.
*/
/*
Hint 1: || A vonatok ugyanazon a pályán mennek egymással szemben, ezért minden szakaszt csak az egyik vonat foglalhat egyszerre; a foglaltságot a szakasz szabad időpontjával érdemes tárolni. ||
Hint 2: || A találkozás abban az állomásban van, ahol a két vonat egy időben tartózkodik (a bennük lévő intervallumok metszik egymást); a várakozás a tényleges és a menetrendi indulás különbsége. ||
Hint 3: || Percenként haladj előre: előbb a Kukutyinból induló vonat dönt, aztán a másik, így az azonos időpontú indulás szabálya automatikusan teljesül. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long h1, m1, h2, m2;
    cin >> h1 >> m1 >> h2 >> m2;
    int n;
    cin >> n;
    vector<long long> v;
    for (long long x; cin >> x; ) v.push_back(x);

    vector<long long> dist(n + 2, 0), wait(n + 2, 0);
    for (int i = 1; i <= n; ++i) {
        dist[i] = v[2 * (i - 1)];
        wait[i] = v[2 * (i - 1) + 1];
    }
    dist[n + 1] = v[2 * n];

    long long tK = h1 * 60 + m1;
    long long tP = h2 * 60 + m2;

    vector<long long> kDep(n + 2, -1), kArr(n + 2, -1), pDep(n + 2, -1), pArr(n + 2, -1);
    vector<long long> occEnd(n + 2, -1);  // szakasz foglalt vége (kizárt), -1: szabad

    int kst = 0, pst = n + 1;
    long long kReady = tK, pReady = tP;
    bool kDone = false, pDone = false;
    long long kWait = 0, pWait = 0;
    kArr[0] = tK;
    pArr[n + 1] = tP;

    for (long long t = min(tK, tP); !(kDone && pDone); ++t) {
        if (!kDone && kReady <= t) {
            int seg = kst + 1;
            if (occEnd[seg] <= t) {
                kDep[kst] = t;
                kWait += t - kReady;
                long long a = t + dist[seg];
                occEnd[seg] = a;
                ++kst;
                kArr[kst] = a;
                if (kst == n + 1) {
                    kDone = true;
                    kDep[kst] = a;
                } else {
                    kReady = a + wait[kst];
                }
            }
        }
        if (!pDone && pReady <= t) {
            int seg = pst;
            if (occEnd[seg] <= t) {
                pDep[pst] = t;
                pWait += t - pReady;
                long long a = t + dist[seg];
                occEnd[seg] = a;
                --pst;
                pArr[pst] = a;
                if (pst == 0) {
                    pDone = true;
                    pDep[pst] = a;
                } else {
                    pReady = a + wait[pst];
                }
            }
        }
    }

    int meet = -1;
    for (int i = 0; i <= n + 1 && meet < 0; ++i) {
        long long lo = max(kArr[i], pArr[i]);
        long long hi = min(kDep[i], pDep[i]);
        if (lo <= hi) meet = i;
    }

    auto fmt = [](long long x) {
        ostringstream ss;
        ss << setw(2) << setfill('0') << (x / 60) << ':' << setw(2) << setfill('0') << (x % 60);
        return ss.str();
    };

    cout << meet << '\n';
    if (kWait > 0) {
        cout << "Kukutyin\n" << kWait << '\n';
    } else if (pWait > 0) {
        cout << "Pirip\xa2" << "cs\n" << pWait << '\n';
    } else {
        cout << '\n' << 0 << '\n';
    }
    for (int i = 0; i <= n; ++i) cout << fmt(kDep[i]) << ' ';
    cout << fmt(kArr[n + 1]) << '\n';
    for (int i = n + 1; i >= 1; --i) cout << fmt(pDep[i]) << ' ';
    cout << fmt(pArr[0]) << '\n';
    return 0;
}
