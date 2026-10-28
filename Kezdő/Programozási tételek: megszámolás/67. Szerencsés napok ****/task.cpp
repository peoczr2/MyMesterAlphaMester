/*
Megoldás lényege:
Az első és az utolsó nap kivételével minden napot besorolunk: szerencsés (+1), ha a keresete nagyobb mindkét szomszédos napénál, szerencsétlen (−1), ha kisebb mindkettőnél, egyébként 0. Egy intervallum pontosan akkor megfelelő, ha mindkét végpontja szerencsés nap, és benne a szerencsés és szerencsétlen napok különbsége pozitív. Ezt a különbséget prefixösszeggel O(1) időben kérdezzük le, így a végpontok minden (l, r) párját kipróbálva O(N²) időben számolunk; N ≤ 5000 mellett ez bőven belefér az időkorlátba. A memóriaigény O(N).
*/
/*
Hint 1: || Minden napot külön nézz meg: egy nap szerencsés, ha a keresete nagyobb mind a két szomszédos napénál, szerencsétlen, ha kisebb mindkettőnél. Az első és az utolsó nap egyik csoportba sem tartozik. ||
Hint 2: || Írj minden napra +1-et (szerencsés), −1-et (szerencsétlen) vagy 0-t, és építs belőle prefixösszeg-tömböt. Az [l, r] intervallumban a szerencsés és szerencsétlen napok különbsége P[r] − P[l − 1]. ||
Hint 3: || Az intervallum akkor felel meg, ha l és r is szerencsés nap (l = r is lehet, az egyetlen szerencsés napból álló intervallum is számít), és a különbség pozitív. Ezeket a párokat kell megszámolni, és mivel N legfeljebb 5000, kettős ciklus is elég. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> kereset(n + 2, 0);
    for (int i = 1; i <= n; i++)
        cin >> kereset[i];

    // tipus[i]: +1 szerencsés, −1 szerencsétlen, 0 egyéb (az első és az utolsó nap is ide tartozik)
    vector<int> tipus(n + 2, 0);
    for (int i = 2; i < n; i++) {
        if (kereset[i] > kereset[i - 1] && kereset[i] > kereset[i + 1])
            tipus[i] = 1;
        else if (kereset[i] < kereset[i - 1] && kereset[i] < kereset[i + 1])
            tipus[i] = -1;
    }

    // pref[i] = tipus[1] + ... + tipus[i]
    vector<int> pref(n + 1, 0);
    for (int i = 1; i <= n; i++)
        pref[i] = pref[i - 1] + tipus[i];

    long long valasz = 0;
    for (int l = 1; l <= n; l++) {
        if (tipus[l] != 1)
            continue;
        for (int r = l; r <= n; r++) {
            if (tipus[r] == 1 && pref[r] - pref[l - 1] > 0)
                valasz++;
        }
    }
    cout << valasz << "\n";
    return 0;
}
