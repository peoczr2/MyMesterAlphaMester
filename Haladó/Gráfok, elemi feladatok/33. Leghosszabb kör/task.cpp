/*
Megoldás lényege:
Mindenkinek pontosan egy legjobb barátja van, így minden csúcsból egyetlen kimenő él indul: a gráf funkcionális gráf.
Ebben egy kezdőcsúcsból a barátokon végigkövetve az út egyértelmű: vagy egy korábban már bejárt csúcsba jutunk, vagy egy körbe érünk.
Minden csúcsot pontosan egyszer járunk be úgy, hogy a bejárás kezdőcsúcsát és a lépésszámot megjegyezzük. Ha az aktuális bejárásban korábban látott csúcshoz érünk, a kör hossza a két lépésszám különbsége.
A körök hosszainak maximuma adja a választ. Mivel minden csúcs csak egy bejárásban szerepel, az idő O(N).
*/
/*
Hint 1: || Mindenkinek pontosan egy kimenő éle van, a legjobb barátja, így egy csúcsból indulva a bejárás egyetlen úton halad. ||
Hint 2: || Egy kezdőcsúcsból a barátokon haladva vagy egy korábban már bejárt csúcsba érsz, vagy egy körbe; a kör hosszát a lépésszámok különbségéből kapod. ||
Hint 3: || Minden csúcsnál jegyezd meg, melyik kezdőcsúcsú bejárásban és hányadik lépésben érintetted. Ha ugyanabban a bejárásban érsz vissza egy csúcsra, a különbség a kör hossza. Csak még nem látott csúcsból indíts új bejárást. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> nx(n + 1);
    for (int i = 1; i <= n; i++) cin >> nx[i];

    vector<int> stamp(n + 1, 0), pos(n + 1, 0);
    int best = 0;
    for (int s = 1; s <= n; s++) {
        if (stamp[s]) continue;
        int v = s, step = 0;
        while (!stamp[v]) {
            stamp[v] = s;
            pos[v] = step++;
            v = nx[v];
        }
        if (stamp[v] == s) best = max(best, step - pos[v]);
    }
    cout << best << '\n';
    return 0;
}
