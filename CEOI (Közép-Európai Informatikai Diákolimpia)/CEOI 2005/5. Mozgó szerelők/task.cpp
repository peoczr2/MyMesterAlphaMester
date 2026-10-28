/*
Megoldás lényege:
A kérések sorrendjében haladó dinamikus programozás. Az utolsó kérés helyén mindig áll egy szerelő, így egy állapot elég: az utolsó kérés helye és a másik két szerelő helye (egy pár, O(L^2) lehetőség). Egy új kérésnél, ha a helyen már áll szerelő, az ingyen kiszolgál; különben a három szerelő közül valamelyik odautazik, és az átmenet költsége C(honnan, hova). A DP-minimumok mellé tároljuk, honnan indult a szerelő, így visszakövetéssel az egyes kérések kiszolgálóit is meg tudjuk határozni. Az időigény O(N * L^2), a memóriaigény a visszakövetéshez O(N * L^2) bájt.
*/
/*
Hint 1: || Mindig pontosan egy szerelő áll a legutóbbi kérés helyén, így az állapot elég a másik két szerelő helye (x, y) és a legutóbbi kérés helye. Ezzel dinamikus programozás írható a kérések sorrendjében. ||
Hint 2: || Ha az új kérés helyén már áll szerelő, az költségmentesen kiszolgálja. Különben a három szerelő közül egy utazik oda, és az átmenet költsége a C[honnan][hova] érték; minden állapotra mindhárom lehetőséget vedd figyelembe. ||
Hint 3: || A visszakövetéshez kérésenként tárold, honnan indult el a szerelő (vagy 0, ha nem kellett utaznia). Az utolsó állapotból visszafelé haladva a korábbi állapot pár is megkapható, a végén pedig a kezdeti helyekről (1, 2, 3) szimulálva kiosztható a szerelők sorszáma. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int L, N;
    cin >> L >> N;
    vector<vector<int>> C(L + 1, vector<int>(L + 1, 0));
    for (int i = 1; i <= L; i++)
        for (int j = 1; j <= L; j++)
            cin >> C[i][j];

    // K[0] = 1: a kezdeti állapot az 1-es helyen álló szerelőt tekinti "utolsónak",
    // a másik két szerelő a 2. és a 3. helyen van.
    vector<int> K(N + 1, 0);
    K[0] = 1;
    for (int i = 1; i <= N; i++) cin >> K[i];

    // Állapot: rendezett (x < y) pár a másik két szerelő helyéből.
    auto tri = [](int x, int y) { return y * (y - 1) / 2 + x; };
    const int S = L * (L - 1) / 2 + L + 1;
    const int INF = INT_MAX / 4;

    vector<int> dp(S, INF), ndp(S, INF);
    // from[i][state]: a kérés kiszolgálásához utazó szerelő indulási helye (0: nem utazott).
    vector<vector<unsigned char>> from(N + 1, vector<unsigned char>(S, 0));
    dp[tri(2, 3)] = 0;

    for (int i = 1; i <= N; i++) {
        int p = K[i - 1], q = K[i];
        fill(ndp.begin(), ndp.end(), INF);

        auto relax = [&](int x, int y, int val, int f) {
            int idx = tri(x, y);
            if (val < ndp[idx]) {
                ndp[idx] = val;
                from[i][idx] = (unsigned char)f;
            }
        };

        for (int y = 2; y <= L; y++) {
            for (int x = 1; x < y; x++) {
                int idx = tri(x, y);
                if (dp[idx] >= INF) continue;
                if (x == p || y == p) continue;  // az aktuális hely nem lehet a pár eleme
                int cur = dp[idx];

                if (q == p) {
                    relax(x, y, cur, 0);
                } else if (q == x || q == y) {
                    int other = (q == x) ? y : x;
                    relax(min(p, other), max(p, other), cur, 0);
                } else {
                    // p-ről utazik a szerelő: a pár marad (x, y)
                    relax(x, y, cur + C[p][q], p);
                    // x-ről utazik: az új pár (p, y)
                    relax(min(p, y), max(p, y), cur + C[x][q], x);
                    // y-ról utazik: az új pár (p, x)
                    relax(min(p, x), max(p, x), cur + C[y][q], y);
                }
            }
        }
        swap(dp, ndp);
    }

    // Legjobb végállapot.
    int best = INF, bx = 0, by = 0;
    for (int y = 2; y <= L; y++)
        for (int x = 1; x < y; x++)
            if (dp[tri(x, y)] < best) {
                best = dp[tri(x, y)];
                bx = x;
                by = y;
            }

    // Visszakövetés: minden kéréshez a szerelő indulási helye.
    vector<int> fr(N + 1, 0);
    int x = bx, y = by;
    for (int i = N; i >= 1; i--) {
        int p = K[i - 1], q = K[i];
        int f = from[i][tri(x, y)];
        fr[i] = f;
        if (x == p || y == p) {
            // Az előző állapot: a másik szerelő (other) és a kérés helyét elfoglaló szerelő.
            int other = (x == p) ? y : x;
            int a = (f == 0) ? q : f;
            x = min(a, other);
            y = max(a, other);
        }
    }

    // Kiosztás: a szerelők azonosítói (1, 2, 3) a kezdeti helyeikből (1, 2, 3) követhetők.
    int pos[4] = {0, 1, 2, 3};
    vector<int> ans(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        int q = K[i], f = fr[i];
        int who;
        if (f == 0) {
            who = (pos[1] == q) ? 1 : (pos[2] == q ? 2 : 3);
        } else {
            who = (pos[1] == f) ? 1 : (pos[2] == f ? 2 : 3);
            pos[who] = q;
        }
        ans[i] = who;
    }

    cout << best << '\n';
    for (int i = 1; i <= N; i++) {
        cout << ans[i] << (i == N ? '\n' : ' ');
    }
    return 0;
}
