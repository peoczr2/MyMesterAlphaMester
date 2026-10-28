/*
Megoldás lényege:
Először fajonként megkeressük a legnagyobb egyedszámot az összes helység között. Ezután egy helység akkor "jó", ha minden fajra nézve a saját darabszáma megegyezik ezzel a maximummal (az egyenlőség is megengedett). Mivel a maximumokat csak a teljes adat ismeretében lehet meghatározni, a mátrixot el kell tárolni, ez 50·200 szám, ami kis helyet foglal. Az idő O(M·N), a memóriaigény O(M·N).
*/
/*
Hint 1: || Fajonként előbb számold ki, melyik helységben látták a legtöbb egyedet. Ehhez minden helység adatát meg kell őrizned, mert a maximum az összes helység ismeretében dönthető el. ||
Hint 2: || Ezután helységenként ellenőrizd, hogy minden fajra a helység értéke megegyezik-e az adott faj maximumával. Ha van ilyen helység, a válasz 1, különben 0. ||
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

    vector<int> legtobb(N, 0);
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            legtobb[j] = max(legtobb[j], E[i][j]);

    bool van = false;
    for (int i = 0; i < M; ++i) {
        bool jo = true;
        for (int j = 0; j < N; ++j)
            if (E[i][j] != legtobb[j]) jo = false;
        if (jo) van = true;
    }

    cout << (van ? 1 : 0) << '\n';
    return 0;
}
