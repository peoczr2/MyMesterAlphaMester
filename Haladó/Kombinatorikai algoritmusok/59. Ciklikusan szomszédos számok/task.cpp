/*
Megoldás lényege:
Az érdekes számok sorrendje: előbb a rövidebbek, azonos hosszon lexikografikus.
Ugyanilyen hosszon a következő számot úgy kapjuk, hogy a jobbról első olyan jegyet növeljük, ahol ez
lehetséges, majd a jobb oldalt a maradék összeggel a lehető legkisebbre töltjük; az előzőt a csökkentéssel
és a jobb oldal legnagyobbra töltésével. Ha ilyen nincs, a szomszéd más hosszúságú: a következő az L+1 jegyű
legkisebb szám (L=N esetén az egyjegyű M), az előző az L-1 jegyű legnagyobb szám (L=1 esetén az N jegyű
legnagyobb). Így a legkisebb és a legnagyobb érdekes szám körbe záródik. Egy pozíció ellenőrzése O(1),
a kitöltés O(L), így az időigény O(L), ami 100 000 jegyre is belefér a 0,1 mp-be.
*/
/*
Hint 1: || Az érdekes számok lexikografikus sorrendben vannak, és minden ilyen számban a jegyek összege M. Keresd meg a jobbról első pozíciót, ahol a jegy változtatható úgy, hogy a jobb oldali jegyek összege még kiadható legyen. ||
Hint 2: || Az adott pozícióra a következőnél a nála nagyobb legkisebb lehetséges jegy kell, az előzőnél a nála kisebb legnagyobb. A jobb oldalt a maradék összeggel töltsd ki: következőnél elöl a legkisebb, előzőnél elöl a legnagyobb jegyekkel. ||
Hint 3: || Ha egyik pozíción sincs megoldás, a szomszéd hossza változik. Gondold végig, mi a legkisebb érdekes szám (ez egyjegyű), és mi a legnagyobb N jegyű érdekes szám. ||
*/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// len jegyű sorozat, jegyösszeg sum, minden jegy legfeljebb M.
// A legkisebb ilyen sorozat: elöl a lehető legkisebb jegyek állnak.
// firstPositive esetén az első jegy legalább 1.
static vector<ll> smallestFixedLen(int len, ll sum, ll M, bool firstPositive) {
    vector<ll> a;
    ll rem = sum;
    for (int i = 0; i < len; ++i) {
        ll left = len - 1 - i;
        ll low = max(0LL, rem - left * M);
        if (i == 0 && firstPositive) low = max(low, 1LL);
        a.push_back(low);
        rem -= low;
    }
    return a;
}

// len jegyű sorozat, jegyösszeg sum, minden jegy legfeljebb M.
// A legnagyobb ilyen sorozat: elöl a lehető legnagyobb jegyek állnak.
static vector<ll> largestFixedLen(int len, ll sum, ll M) {
    vector<ll> a;
    ll rem = sum;
    for (int i = 0; i < len; ++i) {
        ll d = min(M, rem);
        a.push_back(d);
        rem -= d;
    }
    return a;
}

// pre[i] = cur[0] + ... + cur[i-1]
static vector<ll> prefixSums(const vector<ll>& cur) {
    vector<ll> pre(cur.size() + 1, 0);
    for (size_t i = 0; i < cur.size(); ++i) pre[i + 1] = pre[i] + cur[i];
    return pre;
}

// Ugyanilyen hosszú, nagyobb érdekes szám: a jobbról első növelhető jegy.
static bool nextSameLen(const vector<ll>& cur, ll M, vector<ll>& out) {
    int L = cur.size();
    vector<ll> pre = prefixSums(cur);
    for (int i = L - 1; i >= 0; --i) {
        ll pref = pre[i];                    // a 0..i-1 jegyek összege
        ll remPos = L - 1 - i;               // a jobb oldalon álló jegyek száma
        ll lo = max(cur[i] + 1, M - pref - remPos * M);  // az i. jegy új értékének alsó határa
        ll hi = M - pref;                    // felső határ az összeg miatt
        if (lo > hi) continue;
        out.assign(cur.begin(), cur.begin() + i);
        out.push_back(lo);
        vector<ll> tail = smallestFixedLen((int)remPos, M - pref - lo, M, false);
        out.insert(out.end(), tail.begin(), tail.end());
        return true;
    }
    return false;
}

// Ugyanilyen hosszú, kisebb érdekes szám: a jobbról első csökkenthető jegy.
static bool prevSameLen(const vector<ll>& cur, ll M, vector<ll>& out) {
    int L = cur.size();
    vector<ll> pre = prefixSums(cur);
    for (int i = L - 1; i >= 0; --i) {
        ll pref = pre[i];
        ll remPos = L - 1 - i;
        ll lo = max(i == 0 ? 1LL : 0LL, M - pref - remPos * M);  // i=0: nincs vezető nulla
        ll hi = min(cur[i] - 1, M - pref);
        if (lo > hi) continue;
        out.assign(cur.begin(), cur.begin() + i);
        out.push_back(hi);
        vector<ll> tail = largestFixedLen((int)remPos, M - pref - hi, M);
        out.insert(out.end(), tail.begin(), tail.end());
        return true;
    }
    return false;
}

static void printSeq(const vector<ll>& a) {
    for (size_t i = 0; i < a.size(); ++i) {
        if (i) cout << ' ';
        cout << a[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N, M;
    cin >> N >> M;
    // A második sor jegyei szóközzel elválasztott egész számok (akár M-ig).
    vector<ll> cur;
    ll x;
    while (cin >> x) cur.push_back(x);
    int L = cur.size();

    vector<ll> prv, nxt;
    if (!prevSameLen(cur, M, prv)) {
        // Nincs kisebb, ugyanilyen hosszú szám: az L-1 jegyű legnagyobb előzi meg,
        // L=1 esetén pedig a legnagyobb N jegyű szám.
        prv = (L == 1) ? largestFixedLen((int)N, M, M) : largestFixedLen(L - 1, M, M);
    }
    if (!nextSameLen(cur, M, nxt)) {
        // Nincs nagyobb, ugyanilyen hosszú szám: az L+1 jegyű legkisebb következik,
        // L=N esetén pedig a legkisebb érdekes szám, az M.
        nxt = (L < N) ? smallestFixedLen(L + 1, M, M, true) : vector<ll>{M};
    }
    printSeq(prv);
    printSeq(nxt);
    return 0;
}
