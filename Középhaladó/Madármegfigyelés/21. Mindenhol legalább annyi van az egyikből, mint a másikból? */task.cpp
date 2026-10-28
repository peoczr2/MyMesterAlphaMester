/*
Megoldás lényege:
A j-edik sor k-adik karaktere akkor 1, ha a j-edik fajból minden helységben legalább annyi egyed fordult elő, mint a k-adikból, vagyis a két oszlop minden sorában E[i][j] ≥ E[i][k]. A táblázatot beolvassuk, majd minden j ≠ k párra végigmegyünk az összes helységen. Ha találunk olyan helységet, ahol E[i][j] < E[i][k], a pár értéke 0 lesz. A példa szerint a főátló (j = k) mindig 0, mert a feladat különböző fajok párjait vizsgálja. Az idő O(M·N²), ami legfeljebb 2 000 000 művelet, így az időlimit bőven teljesül.
*/
/*
Hint 1: || Két fajt úgy hasonlíthatsz össze, hogy a két oszlopot sorról sorra nézed. Egyetlen olyan sor is elég a kizáráshoz, ahol a j-edik faj darabszáma kisebb. ||
Hint 2: || Készíts N×N-es karaktertáblát, és a (j, k) cellát a j-edik és a k-adik oszlop sorainak bejárásával töltsd ki. A főátlót (j = k) hagyd ki, ott a kimenetben 0 marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;

    vector<vector<int>> E(M, vector<int>(N + 1));
    for (int i = 0; i < M; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin >> E[i][j];
        }
    }

    for (int j = 1; j <= N; ++j) {
        string sor(N, '0');
        for (int k = 1; k <= N; ++k) {
            if (j == k) continue;
            bool legalabb = true;
            for (int i = 0; i < M && legalabb; ++i) {
                if (E[i][j] < E[i][k]) legalabb = false;
            }
            if (legalabb) sor[k - 1] = '1';
        }
        cout << sor << '\n';
    }
    return 0;
}
