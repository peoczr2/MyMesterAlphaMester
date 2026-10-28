/*
Megoldás lényege:
Az utazók a hozzájuk legközelebbi szállodába mennek, ezért a két szálloda közötti határ egy s index: az 1..s települések az elsőbe (p), az s+1..N települések a másodikba (q) utaznak. Minden s-re külön-külön kiszámítjuk a két csoport legolcsóbb szállodáját. Egy csoport költsége „utazók × távolság” összeg, amely előtagösszegekkel (a B_i és a B_i·x_i összegeivel) egy szálloda helyére O(1)-ben kiszámolható. Így s-enként a bal és a jobb oldal legjobb költsége összeadható, és a legkisebb összeg adja a választ. Az idő O(N²), N ≤ 2000 esetén ez néhány millió művelet.
*/
/*
Hint 1: || Az utazók mindig a hozzájuk legközelebbi szállodába mennek. Mivel a települések egy úton vannak, a két szálloda között van egy határ: az első szállodába egy 1..s szakasz, a másodikba az s+1..N szakasz megy. ||
Hint 2: || Ha a határ s, a két csoport külön-külön optimalizálható: az első szálloda az 1..s települések közül kerül ki, a második az s+1..N közül. Így s-enként a két költség összege adja a teljes költséget. ||
Hint 3: || Egy csoport költsége egy szálloda helyére „utazók × távolság” összegek összege. Ha előtagösszegeket tárolsz (a B_i és a B_i · x_i összegeit), bármely szálloda költsége O(1)-ben kiszámítható. Minden s-re végigpróbálhatod a p és q lehetőségeket. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // x[i]: az i. település távolsága az 1. településtől, b[i]: a dolgozók száma
    vector<long long> x(n + 1, 0), b(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        long long a;
        cin >> a >> b[i];
        x[i] = x[i - 1] + a;
    }

    // pb[i] = B_1 + ... + B_i,  px[i] = B_1*x_1 + ... + B_i*x_i
    vector<long long> pb(n + 1, 0), px(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        pb[i] = pb[i - 1] + b[i];
        px[i] = px[i - 1] + b[i] * x[i];
    }

    const long long INF = LLONG_MAX;
    // bal[s]: az 1..s települések legolcsóbb költsége egy p szállodával (p <= s)
    // jobb[s]: az s+1..n települések legolcsóbb költsége egy q szállodával (q > s)
    vector<long long> bal(n + 1, INF), jobb(n + 1, INF);
    vector<int> balP(n + 1, 0), jobbQ(n + 1, 0);

    for (int s = 1; s < n; s++) {
        for (int p = 1; p <= s; p++) {
            // i <= p: x_p - x_i,  p < i <= s: x_i - x_p
            long long c = (x[p] * pb[p] - px[p])
                        + (px[s] - px[p]) - x[p] * (pb[s] - pb[p]);
            if (c < bal[s]) {
                bal[s] = c;
                balP[s] = p;
            }
        }
        for (int q = s + 1; q <= n; q++) {
            // s < i <= q: x_q - x_i,  i > q: x_i - x_q
            long long c = x[q] * (pb[q] - pb[s]) - (px[q] - px[s])
                        + (px[n] - px[q]) - x[q] * (pb[n] - pb[q]);
            if (c < jobb[s]) {
                jobb[s] = c;
                jobbQ[s] = q;
            }
        }
    }

    long long legjobb = INF;
    int ap = 0, as = 0, aq = 0;
    for (int s = 1; s < n; s++) {
        long long c = bal[s] + jobb[s];
        if (c < legjobb) {
            legjobb = c;
            ap = balP[s];
            as = s;
            aq = jobbQ[s];
        }
    }

    cout << legjobb << "\n";
    cout << ap << " " << as << " " << aq << "\n";
    return 0;
}
