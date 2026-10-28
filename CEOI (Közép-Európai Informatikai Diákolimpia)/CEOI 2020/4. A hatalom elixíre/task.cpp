/*
Megoldás lényege:
Minden sámán barátai bármely V napon visszaállíthatók, ha sámánonként eltároljuk a rá vonatkozó változásokat napjuk szerint.
Minden K-adik változás után pillanatképet készítünk a sámán aktuális barátairól, magasság szerint rendezve, így egy kérdésnél
a V-nél korábbi változások közül csak legfeljebb K-1 darabot kell visszajátszani a legközelebbi pillanatképről.
A visszajátszás után X és Y barátainak rendezett listája O(D + K) időben kész, ezért a válasz két rendezett lista
kétmutatós bejárásával, lineáris időben adódik. Egy kérdés ideje O(D + K log K), a teljes előfeldolgozás O(U·D).
*/
/*
Hint 1: || Egy változás csak két sámán barátlistáját módosítja, ezért elég sámánonként a rájuk vonatkozó változásokat napjuk szerint sorban tárolni. ||
Hint 2: || A kérdésnél bináris kereséssel keresd meg, hány változás történt V előtt, és minden K-adik változás után mentsd el a barátok listáját magasság szerint rendezve. ||
Hint 3: || A legközelebbi pillanatképből indulva csak a hátralévő néhány változást játszd vissza, majd a két rendezett listát kétmutatós bejárással hasonlítsd össze. ||
*/
#include <bits/stdc++.h>
using namespace std;

namespace {

const int K = 32;

int gN = 0;
int gD = 0;
vector<int> gH;
// ev[p]: p-re vonatkozó változások (nap, társ) párjai, növekvő nap szerint
vector<vector<pair<int, int>>> ev;
// snap[p][s-1]: p barátai a p s*K-adik változása után, magasság szerint rendezve
vector<vector<vector<int>>> snap;
vector<char> inBase, curMark, seen;

bool byH(int a, int b) { return gH[a] < gH[b]; }

vector<int> friendsAt(int p, int V) {
    const vector<pair<int, int>> &e = ev[p];
    int k = (int)(lower_bound(e.begin(), e.end(), make_pair(V, -1)) - e.begin());
    int s = k / K;
    vector<int> base;
    if (s > 0) base = snap[p][s - 1];
    for (int q : base) {
        inBase[q] = 1;
        curMark[q] = 1;
    }
    vector<int> touched;
    for (int i = s * K; i < k; i++) {
        int q = e[i].second;
        curMark[q] ^= 1;
        touched.push_back(q);
    }
    vector<int> res;
    for (int q : base)
        if (curMark[q]) res.push_back(q);
    vector<int> added;
    for (int q : touched) {
        if (curMark[q] && !inBase[q] && !seen[q]) {
            seen[q] = 1;
            added.push_back(q);
        }
    }
    sort(added.begin(), added.end(), byH);
    vector<int> out;
    out.reserve(res.size() + added.size());
    merge(res.begin(), res.end(), added.begin(), added.end(), back_inserter(out), byH);
    for (int q : base) {
        inBase[q] = 0;
        curMark[q] = 0;
        seen[q] = 0;
    }
    for (int q : touched) {
        inBase[q] = 0;
        curMark[q] = 0;
        seen[q] = 0;
    }
    return out;
}

}  // namespace

void init(int N, int D, int H[]) {
    gN = N;
    gD = D;
    gH.assign(H, H + N);
}

void curseChanges(int U, int A[], int B[]) {
    ev.assign(gN, {});
    for (int i = 0; i < U; i++) {
        ev[A[i]].push_back({i, B[i]});
        ev[B[i]].push_back({i, A[i]});
    }
    snap.assign(gN, {});
    inBase.assign(gN, 0);
    curMark.assign(gN, 0);
    seen.assign(gN, 0);

    vector<vector<int>> fr(gN);
    vector<int> cnt(gN, 0);
    auto removeFrom = [](vector<int> &v, int x) {
        for (size_t i = 0; i < v.size(); i++) {
            if (v[i] == x) {
                v[i] = v.back();
                v.pop_back();
                return;
            }
        }
    };
    for (int i = 0; i < U; i++) {
        int a = A[i], b = B[i];
        bool present = find(fr[a].begin(), fr[a].end(), b) != fr[a].end();
        if (present) {
            removeFrom(fr[a], b);
            removeFrom(fr[b], a);
        } else {
            fr[a].push_back(b);
            fr[b].push_back(a);
        }
        int ends[2] = {a, b};
        for (int p : ends) {
            cnt[p]++;
            if (cnt[p] % K == 0) {
                vector<int> sn = fr[p];
                sort(sn.begin(), sn.end(), byH);
                snap[p].push_back(move(sn));
            }
        }
    }
}

int question(int X, int Y, int V) {
    const int INF = 1000000000;
    vector<int> f1 = friendsAt(X, V);
    vector<int> f2 = friendsAt(Y, V);
    if (f1.empty() || f2.empty()) return INF;
    long long best = INF;
    size_t i = 0, j = 0;
    while (i < f1.size() && j < f2.size()) {
        long long hx = gH[f1[i]], hy = gH[f2[j]];
        best = min(best, llabs(hx - hy));
        if (hx < hy)
            i++;
        else
            j++;
    }
    return (int)best;
}
