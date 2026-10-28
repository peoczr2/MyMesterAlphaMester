/*
Megoldás lényege:
Legyen L az 1. és az N. csomóponton átmenő egyenes. A feltétel szerint az útvonal L-et csak az 1–N szakasz belsejében
keresztezi, ezért az L egyik oldalán lévő csomópontokat az 1.-kel és az N.-nel együtt véve, az útvonal ezen oldali darabjai
mind a pontok konvex burkán belül maradnak. A burok határa (az 1–N szakasz nélkül) N-től 1-ig vezető lánc; szomszédos
pontjainak szakaszait az útvonal nem metszheti, és ugyanez igaz a másik oldalra is (ha az egyik oldalon nincs csomópont,
akkor az N–1 szakasz maga a lánc). A hozzáadott élek visszafelé mutatnak (nagyobb sorszámtól a kisebb felé), mert előre
az útvonal már összeköt. Az u->v (u>v) él a v..u csomópontokat kör mentén köti össze; a gráf akkor erősen összefüggő,
ha az (i,i+1) „vágások” mindegyikét lefedi valamelyik hozzáadott él. Mindkét lánc N-től 1-ig ér, ezért együtt minden vágást
lefednek (egy vágást egy lánc csak az útvonal (i,i+1) élével fedhetne, az pedig nem lehet mindkét láncban).
A jelöltekből mohó intervallumlefedéssel választjuk ki a legkevesebb élt. Idő: O(N log N). Több megoldás is lehet.
*/
/*
Hint 1: || Húzd meg az 1. és az N. csomóponton át az egyenest. Az útvonal csak az 1–N szakasz belsejében keresztezheti, ezért az egyik oldalon lévő csomópontok az 1.-kel és az N.-nel együtt olyan konvex burkot adnak, amelyen belül marad az útvonal ezen oldali része. ||
Hint 2: || Az így kapott két konvex burok határa (az 1–N szakasz nélkül) olyan szakaszokból áll, amelyeket az útvonal nem metsz. Jelöltnek a burok szomszédos csúcsainak szakaszai jók, kivéve ha az útvonalon már egymás mellett vannak; az új élt mindig a nagyobb sorszámú csomópontból a kisebb felé irányítsd. Ha az egyik oldalon nincs csomópont, az N–1 szakasz is jelölt. ||
Hint 3: || Az irányított gráf pontosan akkor erősen összefüggő, ha minden i és i+1 közötti vágást átível egy visszafelé mutató él (u->v, v<=i<u). A jelöltek közül mohón válassz: mindig azt az élt, amelynek v végpontja már elért, és u-ja a legnagyobb. ||
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

static char buf[1 << 16];
static int bufLen = 0, bufPos = 0;

static inline int readChar() {
    if (bufPos == bufLen) {
        bufLen = (int)fread(buf, 1, sizeof(buf), stdin);
        bufPos = 0;
        if (bufLen <= 0) return -1;
    }
    return buf[bufPos++];
}

static bool readInt(ll& v) {
    int c = readChar();
    while (c != -1 && c != '-' && (c < '0' || c > '9')) c = readChar();
    if (c == -1) return false;
    int sign = 1;
    if (c == '-') { sign = -1; c = readChar(); }
    ll r = 0;
    while (c >= '0' && c <= '9') { r = r * 10 + (c - '0'); c = readChar(); }
    v = r * sign;
    return true;
}

int n;
vector<ll> X, Y;

// az o csúcsból nézve az a->b fordulás előjele (>0: balra)
static ll orient(int o, int a, int b) {
    return (X[a] - X[o]) * (Y[b] - Y[o]) - (Y[a] - Y[o]) * (X[b] - X[o]);
}

// Az egyik oldal csomópontjainak (és az 1., N. csomópontnak) konvex burka;
// a burok szomszédos csúcspárjai közül a jelölt élek (kisebb, nagyobb) a cand-ba kerülnek.
static void sideChain(const vector<int>& side, vector<pair<int, int>>& cand) {
    if (side.empty()) {            // ezen az oldalon nincs csomópont: az N-1 szakasz szabad
        cand.push_back({1, n});
        return;
    }
    ll dx = X[n] - X[1], dy = Y[n] - Y[1];
    vector<int> ids = side;
    ids.push_back(1);
    ids.push_back(n);
    // az 1.-N. egyenes irányú koordináta szerint rendezünk, így az 1-N szakasz a burok alsó éle
    vector<pair<pair<ll, ll>, int>> key;
    for (int id : ids) {
        ll vx = X[id] - X[1], vy = Y[id] - Y[1];
        key.push_back({{dx * vx + dy * vy, dx * vy - dy * vx}, id});
    }
    sort(key.begin(), key.end());
    int m = (int)key.size();
    vector<int> lo, up;            // alsó és felső burok, a kollineáris pontokat megtartjuk
    for (int i = 0; i < m; ++i) {
        int p = key[i].second;
        while (lo.size() >= 2 && orient(lo[lo.size() - 2], lo.back(), p) < 0) lo.pop_back();
        lo.push_back(p);
    }
    for (int i = m - 1; i >= 0; --i) {
        int p = key[i].second;
        while (up.size() >= 2 && orient(up[up.size() - 2], up.back(), p) < 0) up.pop_back();
        up.push_back(p);
    }
    lo.pop_back();
    up.pop_back();
    lo.insert(lo.end(), up.begin(), up.end());
    int k = (int)lo.size();
    for (int i = 0; i < k; ++i) {
        int u = lo[i], v = lo[(i + 1) % k];
        if ((u == 1 && v == n) || (u == n && v == 1)) continue;   // az 1-N szakaszt az útvonal metszi
        if (abs(u - v) == 1) continue;                            // ez az él már létezik
        cand.push_back({min(u, v), max(u, v)});
    }
}

int main() {
    ll nn;
    readInt(nn);
    n = (int)nn;
    X.assign(n + 1, 0);
    Y.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        readInt(X[i]);
        readInt(Y[i]);
    }
    ll dx = X[n] - X[1], dy = Y[n] - Y[1];
    vector<int> up, down;
    for (int i = 2; i < n; ++i) {
        ll s = dx * (Y[i] - Y[1]) - dy * (X[i] - X[1]);
        if (s > 0) up.push_back(i);
        else down.push_back(i);
    }
    vector<pair<int, int>> cand;
    sideChain(up, cand);
    sideChain(down, cand);
    sort(cand.begin(), cand.end());
    cand.erase(unique(cand.begin(), cand.end()), cand.end());

    // mohó lefedés: reach = az 1. csomópontból oda-vissza elérhető csomópontok vége
    vector<pair<int, int>> res;
    int reach = 1;
    size_t idx = 0;
    while (reach < n) {
        int best = reach, bi = -1;
        while (idx < cand.size() && cand[idx].first <= reach) {
            if (cand[idx].second > best) {
                best = cand[idx].second;
                bi = (int)idx;
            }
            ++idx;
        }
        if (bi < 0) break;         // elvileg nem fordulhat elő
        res.push_back({cand[bi].second, cand[bi].first});
        reach = best;
    }
    string out = to_string(res.size()) + "\n";
    for (auto& e : res) out += to_string(e.first) + " " + to_string(e.second) + "\n";
    fputs(out.c_str(), stdout);
    return 0;
}
