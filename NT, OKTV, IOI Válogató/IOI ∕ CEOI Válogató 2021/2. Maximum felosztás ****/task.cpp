/*
Megoldás lényege:
Mivel a B-beli értékek különbözők, az i-edik szakaszt egyértelműen azonosítja az első B_i-előfordulása benne (p_i), így minden felosztás pontosan egyszer számolódik.
A p_i-t tartalmazó szakasz vége csak p_i és az első utána következő nála nagyobb elem között lehet, az (i+1)-edik szakasz eleje pedig nem nyúlhat vissza a p_{i+1} előtti utolsó nagyobb elemen és az előző B_{i+1}-előfordulásén túl.
Így F(y) = sum_{c=L(y)}^{y-1} Q(c), ahol Q(c) az összes olyan x (B_i-előfordulás) F(x) értékének összege, amelyre x <= c <= H(x).
A Q-t tartomány-hozzáadó, tartomány-összegző Fenwick-fával kezeljük, a lépés után az intervallumokat visszavonjuk.
A határokat ritka táblázattal (sparse table) bináris ugrással keressük, az összidő O((N+M) log N).
*/
/*
Hint 1: || Minden B_i-hez csak az A-beli előfordulásai kellenek; az i-edik szakasz akkor jó, ha tartalmaz B_i-t és nincs benne nála nagyobb elem. Válaszd kanonikusan a szakasz első B_i-előfordulását, így minden felosztás pontosan egyszer számolódik. ||
Hint 2: || Az i-edik és az (i+1)-edik szakasz közti vágás c helyére két feltétel van: c legalább az i-edik szakaszban választott előfordulás, legfeljebb az első nála nagyobb elem előtti pozíció, továbbá legalább az (i+1)-edik szakasz előfordulása előtti utolsó nagyobb elem és az előző B_{i+1}-előfordulás. ||
Hint 3: || Egy vágás-DP-értékekből álló tömbre minden előfordulás egy tartomány-hozzáadásnak felel meg, a következő előfordulások értékei pedig tartomány-összegek. Két tömböt használó Fenwick-fa (tartomány-hozzáadás, tartomány-összegzés) elég. ||
*/
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;

// Tartomány-hozzáadás és tartomány-összegzés Fenwick-fával, modulo MOD, 1-indexelt.
struct RangeFenwick {
    int n;
    vector<long long> b1, b2;
    explicit RangeFenwick(int n) : n(n), b1(n + 2, 0), b2(n + 2, 0) {}
    void upd(vector<long long>& b, int i, long long v) {
        for (; i <= n; i += i & -i) b[i] = (b[i] + v) % MOD;
    }
    long long qry(const vector<long long>& b, int i) const {
        long long s = 0;
        for (; i > 0; i -= i & -i) s += b[i];
        return s % MOD;
    }
    // [l, r] tartomány minden eleméhez hozzáadja v-t
    void add(int l, int r, long long v) {
        v %= MOD;
        upd(b1, l, v);
        upd(b1, r + 1, (MOD - v) % MOD);
        upd(b2, l, v * (l - 1) % MOD);
        upd(b2, r + 1, (MOD - v * r % MOD) % MOD);
    }
    long long pref(int x) const {
        return ((qry(b1, x) * x - qry(b2, x)) % MOD + MOD) % MOD;
    }
    // [l, r] tartomány összege
    long long sum(int l, int r) const {
        return ((pref(r) - pref(l - 1)) % MOD + MOD) % MOD;
    }
};

int N, M, LOGN;
vector<int> A;               // A[1..N]
vector<vector<int>> sp;      // sp[k][i] = max(A[i..i+2^k-1])

// Legkisebb p >= l, amelyre A[p] > v; ha nincs, N+1.
int firstGreater(int l, int v) {
    int pos = l;
    for (int k = LOGN; k >= 0; --k)
        if (pos + (1 << k) - 1 <= N && sp[k][pos] <= v) pos += 1 << k;
    return pos;
}

// Legnagyobb p <= r, amelyre A[p] > v; ha nincs, 0.
int lastGreater(int r, int v) {
    int pos = r;
    for (int k = LOGN; k >= 0; --k)
        if (pos - (1 << k) >= 0 && sp[k][pos - (1 << k) + 1] <= v) pos -= 1 << k;
    return pos;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    A.assign(N + 2, 0);
    for (int i = 1; i <= N; i++) cin >> A[i];
    vector<int> B(M + 1);
    for (int i = 1; i <= M; i++) cin >> B[i];

    LOGN = 0;
    while ((1 << (LOGN + 1)) <= N) LOGN++;
    sp.assign(LOGN + 1, vector<int>(N + 2, 0));
    for (int i = 1; i <= N; i++) sp[0][i] = A[i];
    for (int k = 1; k <= LOGN; k++)
        for (int i = 1; i + (1 << k) - 1 <= N; i++)
            sp[k][i] = max(sp[k - 1][i], sp[k - 1][i + (1 << (k - 1))]);

    // B-értékek sorszáma, és az A-beli előfordulásaik pozíciói (növekvő sorrendben)
    unordered_map<int, int> bidx;
    for (int i = 1; i <= M; i++) bidx[B[i]] = i;
    vector<vector<int>> O(M + 2);
    for (int x = 1; x <= N; x++) {
        auto it = bidx.find(A[x]);
        if (it != bidx.end()) O[it->second].push_back(x);
    }
    for (int i = 1; i <= M; i++)
        if (O[i].empty()) {
            cout << 0 << '\n';
            return 0;
        }

    // Minden előfordulásra: L = a vágás alsó határa, H = a szakasz felső határa
    vector<vector<int>> Lb(M + 2), Hb(M + 2);
    for (int i = 1; i <= M; i++) {
        int v = B[i], sz = (int)O[i].size();
        Lb[i].resize(sz);
        Hb[i].resize(sz);
        for (int k = 0; k < sz; k++) {
            int y = O[i][k];
            int g = lastGreater(y - 1, v);
            int prevOcc = k > 0 ? O[i][k - 1] : 0;
            Lb[i][k] = max(g, prevOcc);
            Hb[i][k] = firstGreater(y + 1, v) - 1;
        }
    }

    // F[k]: hány részfelosztás van, amelyben az i-edik szakasz kanonikus kezdete O[i][k]
    RangeFenwick bit(N + 1);  // a c vágáspontot a c+1 index jelöli (c = 0..N)
    vector<long long> F(O[1].size()), NF;
    for (size_t k = 0; k < F.size(); k++) F[k] = (Lb[1][k] == 0) ? 1 : 0;

    for (int i = 1; i < M; i++) {
        for (size_t k = 0; k < O[i].size(); k++)
            bit.add(O[i][k] + 1, Hb[i][k] + 1, F[k]);
        NF.assign(O[i + 1].size(), 0);
        for (size_t k = 0; k < O[i + 1].size(); k++)
            NF[k] = bit.sum(Lb[i + 1][k] + 1, O[i + 1][k]);
        for (size_t k = 0; k < O[i].size(); k++)
            bit.add(O[i][k] + 1, Hb[i][k] + 1, (MOD - F[k]) % MOD);
        F = NF;
    }

    long long ans = 0;
    for (size_t k = 0; k < O[M].size(); k++)
        if (Hb[M][k] == N) ans = (ans + F[k]) % MOD;
    cout << ans << '\n';
    return 0;
}
