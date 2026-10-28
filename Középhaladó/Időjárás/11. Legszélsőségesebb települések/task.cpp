/*
Megoldás lényege:
Minden településre egyetlen bejárással meghatározzuk a legnagyobb és a legkisebb várt hőmérsékletet, és ezek különbségét (a szélsőségességet) eltároljuk.
Ezután megkeressük a legnagyobb különbséget, és kiírjuk azoknak a településeknek a sorszámát, amelyeknél ez a különbség elérhető.
A sorszámokat növekvő sorrendben írjuk ki, mert a településeket sorban dolgozzuk fel.
Az idő O(N · M).
*/
/*
Hint 1: || Egy település szélsőségességét a legnagyobb és a legkisebb érték különbsége adja, ezt sorról sorra egyetlen bejárással ki lehet számolni. ||
Hint 2: || Tárold el minden település különbségét egy tömbben, utána keresd meg a legnagyobb értéket, és írd ki azoknak a településeknek a sorszámát, akiknél ez éri el. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> range(n);
    for (int i = 0; i < n; i++) {
        int mx = INT_MIN, mn = INT_MAX;
        for (int j = 0; j < m; j++) {
            int h;
            cin >> h;
            mx = max(mx, h);
            mn = min(mn, h);
        }
        range[i] = mx - mn;
    }

    int best = *max_element(range.begin(), range.end());
    vector<int> chosen;
    for (int i = 0; i < n; i++)
        if (range[i] == best)
            chosen.push_back(i + 1);

    cout << chosen.size();
    for (int x : chosen)
        cout << ' ' << x;
    cout << '\n';
    return 0;
}
