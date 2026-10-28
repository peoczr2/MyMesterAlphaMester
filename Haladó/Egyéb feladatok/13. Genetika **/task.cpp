/*
Megoldás lényege:
Minden darabolás a teljes molekulát lefedi, ezért minden bázis pontosan K darabban szerepel (mindegyik darabolásból
egy), így a molekula hossza az összes darab hosszösszegének K-ad része. Balról jobbra haladva mindig K „aktív”
darab tart: egy esemény akkor van, amikor a legkorábban végződő darab véget ér, és ugyanannyi új darabnak kell
ott kezdődnie, ahány darab végződött. Mivel minden darab csak egy helyen szerepel, a t pozícióban kezdődő darabok
mind előtag-viszonyban állnak egymással, és a leghosszabbjuk (M) minden más ott kezdődő darabnak az előtagja.
Ezért M-et választjuk ki, a hozzá illő rövidebb darabok ugyanott kezdődnek. Az M-hez illeszkedés karakterekkel
ellenőrizhető, és ha egy választás zsákutcába vezet, visszalépünk (visszalépéses keresés).
*/
/*
Hint 1: || Minden darabolás a teljes molekulát lefedi, így minden bázis pontosan K darabban szerepel. Ebből az összes darab hosszösszegének és K-nak a hányadosa adja a molekula hosszát. ||
Hint 2: || Balról jobbra haladj: a 0. pozícióban pontosan K darab kezdődik. Mindig a legkorábban végződő darab végén kell új darabnak kezdődnie, és ugyanannyinak, ahány darab ott véget ér. ||
Hint 3: || Mivel minden darab csak egy helyen szerepel, az ugyanott kezdődő darabok egymás előtagjai. Válaszd a leghosszabbat, és ellenőrizd, hogy a többi, rá illeszkedő darab száma pont a kellő. Ha zsákutca, lépj vissza. ||
*/
#include <bits/stdc++.h>
using namespace std;

static int K, N;
static vector<string> piece;
static vector<char> usedP;
static int usedCnt = 0;
static vector<pair<int, int>> active; // (a darab vége, a darab indexe)
static string S;                      // a molekula ismert része
static int F = 0;                     // az ismert rész hossza
static long long LMAX = LLONG_MAX;    // a molekula hossza (ha kiszámítható)

static bool dfs();

// Két darab előtag-viszonyban van-e (az egyik a másiknak eleje).
static bool prefixRelated(const string &a, const string &b) {
    const string &s = a.size() <= b.size() ? a : b;
    const string &l = a.size() <= b.size() ? b : a;
    return l.compare(0, s.size(), s) == 0;
}

// A p darab a t pozícióra illeszthető-e a már ismert részhez.
static bool consistentAt(int t, const string &p) {
    for (int k = 0; k < (int)p.size(); ++k) {
        int pos = t + k;
        if (pos < F && S[pos] != p[k])
            return false;
    }
    return true;
}

// A p darab karaktereit a t pozícióba írja; az ismert rész a szükséges mértékben bővül.
static void writeAt(int t, const string &p) {
    for (int k = 0; k < (int)p.size(); ++k) {
        int pos = t + k;
        if (pos >= F) {
            S[pos] = p[k];
            F = pos + 1;
        }
    }
}

static void removeActive(int idx) {
    for (size_t q = 0; q < active.size(); ++q)
        if (active[q].second == idx) {
            active.erase(active.begin() + q);
            return;
        }
}

// A t pozícióban j darab kezdődik. Választ egy M darabot (ez lesz a leghosszabb), és a vele
// előtag-viszonyban álló, még nem használt darabok pontosan azok, amelyek ott kezdődnek.
static bool tryEvent(int t, int j) {
    for (int idx = 0; idx < N; ++idx) {
        if (usedP[idx])
            continue;
        const string &M = piece[idx];
        if ((long long)t + (long long)M.size() > LMAX)
            continue;
        if (!consistentAt(t, M))
            continue;

        vector<int> chain;
        chain.push_back(idx);
        bool good = true;
        for (int q = 0; q < N && good; ++q) {
            if (q == idx || !prefixRelated(piece[q], M))
                continue;
            if (usedP[q]) {
                good = false; // már máshol szerepel, ezért ide nem illeszkedhet
                break;
            }
            if (piece[q].size() > M.size()) {
                good = false; // van nála hosszabb, vele előtag-viszonyban álló darab: M nem a leghosszabb
                break;
            }
            chain.push_back(q);
        }
        if (!good || (int)chain.size() != j)
            continue;

        int oldF = F;
        size_t placed = 0;
        bool okPlace = true;
        for (int c : chain) {
            if (!consistentAt(t, piece[c])) {
                okPlace = false;
                break;
            }
            writeAt(t, piece[c]);
            usedP[c] = 1;
            ++usedCnt;
            active.push_back({t + (int)piece[c].size(), c});
            ++placed;
        }
        if (okPlace && dfs())
            return true;

        for (size_t q = 0; q < placed; ++q) {
            int c = chain[q];
            removeActive(c);
            usedP[c] = 0;
            --usedCnt;
        }
        F = oldF;
    }
    return false;
}

// A következő eseményt dolgozza fel: a legkorábban véget érő darabok végén új darabok kezdődnek.
static bool dfs() {
    if (active.empty())
        return usedCnt == N;

    int t = INT_MAX;
    for (const auto &a : active)
        t = min(t, a.first);

    vector<pair<int, int>> removed, keep;
    for (const auto &a : active) {
        if (a.first == t)
            removed.push_back(a);
        else
            keep.push_back(a);
    }
    active = keep;

    bool ok;
    if (active.empty())
        ok = (usedCnt == N); // mindegyik darab ugyanott ért véget: a molekula vége
    else
        ok = tryEvent(t, (int)removed.size());

    if (!ok) {
        for (const auto &a : removed)
            active.push_back(a);
    }
    return ok;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> K >> N;
    piece.resize(N);
    long long total = 0;
    for (int i = 0; i < N; ++i) {
        cin >> piece[i];
        total += (long long)piece[i].size();
    }
    if (total % K == 0)
        LMAX = total / K;

    S.assign(total + 2, '?');
    usedP.assign(N, 0);

    if (tryEvent(0, K)) {
        cout << S.substr(0, F) << '\n';
    } else {
        cout << '\n';
    }
    return 0;
}
