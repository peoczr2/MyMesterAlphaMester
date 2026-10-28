/*
Megoldás lényege:
Egy település legmagasabb várt hőmérséklete a saját sorának maximuma. Az országos maximum a sorok maximumainak legnagyobbja.
A keresett települések azok, amelyek sorának maximuma megegyezik az országos maximummal, a sorszámaikat növekvő sorrendben kell kiírni.
A teljes táblázat nem kell: beolvasás közben soronként elég a maximumot megjegyezni, majd a maximumokat összevetni.
Az idő O(N · M), a memóriaigény O(N).
*/
/*
Hint 1: || Egy település legmelegebb várt értéke a saját sorának maximuma. Az országos maximumot a sorok maximumainak maximumából kapod meg. ||
Hint 2: || Ne tárold a teljes táblázatot: beolvasás közben minden sorhoz csak a maximumot jegyezd meg. A végén a maximummal egyező sorok sorszámait írd ki növekvő sorrendben, elöl a darabszámmal. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> rowMax(n);
    for (int i = 0; i < n; i++) {
        rowMax[i] = INT_MIN;
        for (int j = 0; j < m; j++) {
            int h;
            cin >> h;
            rowMax[i] = max(rowMax[i], h);
        }
    }

    int globalMax = *max_element(rowMax.begin(), rowMax.end());

    vector<int> towns;
    for (int i = 0; i < n; i++)
        if (rowMax[i] == globalMax)
            towns.push_back(i + 1);

    cout << towns.size();
    for (int t : towns)
        cout << ' ' << t;
    cout << '\n';
    return 0;
}
