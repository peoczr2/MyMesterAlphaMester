/*
Megoldás lényege:
A napi létszámok K pozitív egész szám, összegük N; ilyen beosztásból C(N−1, K−1) darab van, mert N−1 osztópont közül K−1-et kell kiválasztani.
A beosztásokat lexikografikusan csökkenő sorrendben számozzuk: egy beosztás rangja 1 plusz azoknak a beosztásoknak a száma, amelyek előzik meg; minden pozícióban az adott értéknél nagyobb első elemmel kezdődő beosztásokat összeadjuk, a darabszámot binomiális érték adja.
Az előző és a következő beosztást a rang −1, illetve +1 értékéből állítjuk elő (unrankeléssel), az elejétől választva az egyes számokat; a határokon ciklikusan az utolsó, illetve az első beosztás következik.
Az időigény O(K·N), N ≤ 50 és K ≤ 10 mellett ez nyilvánvalóan gyors.
*/
/*
Hint 1: || A K pozitív szám összege N: ezek száma úgy adódik, hogy N−1 osztópont közül K−1-et választasz ki, ez egy binomiális együttható. ||
Hint 2: || A rangot pozíciónként számold: az aktuális helyen minden, az aktuális értéknél nagyobb számmal kezdődő, a maradékból képezhető beosztás előbb jön; ezek száma egy binomiális érték, amelyet binomiális táblázatból kapsz. ||
Hint 3: || Az unranking az elejétől dolgozik: az első pozícióban végigmész a lehetséges értékeken, és a blokkméretekből megállapítod, melyik érték tartalmazza a kért rangot; a maradékra ugyanígy rekurzívan folytatod. ||
*/
#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
static ull C[55][55];

ull countComp(int sum, int parts) {
    if (parts == 1) return 1;
    return C[sum - 1][parts - 1];
}

vector<int> unrankComp(int sum, int parts, ull rank) {
    if (parts == 1) return {sum};
    for (int first = sum - parts + 1; first >= 1; --first) {
        ull cnt = countComp(sum - first, parts - 1);
        if (rank > cnt) rank -= cnt;
        else {
            vector<int> tail = unrankComp(sum - first, parts - 1, rank);
            tail.insert(tail.begin(), first);
            return tail;
        }
    }
    return {};
}

ull rankComp(const vector<int>& a, int sum, int parts) {
    ull rank = 1;
    const int K = parts;
    for (int i = 0; i < K; ++i) {
        for (int first = sum - parts + 1; first > a[i]; --first) {
            rank += countComp(sum - first, parts - 1);
        }
        sum -= a[i];
        --parts;
    }
    return rank;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int n = 0; n <= 50; ++n) {
        C[n][0] = C[n][n] = 1;
        for (int k = 1; k < n; ++k) C[n][k] = C[n - 1][k - 1] + C[n - 1][k];
    }

    int N, K;
    cin >> N >> K;
    vector<int> a(K);
    for (int i = 0; i < K; ++i) cin >> a[i];

    ull total = countComp(N, K);
    ull r = rankComp(a, N, K);
    vector<int> prev = unrankComp(N, K, r == 1 ? total : r - 1);
    vector<int> next = unrankComp(N, K, r == total ? 1 : r + 1);

    cout << total << '\n';
    for (int i = 0; i < K; ++i) {
        if (i) cout << ' ';
        cout << prev[i];
    }
    cout << '\n';
    for (int i = 0; i < K; ++i) {
        if (i) cout << ' ';
        cout << next[i];
    }
    cout << '\n';
    return 0;
}