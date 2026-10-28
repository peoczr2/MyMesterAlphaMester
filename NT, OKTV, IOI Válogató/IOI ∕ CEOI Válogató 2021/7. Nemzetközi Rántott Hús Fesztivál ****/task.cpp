/*
Megoldás lényege:
Egy i-ből induló túrán a köret (K) +1, a rántott hús (H) -1 az egyensúlyban, az M-et pedig választhatjuk +1-nek vagy -1-nek. A H-t csak akkor tudja Tibi teljes adagként elfogyasztani, ha van nála köret; ha nincs, a számolás véget ér. Először minden M-et körettnek tekintünk: az első olyan pont, ahol az egyensúly negatív lenne, lezárja a túrát (következő kisebb elem veremmel). A lezárásig egy M-et rántott húsnak választva a későbbi egyensúly 2-vel csökken, ezért minden q pontig legfeljebb floor(egyensúly(q)/2) M lehet rántott hús. Ez prefix-korlátos kiválasztás, amelynek maximuma min_q (korlát(q) + q utáni M-ek száma). A minimumot szegmensfával kérdezzük le, a paritás miatt két tömböt használunk. A válasz: a fix H-k száma plus a maximális rántott hús M-ek száma. Az időigény O(N log N).
*/
/*
Hint 1: || Rendeld a köretekhez +1-et, a rántott húsokhoz -1-et, és tekints minden M-et köretnek. Keresd meg minden kezdőpontra azt az első helyet, ahol az egyensúly negatívvá válik; a túra ott nem tud több teljes adagot adni. ||
Hint 2: || Egy M-et rántott húsnak választva az egyensúly a későbbi pontokon 2-vel csökken. Így az i-től q-ig a rántott húsnak választható M-ek száma legfeljebb floor(egyensúly(q)/2), és ezek prefix-korlátok, amelyek mohó vagy min-képlettel kezelhetők. ||
Hint 3: || A prefix-összegekből és M-darabszámokból a korlát-minimum egy szegmensfával lekérdezhető. Mivel a korlát floor-os, a kezdőpont paritását külön kezeld: két tömböt készíts, és a válasz a fix H-k száma plus a maximális M-darab. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Minimum szegmensfa (alulról felfelé, 0-indexelt, [l, r) intervallum).
struct MinTree {
    int n;
    vector<int> t;

    explicit MinTree(const vector<int> &a) : n((int)a.size()), t(2 * a.size()) {
        for (int i = 0; i < n; i++) t[n + i] = a[i];
        for (int i = n - 1; i >= 1; i--) t[i] = min(t[2 * i], t[2 * i + 1]);
    }

    int query(int l, int r) const {
        int res = INT_MAX;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = min(res, t[l++]);
            if (r & 1) res = min(res, t[--r]);
        }
        return res;
    }
};

// Nemnegatív maradék a paritáshoz (negatív számokra is).
static inline int parity(int x) { return ((x % 2) + 2) % 2; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;

    // Prefix tömbök, 1-indexelve: G az egyensúly (K és M: +1, H: -1),
    // H a rántott húsok, MC az M-ek száma.
    vector<int> G(n + 1, 0), H(n + 1, 0), MC(n + 1, 0);
    for (int q = 1; q <= n; q++) {
        char ch = s[q - 1];
        G[q] = G[q - 1] + (ch == 'H' ? -1 : 1);
        H[q] = H[q - 1] + (ch == 'H');
        MC[q] = MC[q - 1] + (ch == 'M');
    }

    // nxt[j]: az első q > j, amelyre G[q] < G[j]; ha nincs ilyen, n+1.
    vector<int> nxt(n + 1, n + 1);
    vector<int> stk;
    for (int j = n; j >= 0; j--) {
        while (!stk.empty() && G[stk.back()] >= G[j]) stk.pop_back();
        nxt[j] = stk.empty() ? n + 1 : stk.back();
        stk.push_back(j);
    }

    // A_p(q) = (G[q] - 2*MC[q]) - ((G[q] paritása) xor p), ahol p a kezdő egyensúly paritása.
    vector<int> A0(n), A1(n);
    for (int q = 1; q <= n; q++) {
        int v = G[q] - 2 * MC[q];
        int gp = parity(G[q]);
        A0[q - 1] = v - gp;
        A1[q - 1] = v - (1 - gp);
    }
    MinTree tree0(A0), tree1(A1);

    string out;
    for (int i = 1; i <= n; i++) {
        int last = nxt[i - 1] - 1;  // az utolsó olyan pont, ameddig a túra érvényes
        long long ans = 0;
        if (last >= i) {
            int c = G[i - 1];
            int pc = parity(c);
            int minA = (pc == 0) ? tree0.query(i - 1, last) : tree1.query(i - 1, last);
            // (minA - c) páros, így a osztás pontos
            int minTerm = (minA - c) / 2;
            int mCnt = MC[last] - MC[i - 1];
            int rank = min(mCnt, MC[last] + minTerm);
            ans = (H[last] - H[i - 1]) + rank;
        }
        out += to_string(ans);
        out += (i == n ? '\n' : ' ');
    }
    cout << out;
    return 0;
}
