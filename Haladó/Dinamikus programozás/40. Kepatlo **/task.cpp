/*
Egy oszlopban a határvonal összefüggő függőleges szakaszt foglal el: a szakasz felett lévő pixelek a jobb-felső,
az alatta lévők a bal-alsó oldalra esnek, a szakasz pixelei nem számítanak. Az oszlopok között a vonal az egyik
oszlop alsó pontjából lép a következő oszlop felső pontjába, ezért a DP állapota az oszlop alsó sorának indexe.
Egy oszlop költsége prefixösszegekből számolható (fekete a felső, fehér az alsó részen), az átmenetnél pedig az
előző állapotok futó minimumát tartjuk. Így az egész DP O(N²) időben fut, a végső válasz az utolsó oszlop
alsó sorának (N) értéke.
*/
/*
Hint 1: || Egy oszlopban a vonal egy függőleges szakaszt foglal el: a szakasz felett a fekete, alatta a fehér pixelek számítanak. ||
Hint 2: || A vonal egy oszlop alsó pontjából lép tovább, ezért a DP állapota az oszlop alsó sorának indexe legyen. ||
Hint 3: || Egy új alsó ponthoz az összes olyan felső pont versenyez, amely nem nagyobb nála, ezért futó minimumot kell tartani. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> a(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> a[i][j];
        }
    }

    const int INF = 1e9;
    // leave[b]: az eddigi oszlopok minimális költsége, ha az utolsó feldolgozott oszlopot a vonal a b. sorban hagyja el
    vector<int> leave(n + 1, INF);
    leave[1] = 0;

    for (int col = 1; col <= n; ++col) {
        vector<int> black(n + 1, 0), white(n + 1, 0);
        for (int row = 1; row <= n; ++row) {
            black[row] = black[row - 1] + (a[row][col] == 0);
            white[row] = white[row - 1] + (a[row][col] == 1);
        }

        vector<int> next(n + 1, INF);
        int prefix_best = INF;
        for (int b = 1; b <= n; ++b) {
            // az oszlop felső pontja t <= b: a t. sortól a b. sorig fut a vonal
            if (leave[b] < INF) {
                prefix_best = min(prefix_best, leave[b] + black[b - 1]);
            }
            next[b] = prefix_best + (white[n] - white[b]);
        }
        leave = next;
    }

    cout << leave[n] << '\n';
    return 0;
}
