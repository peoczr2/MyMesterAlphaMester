/*
Megoldás lényege:
Hegycsúcs csak a táblázat belső cellája lehet, mert csak ezeknek van mind a négy szomszédjuk. Minden belső cellára eldöntjük, hogy szigorúan magasabb-e a négy szomszédjánál, és a csúcsokat egy 0/1 jelölésű táblázatba írjuk. Ennek kétdimenziós prefix-összegeivel bármely K×K-as részterület csúcsszáma állandó idő alatt megkapható. A bal felső sarkokat sor-, majd oszlopsorrendben végigpróbáljuk, és csak a szigorúan nagyobb érték cseréli a legjobbat, így döntetlen esetén a legkisebb koordinátájú négyzet marad. Az időigény és a memóriaigény O(N·M).
*/
/*
Hint 1: || Csak azok a cellák lehetnek hegycsúcsok, amelyeknek mind a négy szomszédjuk létezik, vagyis a tábla szélső sorában és szélső oszlopában lévők nem. ||
Hint 2: || Készíts 0/1 táblázatot a csúcsokról, majd annak kétdimenziós prefix-összegeivel bármely K×K-as négyzet csúcsszáma O(1) alatt kiszámolható. A négyzeteket sor-, majd oszlopsorrendben végigpróbálva csak a szigorúan nagyobb értéket fogadd el. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> h(n, vector<int>(m));
    for (auto &row : h)
        for (int &x : row) cin >> x;

    vector<vector<int>> pref(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            bool isPeak = i > 0 && i + 1 < n && j > 0 && j + 1 < m
                && h[i][j] > h[i - 1][j] && h[i][j] > h[i + 1][j]
                && h[i][j] > h[i][j - 1] && h[i][j] > h[i][j + 1];
            pref[i + 1][j + 1] = pref[i][j + 1] + pref[i + 1][j] - pref[i][j] + (isPeak ? 1 : 0);
        }
    }

    int bestCount = -1;
    int bestRow = 1;
    int bestCol = 1;
    for (int i = 0; i + k <= n; ++i) {
        for (int j = 0; j + k <= m; ++j) {
            int count = pref[i + k][j + k] - pref[i][j + k] - pref[i + k][j] + pref[i][j];
            if (count > bestCount) {
                bestCount = count;
                bestRow = i + 1;
                bestCol = j + 1;
            }
        }
    }

    cout << bestRow << ' ' << bestCol << '\n';
    return 0;
}
