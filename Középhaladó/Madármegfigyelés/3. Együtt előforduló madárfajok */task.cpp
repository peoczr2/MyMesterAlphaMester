/*
Megoldás lényege:
Egy j-edik faj társfajai azok a k fajok, amelyek minden olyan helységben jelen voltak, ahol a j-edik faj előfordult. Ezt minden (j, k) párra külön ellenőrizzük: ha van olyan helység, ahol j volt, de k nem, akkor k nem társfaj. Ha a j-edik faj sehol nem fordult elő, nincs társfaja, ezért 0-t írunk. A futásidő O(N²·M), ami M ≤ 50 és N ≤ 200 mellett bőven belefér az időkorlátba, a memóriaigény O(M·N).
*/
/*
Hint 1: || Egy j faj társfajait úgy kapod meg, hogy csak azokat a helységeket nézed, ahol j előfordult. Ezekben kell minden társnak jelen lennie. ||
Hint 2: || Tartsd nyilván a helységenkénti darabszámokat egy M×N-es táblázatban. Egy (j, k) pár akkor társ, ha a j-t tartalmazó sorok mindegyikében k darabszáma is pozitív; ezt a sorok végigjárásával ellenőrizd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;
    vector<vector<int>> E(M, vector<int>(N));
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            cin >> E[i][j];

    for (int j = 0; j < N; ++j) {
        bool elofordult = false;
        for (int i = 0; i < M; ++i)
            if (E[i][j] > 0) elofordult = true;

        vector<int> tars;
        if (elofordult) {
            for (int k = 0; k < N; ++k) {
                if (k == j) continue;
                bool minden = true;
                for (int i = 0; i < M && minden; ++i)
                    if (E[i][j] > 0 && E[i][k] == 0) minden = false;
                if (minden) tars.push_back(k + 1);
            }
        }

        cout << tars.size();
        for (int k : tars) cout << ' ' << k;
        cout << '\n';
    }
    return 0;
}
