/*
Megoldás lényege:
Egy toronyban a konténerek mérete felfelé szigorúan csökken, így egy toronyban nem lehet két azonos méret, és a torony alapjának nagyobbnak kell lennie minden rá kerülő konténernél. Jobbról balra haladva minden konténer először egy már meglévő toronyba próbál beférni; ha ez nem megy, egy korábban kiürült helyre nyit új, alap nélküli tornyot, és csak ha ilyen sincs, a saját helyén alapít tornyot. A döntéshez elég számolni, hány toronyban szerepel már egy adott méret, és hány szabad hely áll rendelkezésre, a tornyok pontos tartalmát nem kell tárolni. A felszabadult helyek száma N mínusz a tornyok száma; az időigény O(N log N).
*/
/*
Hint 1: || Egy torony csak különböző méretű konténereket fogadhat, és a tetejére mindig kisebb kerül. ||
Hint 2: || Jobbról balra haladva a konténer előbb egy már meglévő toronyba próbál beférni; csak ha ez nem megy, nyit új tornyot. ||
Hint 3: || A tornyok tartalmát nem kell nyilvántartani: elég, hogy melyik méret hány toronyban szerepel, és hány szabad hely maradt. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    cin >> n >> k;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;

    // a méreteket sorszámozzuk, hogy a számlálók egyszerű tömbben férjenek el
    vector<long long> vals(a);
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    vector<int> id(n);
    for (int i = 0; i < n; ++i) id[i] = (int)(lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin());

    vector<long long> caps;          // saját tornyok alja, növekvő sorrendben
    vector<int> jOwn(vals.size(), 0);    // saját toronyba került azonos méretek száma
    vector<int> cntFree(vals.size(), 0); // szabad toronyba került azonos méretek száma
    int freeCnt = 0;                 // már használt (nem üres) szabad tornyok száma
    int emptyCnt = 0;                // felszabaduló, még kihasználatlan helyek száma
    int towers = 0;

    for (int p = n - 1; p >= 0; --p) {
        long long v = a[p];
        int c = id[p];
        int greater = (int)(caps.end() - upper_bound(caps.begin(), caps.end(), v));
        if (greater > jOwn[c]) {
            jOwn[c]++;
            emptyCnt++;
        } else if (freeCnt > cntFree[c]) {
            cntFree[c]++;
            emptyCnt++;
        } else if (emptyCnt > 0) {
            freeCnt++;
            cntFree[c]++;
            towers++;
        } else {
            caps.push_back(v);
            towers++;
        }
    }

    cout << n - towers << '\n';
    return 0;
}
