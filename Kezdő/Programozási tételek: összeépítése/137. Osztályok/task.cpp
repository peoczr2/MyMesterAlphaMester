/*
Megoldás lényege:
Két képpont akkor kerül egy osztályba, ha az értékük legfeljebb 1-gyel tér el, így az osztályok a képen előforduló
egymást követő értéktartományok (futamok). Ezek száma a futamok számával egyezik. Egy küszöb t esetén minden olyan értéket
kidobunk, amelyből legfeljebb t darab van a képen: ez bontja szét az osztályokat. A t-t növelve, az értékeket darabszám
szerint sorban dobjuk ki, és minden darabszám-csoport után megnézzük, elér-e K osztályt. A futamszámot inkrementálisan tartjuk:
egy érték törlése a szomszédos értékek állapotától függően egyszerre -1, 0 vagy +1 hatású. Az első olyan t a válasz,
ahol az osztályszám legalább K; ha már a kezdeti állapot is megfelel, a válasz 0, ha soha, akkor -1.
Az időigény O(N·M + maxérték).
*/
/*
Hint 1: || Két egymás utáni egész érték mindig egy osztályba kerül, így az osztályok a képen előforduló, folytonos értéktartományok. Számold meg, hány ilyen tartomány van. ||
Hint 2: || Ha egy értéket kidobunk, a tartomány szétesik. Vedd sorra a értékeket a darabszámuk szerint növekvően, és minden csoport után ellenőrizd a tartományok számát; az első megfelelő darabszám a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAXV = 100000;
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> cnt(MAXV + 2, 0);
    int total = n * m;
    for (int i = 0; i < total; i++) {
        int f;
        cin >> f;
        cnt[f]++;
    }

    vector<char> act(MAXV + 2, 0);
    for (int v = 1; v <= MAXV; v++) act[v] = cnt[v] > 0;

    // futamok száma: olyan aktív v, amelynek a v-1 értéke nem aktív
    long long runs = 0;
    for (int v = 1; v <= MAXV; v++)
        if (act[v] && !act[v - 1]) runs++;

    if (runs >= k) {
        cout << 0 << '\n';
        return 0;
    }

    vector<int> vals;
    for (int v = 1; v <= MAXV; v++)
        if (cnt[v] > 0) vals.push_back(v);
    sort(vals.begin(), vals.end(), [&](int a, int b) { return cnt[a] < cnt[b]; });

    size_t p = 0;
    while (p < vals.size()) {
        int t = cnt[vals[p]];
        while (p < vals.size() && cnt[vals[p]] == t) {
            int v = vals[p++];
            // v törlése (v aktív volt): a v saját tagja megszűnik, a v+1 új futamkezdő lehet
            runs += (act[v + 1] ? 1 : 0) - (!act[v - 1] ? 1 : 0);
            act[v] = 0;
        }
        if (runs >= k) {
            cout << t << '\n';
            return 0;
        }
    }

    cout << -1 << '\n';
    return 0;
}
