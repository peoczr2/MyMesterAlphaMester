/*
Megoldás lényege:
A kívánt elrendezésben minden M egymás utáni hely (blokk) az 1..M címkék egy permutációja. Blokkonként minden címkéből egy példány a helyén marad, a többi (a többlet) konténer a blokkban hiányzó címkék helyére mozog. Egy átrendezés költsége a mozgatott konténerek száma plusz a nem triviális ciklusok száma a pozíciók permutációjában, mert az üres hely a kezdő helyére tér vissza és nem alkot ciklust. A blokkokat csúcsoknak, a mozgó konténereket irányított éleknek (régi blokk -> új blokk) tekintve egy irányított multigráfot kapunk, így a ciklusok száma a komponensek számát adja. A címkék szerinti célpárosítás szabadon választható, és két komponens azonos címkéjű éleinek célját felcserélve a komponensek egyesíthetők; a végén komponensenként egy Euler-kör egyetlen ciklust ad, amelyet az üres hellyel a ciklus hossza + 1 mozgatással lehet feloldani. Az idő O(N·M).
*/
/*
Hint 1: || Egy átrendezés költsége: a helyükön nem maradó konténerek száma, plusz a nem triviális ciklusok száma a pozíciók permutációjában. Az üres hely a kezdő helyére tér vissza, ezért ő nem ad ciklust. ||
Hint 2: || Blokkonként minden címkéből egy példány maradhat a helyén; a többit a blokkban hiányzó címkék helyére kell vinni. A párosítás szabadon választható, és a többlet-konténerek célblokkjainak megválasztásával lehet a komponensek számát csökkenteni. ||
Hint 3: || Építs irányított multigráfot: a blokkok a csúcsok, minden mozgó konténer egy él a régi blokkjából az új blokkjába. Két komponens között, ha van közös címkéjű él, a két él célját megcserélve a komponensek egyesülnek; a végén minden komponens egy Euler-kör, ami egy ciklust ad, és az üres hellyel egy-egy ciklust (hossz + 1) lépésben lehet megoldani. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> par;

int findp(int x) {
    while (par[x] != x) {
        par[x] = par[par[x]];
        x = par[x];
    }
    return x;
}

void unite(int x, int y) {
    x = findp(x);
    y = findp(y);
    if (x != y) par[x] = y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    int NM = N * M;
    int E = NM + 1;  // az üres hely kezdetben és a végén is
    vector<int> a(NM + 1);
    for (int p = 1; p <= NM; p++) cin >> a[p];

    auto blk = [&](int p) { return (p - 1) / M; };

    // ex[x]: a x címke többlet-példányainak helyei; miss[x]: a x címkét nem tartalmazó blokkok
    vector<vector<int>> ex(M + 1), miss(M + 1);
    vector<char> cnt(M + 1);
    for (int b = 0; b < N; b++) {
        fill(cnt.begin(), cnt.end(), 0);
        for (int j = 0; j < M; j++) {
            int p = b * M + j + 1;
            int x = a[p];
            if (!cnt[x]) cnt[x] = 1;
            else ex[x].push_back(p);
        }
        for (int x = 1; x <= M; x++)
            if (!cnt[x]) miss[x].push_back(b);
    }

    // Kezdeti párosítás: minden többlet-példány egy hiányzó blokkba megy.
    vector<int> dest(NM + 1, -1);
    par.resize(N);
    iota(par.begin(), par.end(), 0);
    for (int x = 1; x <= M; x++) {
        for (size_t i = 0; i < ex[x].size(); i++) {
            int p = ex[x][i];
            dest[p] = miss[x][i];
            unite(blk(p), dest[p]);
        }
    }

    // Különböző komponensek egyesítése: ugyanazon címke két élének célját cseréljük.
    for (int x = 1; x <= M; x++) {
        if (ex[x].empty()) continue;
        int r = ex[x][0];
        for (size_t i = 1; i < ex[x].size(); i++) {
            int p = ex[x][i];
            if (findp(blk(p)) != findp(blk(r))) {
                swap(dest[p], dest[r]);
                unite(blk(p), blk(r));
            }
        }
    }

    // Euler-körök: minden körben a mozgó konténerek egy ciklust alkotnak.
    vector<vector<int>> outE(N);
    for (int p = 1; p <= NM; p++)
        if (dest[p] >= 0) outE[blk(p)].push_back(p);

    vector<size_t> ptr(N, 0);
    vector<vector<int>> cycles;
    for (int s = 0; s < N; s++) {
        while (ptr[s] < outE[s].size()) {
            vector<pair<int, int>> st;  // (csúcs, az ide vezető él; -1 a kezdő csúcsnál)
            vector<int> circ;
            st.push_back({s, -1});
            while (!st.empty()) {
                int v = st.back().first;
                if (ptr[v] < outE[v].size()) {
                    int e = outE[v][ptr[v]++];
                    st.push_back({dest[e], e});
                } else {
                    if (st.back().second != -1) circ.push_back(st.back().second);
                    st.pop_back();
                }
            }
            reverse(circ.begin(), circ.end());
            cycles.push_back(circ);
        }
    }

    // P_i konténere a P_{i+1} helyre megy (indexek modulo L).
    // Mozgatás: P0 -> E, P_{L-1} -> P0, majd P_{i-1} -> P_i (i = L-1 ... 2), végül E -> P1.
    long long S = 0;
    for (auto &c : cycles) S += (long long)c.size() + 1;

    cout << S << '\n';
    for (auto &P : cycles) {
        int L = (int)P.size();
        cout << P[0] << ' ' << E << '\n';
        cout << P[L - 1] << ' ' << P[0] << '\n';
        for (int i = L - 1; i >= 2; i--) cout << P[i - 1] << ' ' << P[i] << '\n';
        cout << E << ' ' << P[1] << '\n';
    }
    return 0;
}
