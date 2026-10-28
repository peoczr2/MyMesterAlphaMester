/*
Megoldás lényege:
Fordulónként a j-edik helyezett K-j+1 pontot kap, ezeket versenyzőnként gyűjtjük, majd csökkenő sorrendbe rendezzük.
Az első sorba azok a versenyzők kerülnek, akik minden fordulóban szerepeltek, vagyis a szereplésük száma megegyezik a fordulók számával.
Az összetett pontszám a versenyző legjobb L pontjának összege, és ez alapján rendezünk csökkenő sorrendben.
Azonos összeg esetén a csökkenő sorba rendezett pontlisták lexikografikus összehasonlítása dönt (több magasabb pont az előnyösebb), és ha ez is egyforma, a kisebb sorszám áll előbb.
Az időigény O(N·K + P·L·log P), ami bőven belefér a 0,1 másodperces időlimitbe.
*/
/*
Hint 1: || Fordulónként a helyezettek sorrendjéből kiszámolható a pontjuk: az első helyezett K pontot kap, a második K-1-et, és így tovább. Versenyzőnként tárold a kapott pontokat, és számold meg azt is, hány fordulóban szerepelt. ||
Hint 2: || Az első sorba azok kerülnek, akik minden fordulóban szerepeltek. Az összetett pontszámhoz a versenyző pontjait csökkenő sorrendbe rendezd, és csak az első L értéket add össze. ||
Hint 3: || A rendezés kulcsa: először az összeg (csökkenő), majd a csökkenő sorba rendezett pontlisták összehasonlítása (a vector > operátora pontosan ezt teszi), végül a sorszám (növekvő). ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, l;
    cin >> n >> k >> l;

    const int MAXR = 1001;
    vector<int> placed(MAXR, 0);
    vector<vector<int>> pts(MAXR);

    for (int i = 0; i < n; ++i) {
        int h;
        cin >> h;
        for (int j = 0; j < h; ++j) {
            int r;
            cin >> r;
            placed[r]++;
            pts[r].push_back(k - j);
        }
    }

    vector<int> allRounds, people;
    vector<long long> sum(MAXR, 0);
    for (int r = 1; r < MAXR; ++r) {
        if (placed[r] == n) allRounds.push_back(r);
        if (!pts[r].empty()) {
            sort(pts[r].begin(), pts[r].end(), greater<int>());
            if ((int)pts[r].size() > l) pts[r].resize(l);
            for (int x : pts[r]) sum[r] += x;
            people.push_back(r);
        }
    }

    sort(people.begin(), people.end(), [&](int a, int b) {
        if (sum[a] != sum[b]) return sum[a] > sum[b];
        if (pts[a] != pts[b]) return pts[a] > pts[b];
        return a < b;
    });

    cout << allRounds.size();
    for (int x : allRounds) cout << ' ' << x;
    cout << '\n';
    cout << people.size();
    for (int x : people) cout << ' ' << x;
    cout << '\n';
    return 0;
}
