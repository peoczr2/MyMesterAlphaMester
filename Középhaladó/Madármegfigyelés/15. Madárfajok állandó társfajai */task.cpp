/*
Megoldás lényege:
Egy j faj állandó társfajai azok a k fajok, amelyek minden olyan helységben jelen vannak, ahol j előfordul. Helységenként végignézzük a fajokat: ha j jelen van, de k nincs, akkor k nem lehet j állandó társfaja. Ezt egy N×N-es logikai táblázatban követjük, amelynek minden eleme kezdetben igaz, és a kizáró eseteknél hamisra állítjuk. Végül j sorában a k ≠ j fajokat írjuk ki, amelyekre az elem igaz maradt, előbb a számukat. Ha egy faj sehol sem fordult elő, nincs állandó társfaja, így a sora 0. Az idő O(M·N²), legfeljebb 2·10^6 művelet.
*/
/*
Hint 1: || Egy j fajhoz csak azok a k fajok tartoznak, amelyek minden olyan helységben jelen vannak, ahol j előfordul. Elég ezeket a helységeket végignézni. ||
Hint 2: || Tarts nyilván egy N×N-es logikai táblázatot, amely kezdetben minden eleme igaz. Ha egy helységben j jelen van, k pedig nincs, akkor a (j, k) elemet állítsd hamisra. Végül j sorában azok a k fajok (k ≠ j) a társfajok, amelyekre az elem igaz maradt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;

    vector<vector<bool>> allando(N + 1, vector<bool>(N + 1, true));
    vector<bool> elofordult(N + 1, false);
    vector<int> sor(N + 1);
    for (int i = 0; i < M; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin >> sor[j];
        }
        for (int j = 1; j <= N; ++j) {
            if (sor[j] == 0) continue;
            elofordult[j] = true;
            for (int k = 1; k <= N; ++k) {
                if (sor[k] == 0) allando[j][k] = false;
            }
        }
    }

    for (int j = 1; j <= N; ++j) {
        vector<int> tarsok;
        if (elofordult[j]) {
            for (int k = 1; k <= N; ++k) {
                if (k != j && allando[j][k]) tarsok.push_back(k);
            }
        }
        cout << tarsok.size();
        for (int k : tarsok) cout << ' ' << k;
        cout << '\n';
    }
    return 0;
}
