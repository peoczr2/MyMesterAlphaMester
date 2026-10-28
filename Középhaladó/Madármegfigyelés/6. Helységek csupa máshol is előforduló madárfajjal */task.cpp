/*
Megoldás lényege:
Először fajonként megszámoljuk, hány helységben fordult elő a faj. Egy helység akkor találat, ha van benne madár, és az ott látott mindegyik faj legalább két helységben előfordult, így máshol is. A találatok számát, majd sorszámaikat növekvő sorrendben írjuk ki; ha nincs találat, csak a 0 kerül ki. Az idő O(M·N), a memóriaigény O(M·N), mert a mátrixot két menetben dolgozzuk fel.
*/
/*
Hint 1: || Először számold meg fajonként, hány helységben volt előfordulás. Egy faj „máshol is előfordult”, ha ez a szám legalább 2. ||
Hint 2: || Ezután helységenként nézd végig az ott látott fajokat: a helység akkor találat, ha volt benne legalább egy madár, és mindegyik ott látott faj megfelel a feltételnek. Az üres helységeket ne írd ki. ||
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

    vector<int> helyekSzama(N, 0);
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            if (E[i][j] > 0) ++helyekSzama[j];

    vector<int> valasz;
    for (int i = 0; i < M; ++i) {
        bool vanMadar = false;
        bool csakMashol = true;
        for (int j = 0; j < N; ++j) {
            if (E[i][j] == 0) continue;
            vanMadar = true;
            if (helyekSzama[j] < 2) csakMashol = false;
        }
        if (vanMadar && csakMashol) valasz.push_back(i + 1);
    }

    cout << valasz.size() << '\n';
    for (size_t k = 0; k < valasz.size(); ++k) {
        if (k) cout << ' ';
        cout << valasz[k];
    }
    if (!valasz.empty()) cout << '\n';
    return 0;
}
