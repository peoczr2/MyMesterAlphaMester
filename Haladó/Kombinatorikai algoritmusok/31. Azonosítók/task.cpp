/*
Megoldás lényege:
Az N betűből álló, M hosszú, szigorúan növekvő azonosítók lexikografikus
sorrendje megegyezik a kombinációk megszokott sorrendjével, ezért a feladat
lényegében sorszámozási kérdés.
Először kiszámoljuk az A azonosító sorszámát: pozíciónként összeadjuk azoknak a
lehetséges, A-nál kisebb betűknek a binomiális együtthatóit, amelyekkel az adott
pozíción kisebb azonosító állhatna, a hátralévő helyek száma szerint.
Ehhez hozzáadjuk K-t, majd a kapott sorszámból balról jobbra haladva
visszaépítjük a célazonosítót: minden pozícióban azt a legkisebb betűt
választjuk, amelynek blokkja még tartalmazza a hátralévő sorszámot.
A binomiális együtthatókat egy 27 x 27-es Pascal-háromszögben tároljuk, így az
algoritmus O(N·M) időben fut, ami a 0,01 másodperces időlimithez is bőven elég.
*/
/*
Hint 1: || Az azonosítókat nem kell felsorolni: a szigorúan növekvő
betűsorozatok lexikografikus sorrendje ugyanaz, mint a 0-tól N-1-ig terjedő
számok M-elemű kombinációinak sorrendje, így elég a sorszámokkal dolgozni. ||
Hint 2: || Számoljuk meg, hány A előtti azonosító van. Ha egy pozíción a c betűt
választjuk, a hátralévő helyeket a c utáni betűkből kell kitölteni, és ennek
száma egy binomiális együttható. A teljes sorszám ezeknek az összege. ||
Hint 3: || A célsorszám (A sorszáma + K) alapján balról jobbra haladva próbáljuk
ki a betűket: a c betű blokkjának mérete a hátralévő helyek binomiális
együtthatója. Ha ez kisebb vagy egyenlő a céllal, levonjuk és a következő betűt
nézzük, különben a c betű következik. ||
*/

#include <bits/stdc++.h>
using namespace std;

static const long long INF = (1LL << 60);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    long long K;
    if (!(cin >> N >> M >> K)) return 0;

    string s;
    cin >> s;

    vector<vector<long long>> C(27, vector<long long>(27, 0));
    for (int n = 0; n <= 26; ++n) {
        C[n][0] = C[n][n] = 1;
        for (int k = 1; k < n; ++k) {
            C[n][k] = min(INF, C[n - 1][k - 1] + C[n - 1][k]);
        }
    }

    vector<int> a(M);
    for (int i = 0; i < M; ++i) a[i] = s[i] - 'a';

    long long rank = 0;
    int prev = -1;
    for (int i = 0; i < M; ++i) {
        for (int c = prev + 1; c < a[i]; ++c) {
            rank += C[N - c - 1][M - i - 1];
        }
        prev = a[i];
    }

    long long target = rank + K;
    string ans;
    ans.reserve(M);
    prev = -1;
    for (int i = 0; i < M; ++i) {
        int rem = M - i - 1;
        for (int c = prev + 1; c <= N - rem - 1; ++c) {
            long long cnt = C[N - c - 1][rem];
            if (cnt <= target) {
                target -= cnt;
            } else {
                ans.push_back(char('a' + c));
                prev = c;
                break;
            }
        }
    }

    cout << ans << '\n';
    return 0;
}