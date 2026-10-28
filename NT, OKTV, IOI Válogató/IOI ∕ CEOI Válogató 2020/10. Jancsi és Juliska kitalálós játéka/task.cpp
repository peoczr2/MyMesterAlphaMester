/*
Megoldás lényege:
Legyen g(l,r) az a minimális összeg, amennyi Jancsinak elég ahhoz, hogy biztosan kitalálja a számot, ha tudjuk, hogy a gondolt szám [l,r]-ben van; g(l,l)=0. Az [a,b] kérdés ára max f[a..b], a válasz után a lehetséges számok a [l,a-1], az [a,b] vagy a [b+1,r] intervallumba esnek, ezért g(l,r) minimuma az (a,b) ≠ (l,r) párokra vett max f[a..b] + max(g(l,a-1), g(a,b), g(b+1,r)) értékeknek. Az intervallumokat hossz szerint növekvő sorrendben töltjük ki, a max f[a..b] értékeket előre tároljuk. Mivel max f[a..b] b növelésével nem csökken, egy (a,b) sor kiértékelését abbahagyjuk, amint a költség már nem lehet jobb a jelenleginél. Legrosszabb esetben ez O(N^4/24) lépés, ami N ≤ 300 esetén belefér az 1 mp-es időlimitbe; a legrosszabb általam próbált, N=300 méretű eset 0,3 mp alatt fut.
*/
/*
Hint 1: || Intervallumokkal dolgozz: írd fel, hogy egy [l,r] tartományban lévő szám megtalálásához mennyi pénz kell, és gondold meg, hogy egyetlen szám esetén ez 0. ||
Hint 2: || Egy [a,b] kérdés után a lehetséges számok három részre esnek: [l,a-1] (-1 válasz), [a,b] (0 válasz) és [b+1,r] (+1 válasz). A kérdés ára a [a,b] szakasz legdrágább f-értéke, és a rossz ágat kell figyelembe venni, vagyis a három részintervallum közül a legnagyobb költséget. ||
Hint 3: || Az összes lehetséges (a,b) párt végigpróbálhatod, a legjobb választ a minimum adja. A maximum f[a..b] értékeket előre számold ki, és az intervallumokat rövidebbtől a hosszabbak felé töltsd ki. Ha a kérdés ára már nagyobb vagy egyenlő a jelenlegi legjobbnál, a b növelését abba lehet hagyni. ||
*/
#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 305;
static int N;
static int f[MAXN];
static int Mx[MAXN][MAXN];  // Mx[a][b] = max f[a..b]
static int G[MAXN][MAXN];   // G[l][r] = g(l,r)
static int GT[MAXN][MAXN];  // GT[r][l] = g(l,r), oszlopos eléréshez

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 1; i <= N; ++i) cin >> f[i];

    for (int a = 1; a <= N; ++a) {
        int m = 0;
        for (int b = a; b <= N; ++b) {
            m = max(m, f[b]);
            Mx[a][b] = m;
        }
    }

    for (int len = 2; len <= N; ++len) {
        for (int l = 1; l + len - 1 <= N; ++l) {
            int r = l + len - 1;
            int best = INT_MAX;
            for (int a = l; a <= r; ++a) {
                int left = (a == l) ? 0 : G[l][a - 1];
                if (Mx[a][a] + left >= best) continue;
                for (int b = a; b <= r; ++b) {
                    int cost = Mx[a][b];
                    if (cost + left >= best) break;
                    if (a == l && b == r) continue;
                    int mid = G[a][b];
                    int right = GT[r][b + 1];
                    int worst = max(left, max(mid, right));
                    best = min(best, cost + worst);
                }
            }
            G[l][r] = best;
            GT[r][l] = best;
        }
    }

    cout << G[1][N] << '\n';
    return 0;
}
