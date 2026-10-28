/*
Megoldás lényege:
Minden ember a Honnan és Hova emelet közötti szakaszokon utazik, vagyis a k. és a k+1. emelet között akkor, ha Honnan <= k < Hova. A lift kapacitásának az a szakaszokon mért legnagyobb utasszám felel meg, mert ennyi embert kell egyszerre elvinnie. Az utasszámokat különbségi tömbbel számoljuk: a Honnan emeletnél +1, a Hova emeletnél -1 áll, a prefixösszeg pedig a szakaszonkénti utasszámot adja. Az időigény O(N + M), a tárigény O(N).
*/
/*
Hint 1: || Minden ember egy felfelé vezető szakaszt fed le: a kiindulási és a célemelet közötti szakaszokon utazik. Azt kell megnézni, melyik szakaszon van egyszerre a legtöbb utas. ||
Hint 2: || Használj különbségi tömböt: a kiindulási emeletnél növeld, a célemeletnél csökkentsd a számlálót 1-gyel. Az emeleteken haladva a prefixösszeg adja az adott szakaszon lévő utasok számát, ennek maximuma a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> diff(n + 2, 0);
    for (int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;
        diff[from]++;
        diff[to]--;
    }

    int cur = 0, best = 0;
    for (int k = 0; k < n; k++) {  // a k. és a k+1. emelet közötti szakasz
        cur += diff[k];
        best = max(best, cur);
    }
    cout << best << "\n";
    return 0;
}
