/*
Megoldás lényege: visszalépéses keresés, mindig a még ki nem elégített legkisebb sorszámú
fajtából indulunk. Minden lépésben egy olyan Q elemű csoportot választunk, amely tartalmazza
ezt a fajtát, minden tagja még kapható, és a csoport minden párja még összehasonlítandó.
A csoportok sorrendje nem számít, ezért a kész megoldás csoportjait bitmaszkként növekvő
sorrendbe rendezzük. Az egyes fajták és párok hátralévő számlálóiból számolt korlátok (például
egy pár hátralévő száma nem lehet nagyobb, mint egy tagjának hátralévő darabszáma) gyorsan
levágják a lehetetlen ágakat, így N ≤ 10 és M ≤ 12 esetén is belefér az időkorlátba.
*/
/*
Hint 1: || Két egyszerű összefüggés: N·P = M·Q és (N-1)·K = P·(Q-1); ha ezek nem teljesülnek, nincs megoldás. ||
Hint 2: || Mindig a legkisebb sorszámú olyan fajtából indulj, amelyiknek még van hátralévő kiosztása, és a következő csoportot úgy válaszd, hogy tartalmazza ezt a fajtát. ||
Hint 3: || Tartsd nyilván a fajták és párok hátralévő számlálóit, visszalépéskor állítsd vissza őket, és vágd le az ágat, ha valamelyik számláló túl nagy vagy negatív lenne. ||
*/

#include <bits/stdc++.h>
using namespace std;

int N, M, P, Q, K;
vector<int> tp;
vector<vector<int>> pc;
vector<int> chosen;

bool feasibleCounts(int rem) {
    for (int x = 0; x < N; ++x) {
        if (tp[x] < 0 || tp[x] > rem) return false;
        for (int y = x + 1; y < N; ++y) {
            int c = pc[x][y];
            if (c < 0 || c > min(tp[x], tp[y])) return false;
            if (tp[x] - c > rem - tp[y]) return false;
            if (tp[y] - c > rem - tp[x]) return false;
        }
    }
    return true;
}

bool place(int rem);

bool extend(int rem, const vector<int>& cand, size_t start, vector<int>& group) {
    if ((int)group.size() == Q) {
        int mask = 0;
        for (int x : group) {
            mask |= 1 << x;
            --tp[x];
        }
        for (size_t i = 0; i < group.size(); ++i)
            for (size_t j = i + 1; j < group.size(); ++j)
                --pc[group[i]][group[j]], --pc[group[j]][group[i]];
        bool ok = false;
        if (feasibleCounts(rem - 1)) {
            chosen.push_back(mask);
            ok = place(rem - 1);
            if (!ok) chosen.pop_back();
        }
        if (!ok) {
            for (size_t i = 0; i < group.size(); ++i)
                for (size_t j = i + 1; j < group.size(); ++j)
                    ++pc[group[i]][group[j]], ++pc[group[j]][group[i]];
            for (int x : group) ++tp[x];
        }
        return ok;
    }
    for (size_t i = start; i < cand.size(); ++i) {
        int y = cand[i];
        bool good = true;
        for (size_t j = 1; j < group.size() && good; ++j)
            if (pc[y][group[j]] < 1) good = false;
        if (!good) continue;
        group.push_back(y);
        if (extend(rem, cand, i + 1, group)) return true;
        group.pop_back();
    }
    return false;
}

bool place(int rem) {
    if (rem == 0) return true;
    int x0 = -1;
    for (int x = 0; x < N; ++x) if (tp[x] > 0) { x0 = x; break; }
    if (x0 < 0) return false;
    vector<int> cand;
    for (int y = 0; y < N; ++y)
        if (y != x0 && tp[y] > 0 && pc[x0][y] > 0) cand.push_back(y);
    vector<int> group(1, x0);
    return extend(rem, cand, 0, group);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> P >> Q >> K;
    if (N * P != M * Q || (N - 1) * K != P * (Q - 1)) {
        cout << -1 << '\n';
        return 0;
    }
    tp.assign(N, P);
    pc.assign(N, vector<int>(N, K));
    if (!place(M)) {
        cout << -1 << '\n';
        return 0;
    }
    sort(chosen.begin(), chosen.end());
    for (int mask : chosen) {
        bool first = true;
        for (int i = 0; i < N; ++i) if (mask & (1 << i)) {
            if (!first) cout << ' ';
            cout << i + 1;
            first = false;
        }
        cout << '\n';
    }
    return 0;
}
