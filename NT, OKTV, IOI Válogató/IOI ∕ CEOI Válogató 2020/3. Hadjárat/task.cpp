/*
Megoldás lényege:
A kiválasztott városok sorszáma, R és A is szigorúan nő, tehát a keresett sorozat a 3 dimenziós (sorszám, R, A) szerinti leghosszabb lánc. Legyen dp[i] a legjobb lánc hossza, amely i-nél végződik: dp[i] = 1 + max dp[j], ahol j < i, R_j < R_i és A_j < A_i. A sorszám szerinti felezéses (CDQ) rekurzióval kezeljük: a bal félben a dp értékek már véglegesek, mielőtt a jobb félre hatnának. A két fél közötti hatást R szerinti sorrendben söpréssel, az A-ra épülő Fenwick-fával (prefix maximum) számoljuk, a maximumhoz az előző várost is eltároljuk. A lánc visszakövetésével kapjuk a városokat. Az időigény O(N log² N).
*/
/*
Hint 1: || Három szempont van: a sorszám, R és A is szigorúan nőjön a kiválasztott városok között. Ez egy leghosszabb lánc keresése: vezess be dp[i]-t, a legjobb lánc hosszát, amely i-nél végződik. Hogyan számolható dp[i] a korábbi városok dp-jéből? ||
Hint 2: || dp[i] kiszámításához a j < i, R_j < R_i és A_j < A_i feltételű városok dp-jének maximuma kell. Ez kétdimenziós dominancia-lekérdezés: egy Fenwick-fa egy koordinátára még kezelhető, de itt két feltétel is van. ||
Hint 3: || Oszd a sorszám-tartományt két félre (felező rekurzió). A bal félből a jobb félbe menő hatást rendezd R szerint, és közben az A-ra épülő Fenwick-fában tartsd a prefix maximumot. Az értékhez mentsd el az előző város sorszámát is, hogy a végén vissza tudd állítani a láncot. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int IDX_BITS = 20;
const long long IDX_MASK = (1LL << IDX_BITS) - 1;

int n;
vector<long long> R, A;
vector<int> dp, prv, rankA;
int maxRank;
vector<long long> bitTree;  // (dp érték << 20) | sorszám, prefix maximum

void bitUpdate(int pos, long long val) {
    for (; pos <= maxRank; pos += pos & -pos) bitTree[pos] = max(bitTree[pos], val);
}

long long bitQuery(int pos) {
    long long res = 0;
    for (; pos > 0; pos -= pos & -pos) res = max(res, bitTree[pos]);
    return res;
}

void bitClear(int pos) {
    for (; pos <= maxRank; pos += pos & -pos) bitTree[pos] = 0;
}

// a [l, r) sorszámtartományon: a dp értékek végleges kiszámítása;
// byR: a [l, r) sorszámú városok R szerint rendezve (a felek is rendezve maradnak, nincs külön rendezés)
void cdq(int l, int r, const vector<int>& byR) {
    if (r - l <= 1) return;
    int mid = (l + r) / 2;

    vector<int> leftR, rightR;
    leftR.reserve(mid - l);
    rightR.reserve(r - mid);
    for (int i : byR) {
        if (i < mid) leftR.push_back(i);
        else rightR.push_back(i);
    }

    cdq(l, mid, leftR);

    // a bal félből csak azok hatnak, amelyek R-je szigorúan kisebb
    size_t p = 0;
    for (int i : rightR) {
        while (p < leftR.size() && R[leftR[p]] < R[i]) {
            int j = leftR[p];
            bitUpdate(rankA[j], ((long long)dp[j] << IDX_BITS) | j);
            ++p;
        }
        long long best = bitQuery(rankA[i] - 1);  // A_j < A_i
        int bestDp = (int)(best >> IDX_BITS);
        if (bestDp + 1 > dp[i]) {
            dp[i] = bestDp + 1;
            prv[i] = (int)(best & IDX_MASK);
        }
    }
    for (size_t q = 0; q < p; ++q) bitClear(rankA[leftR[q]]);

    cdq(mid, r, rightR);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    R.resize(n);
    A.resize(n);
    for (int i = 0; i < n; ++i) cin >> R[i] >> A[i];

    // az A értékek tömörítése 1..maxRank közé
    vector<long long> vals = A;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    maxRank = (int)vals.size();
    rankA.resize(n);
    for (int i = 0; i < n; ++i)
        rankA[i] = (int)(lower_bound(vals.begin(), vals.end(), A[i]) - vals.begin()) + 1;

    dp.assign(n, 1);
    prv.assign(n, -1);
    bitTree.assign(maxRank + 1, 0);

    vector<int> byR(n);
    iota(byR.begin(), byR.end(), 0);
    sort(byR.begin(), byR.end(), [&](int x, int y) { return R[x] < R[y]; });
    cdq(0, n, byR);

    int bestEnd = 0;
    for (int i = 1; i < n; ++i)
        if (dp[i] > dp[bestEnd]) bestEnd = i;

    vector<int> chain;
    for (int cur = bestEnd; cur != -1; cur = prv[cur]) chain.push_back(cur);
    reverse(chain.begin(), chain.end());

    cout << chain.size() << '\n';
    for (size_t i = 0; i < chain.size(); ++i)
        cout << chain[i] + 1 << (i + 1 < chain.size() ? ' ' : '\n');
    return 0;
}
