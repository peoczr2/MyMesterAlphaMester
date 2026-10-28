/*
Megoldás lényege:
Az életkor legfeljebb 150, ezért minden korhoz eltároljuk a testtömegek összegét és darabszámát, majd prefixösszegekkel
egy ember [K-M, K+M] korintervallumának összege és darabszáma O(1)-ben lekérdezhető. Az ember saját magát is beleszámítja
a közeli korúak közé (ezt a példa 8. és 9. embere igazolja). Az átlag és a testtömeg eltérése |T·C - S| / C alakú tört,
ezért a törteket keresztszorzással, egész számokkal hasonlítjuk össze, így nincs lebegőpontos pontatlanság.
A legkisebb eltérést keressük; döntetlen esetén a nagyobb életkorú, majd a nagyobb sorszámú ember nyer.
Az időigény O(N + 150), a memóriaigény O(N).
*/
/*
Hint 1: || Az életkor legfeljebb 150, ezért nem kell embereket páronként összevetni: elég korok szerint összegezni a testtömegeket és számolni a darabszámot. ||
Hint 2: || Korok szerinti prefixösszegekkel egy [K-M, K+M] korintervallum összege és darabszáma két tömbelem különbségeként adódik. Az eltérés |T·C - S| / C, a törteket keresztszorzással hasonlítsd össze. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAXK = 150;
    int n, m;
    cin >> n >> m;

    vector<long long> cnt(MAXK + 1, 0), sum(MAXK + 1, 0);
    vector<int> age(n), weight(n);
    for (int i = 0; i < n; i++) {
        cin >> age[i] >> weight[i];
        cnt[age[i]]++;
        sum[age[i]] += weight[i];
    }

    vector<long long> pc(MAXK + 1, 0), ps(MAXK + 1, 0);
    for (int k = 1; k <= MAXK; k++) {
        pc[k] = pc[k - 1] + cnt[k];
        ps[k] = ps[k - 1] + sum[k];
    }

    int bestIdx = -1;
    long long bestNum = 0, bestDen = 1;
    for (int i = 0; i < n; i++) {
        int lo = max(1, age[i] - m);
        int hi = min(MAXK, age[i] + m);
        long long c = pc[hi] - pc[lo - 1];
        long long s = ps[hi] - ps[lo - 1];
        long long num = llabs((long long)weight[i] * c - s);
        // num / c < bestNum / bestDen  <=>  num * bestDen < bestNum * c
        bool take = false;
        if (bestIdx < 0) {
            take = true;
        } else {
            long long lhs = num * bestDen;
            long long rhs = bestNum * c;
            if (lhs < rhs) {
                take = true;
            } else if (lhs == rhs && age[i] >= age[bestIdx]) {
                // döntetlen: a nagyobb életkor nyer, azonos életkornál a későbbi (nagyobb sorszám)
                take = true;
            }
        }
        if (take) {
            bestIdx = i;
            bestNum = num;
            bestDen = c;
        }
    }

    cout << bestIdx + 1 << '\n';
    return 0;
}
