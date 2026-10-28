/*
Megoldás lényege:
Minden értékre (0..M-1) elkészítjük a prefixösszeg-tömböt: megadja, hányszor szerepel az adott érték a sorozat első i elemében. Egy [A,B] intervallumban egy érték pontosan akkor fordul elő, ha a B-ig és az A-1-ig számolt darabszám különbsége pozitív. Így minden lekérdezésre az M értéket egyszerűen végignézzük, és megszámoljuk a találatokat. Az előkészítés O(N*M), egy lekérdezés O(M) időt igényel, ami a korlátok mellett bőven belefér az időlimitbe.
*/
/*
Hint 1: || Egy lekérdezésnél elég minden lehetséges értékről eldönteni, hogy előfordul-e az adott indexintervallumban. ||
Hint 2: || Készíts előre prefixösszegeket: minden értékre tárold, hány darab van belőle az első i elemben. ||
Hint 3: || Az [A,B] intervallumban egy v érték pontosan akkor szerepel, ha a B-ig és az A-1-ig számolt darabszámok különbsége pozitív. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> v(n + 1);
    for (int i = 1; i <= n; ++i) cin >> v[i];

    // pref[x][i]: az x érték hányszor szerepel az első i elemben
    vector<vector<int>> pref(m, vector<int>(n + 1, 0));
    for (int x = 0; x < m; ++x)
        for (int i = 1; i <= n; ++i)
            pref[x][i] = pref[x][i - 1] + (v[i] == x ? 1 : 0);

    int db;
    cin >> db;
    while (db--) {
        int a, b;
        cin >> a >> b;
        int cnt = 0;
        for (int x = 0; x < m; ++x)
            if (pref[x][b] - pref[x][a - 1] > 0) ++cnt;
        cout << cnt << "\n";
    }
    return 0;
}
