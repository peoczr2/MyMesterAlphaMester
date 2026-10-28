/*
Megoldás lényege:
Minden napra először meghatározzuk az aznapi legmagasabb és legalacsonyabb előrejelzést a településeken át, vagyis az oszlopok maximumát és minimumát.
Ezután minden településről ellenőrizzük, hogy valamelyik napon az értéke megegyezik-e az aznapi maximummal vagy minimummal.
Azok a települések maradnak, amelyeknél ez egyetlen napon sem fordul elő, és ezeket növekvő sorrendben írjuk ki.
Mivel a napi szélsőértékek az egész táblázatból adódnak, a bemenetet először teljesen be kell olvasni, majd két bejárással dolgozunk.
Az idő O(N · M).
*/
/*
Hint 1: || Minden naphoz külön keresd meg az aznapi legnagyobb és legkisebb értéket a településeken át, mert ezek lesznek az összehasonlítás alapjai. ||
Hint 2: || Ezután minden településnél nézd meg, hogy van-e olyan nap, amikor az értéke megegyezik az aznapi maximummal vagy minimummal. Azokat a településeket írd ki, amelyeknél ilyen nap nincs. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> h(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> h[i][j];

    vector<int> dayMax(m, INT_MIN), dayMin(m, INT_MAX);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            dayMax[j] = max(dayMax[j], h[i][j]);
            dayMin[j] = min(dayMin[j], h[i][j]);
        }

    vector<int> chosen;
    for (int i = 0; i < n; i++) {
        bool extreme = false;
        for (int j = 0; j < m && !extreme; j++)
            if (h[i][j] == dayMax[j] || h[i][j] == dayMin[j])
                extreme = true;
        if (!extreme)
            chosen.push_back(i + 1);
    }

    cout << chosen.size();
    for (int x : chosen)
        cout << ' ' << x;
    cout << '\n';
    return 0;
}
