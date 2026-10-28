/*
Megoldás lényege:
A robot csak lefelé halad, ezért minden szintet pontosan egyszer jár be: egy szintre a bal (0.) vagy a jobb (M+1.) lépcsőn érkezik, és onnan a bal vagy a jobb lépcsőn megy tovább. A bemenet első szintsora a legalsó szint, az utolsó a legfelső, ahonnan a robot indul. Egy szinten elég a legkisebb (a) és a legnagyobb (b) kincses szoba számát ismerni, mert a köztük lévő kincsek útközben útba esnek. A szintenkénti séta költsége így ugyanazon az oldalon be- és kilépve bal-bal esetben 2b, jobb-jobb esetben 2(M+1-a), oldalt váltva M+1. A DP-ben dp[oldal] az a legkisebb séta-költség, amellyel a robot az adott oldali lépcsőn érkezik a szintre; a legalsó szinten nem kell visszatérni, ott a bal oldali érkezés b, a jobb oldali M+1-a költséggel jár. A végeredmény: a kincsek száma (mindegyik 1 egység), plus a lépcsők száma (N-1), plus a DP minimuma. A teljes idő O(N + összes kincs), mert minden szinten csak konstans számú átmenet van.
*/
/*
Hint 1: || A bemenet első szintsora a legalsó szint, az utolsó a legfelső, ahonnan a robot indul. Mivel a robot csak lefelé léphet, minden szintet pontosan egyszer kell bejárnia. ||
Hint 2: || Egy szinten elég a legkisebb és a legnagyobb kincses szoba sorszámát figyelembe venni, a köztes kincsek útközben útba esnek. Ha a robot ugyanazon az oldalon lép be és ki, oda-vissza kell mennie a szélső kincsig; ha az oldal változik, a teljes szintet át kell sétálnia. ||
Hint 3: || Dinamikus programozás: az állapot az, hogy a robot a szint bal vagy jobb lépcsőjén érkezik. Az összes kincs felvétele és a lépcsők száma (N-1) fix összeg, ezért csak a sétát kell minimalizálni, a legalsó szinten pedig nem kell visszatérni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m;
    cin >> n >> m;

    // i = 0 a legalsó szint, i = n-1 a legfelső (ahonnan a robot indul)
    vector<long long> lo(n, m + 1), hi(n, 0);
    long long treasures = 0;
    for (long long i = 0; i < n; i++) {
        long long c;
        cin >> c;
        treasures += c;
        for (long long j = 0; j < c; j++) {
            long long s;
            cin >> s;
            lo[i] = min(lo[i], s);
            hi[i] = max(hi[i], s);
        }
    }

    const long long INF = LLONG_MAX / 4;
    // dp[0]: a robot a bal (0.) lépcsőn érkezik a szintre, dp[1]: a jobb (M+1.) lépcsőn
    long long dp[2] = {0, INF};
    for (long long i = n - 1; i >= 1; i--) {
        long long nd[2] = {INF, INF};
        for (int from = 0; from < 2; from++) {
            for (int to = 0; to < 2; to++) {
                long long w;
                if (from == 0 && to == 0) w = 2 * hi[i];
                else if (from == 1 && to == 1) w = 2 * (m + 1 - lo[i]);
                else w = m + 1;
                nd[to] = min(nd[to], dp[from] + w);
            }
        }
        dp[0] = nd[0];
        dp[1] = nd[1];
    }

    // a legalsó szinten bárhol véget érhet
    long long walk = min(dp[0] + hi[0], dp[1] + (m + 1 - lo[0]));
    cout << treasures + (n - 1) + walk << '\n';
    return 0;
}
