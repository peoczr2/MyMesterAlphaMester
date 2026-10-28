/*
Megoldás lényege: az i-edik rész maximuma B_i, ezért minden részt az utolsó B_i-előfordulásával
azonosítunk az adott részben, így minden felosztás pontosan egyszer számolódik. Egy p előfordulásra
a rész kezdete a p előtti legközelebbi nagyobb elem utáni pozíció, a vége pedig a p utáni első
nagyobb elem vagy a következő B_i előtti pozíció lehet; ezeket egy rendezett halmazzal kapjuk meg.
A DP-réteg (az első i rész az r-edik elemig) ilyen intervallumok diszjunkt halmazaként írható le,
így egy átmenet súlya prefixösszegekkel és bináris kereséssel O(log N) alatt számolható.
Az összidő O(N log N), ami N, M <= 10^5 mellett is belefér az 1 másodpercbe.
*/
/*
Hint 1: || Egy rész maximuma pontosan B_i, ha tartalmazza B_i-t, és nincs benne nála nagyobb elem. Minden részt egyértelműen hozzárendelhetsz az utolsó B_i-előfordulásához, így nem számolsz kétszer. ||
Hint 2: || Egy p előfordulásnál a rész kezdete a p előtti legközelebbi nagyobb elem után lehet, a vége pedig a p utáni első nagyobb elem előtt, és a következő B_i előfordulása előtt. Az „aktív” pozíciókat (nagyobbak az aktuális értéknél) rendezett halmazban tartva ez gyorsan megvan. ||
Hint 3: || A DP-réteg csak ezeken az intervallumokon nem nulla, és az intervallumok diszjunktak. Az átmenet súlya a korábbi réteg egy összegének felel meg, amit prefixösszegekkel és bináris kereséssel adsz meg. ||
Hint 4: || Az O(N * M) méretű táblázatos DP N, M = 10^5 mellett túl lassú; rétegenként csak az előfordulások számával arányos munka kell. ||
*/
#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 1000000007LL;

struct Occ {
    int p;
    int l;
    int u;
};

struct Piece {
    int p;
    int u;
    long long w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<int> A(N + 1), B(M + 1);
    for (int i = 1; i <= N; ++i) cin >> A[i];
    for (int i = 1; i <= M; ++i) cin >> B[i];

    unordered_map<int, vector<int>> positions;
    positions.reserve(N * 2);
    for (int i = 1; i <= N; ++i) positions[A[i]].push_back(i);

    vector<pair<int, int>> sortedA;
    sortedA.reserve(N);
    for (int i = 1; i <= N; ++i) sortedA.push_back({A[i], i});
    sort(sortedA.begin(), sortedA.end(), greater<pair<int, int>>());

    vector<pair<int, int>> parts;
    parts.reserve(M);
    for (int i = 1; i <= M; ++i) parts.push_back({B[i], i});
    sort(parts.begin(), parts.end(), greater<pair<int, int>>());

    // info[i]: az i-edik rész lehetséges végpontjai az előfordulásaiból
    vector<vector<Occ>> info(M + 1);
    set<int> active;
    int ptr = 0;

    for (int idx = 0; idx < M; ++idx) {
        int value = parts[idx].first;
        int partIndex = parts[idx].second;

        while (ptr < N && sortedA[ptr].first > value) {
            active.insert(sortedA[ptr].second);
            ++ptr;
        }

        const vector<int>& occ = positions[value];
        if (occ.empty()) {
            cout << 0 << '\n';
            return 0;
        }

        for (int j = 0; j < (int)occ.size(); ++j) {
            int p = occ[j];
            int nextOcc = (j + 1 < (int)occ.size() ? occ[j + 1] : N + 1);

            auto it = active.lower_bound(p);
            int R = (it == active.end() ? N + 1 : *it);
            int L = 0;
            if (it != active.begin()) L = *prev(it);

            int U = min(R - 1, nextOcc - 1);
            info[partIndex].push_back({p, L, U});
        }
    }

    // A DP-réteg darabok listája: [p, u] intervallumon a w súly, a darabok diszjunktak
    // és p szerint rendezettek. dp_0 csak a 0. helyen 1.
    vector<Piece> prevP = {{0, 0, 1}};
    for (int partIndex = 1; partIndex <= M; ++partIndex) {
        const int K = prevP.size();
        vector<int> starts(K);
        vector<long long> pre(K + 1, 0);  // pre[k]: az első k darab teljes összege
        for (int k = 0; k < K; ++k) {
            starts[k] = prevP[k].p;
            pre[k + 1] = (pre[k] + prevP[k].w * (prevP[k].u - prevP[k].p + 1)) % MOD;
        }
        // G(x) = dp_prev[0] + ... + dp_prev[x]
        auto G = [&](int x) -> long long {
            if (x < 0) return 0;
            int idx = int(upper_bound(starts.begin(), starts.end(), x) - starts.begin()) - 1;
            if (idx < 0) return 0;
            long long part = prevP[idx].w * (min(prevP[idx].u, x) - prevP[idx].p + 1) % MOD;
            return (pre[idx] + part) % MOD;
        };

        vector<Piece> curP;
        for (const auto& o : info[partIndex]) {
            // a kezdő pozíció t+1, ahol t in [L, p-1]
            long long w = (G(o.p - 1) - G(o.l - 1) + MOD) % MOD;
            if (w != 0) curP.push_back({o.p, o.u, w});
        }
        prevP.swap(curP);
        if (prevP.empty()) break;
    }

    long long ans = 0;
    for (const auto& pc : prevP) {
        if (pc.u == N) ans = (ans + pc.w) % MOD;
    }
    cout << ans << '\n';
    return 0;
}
