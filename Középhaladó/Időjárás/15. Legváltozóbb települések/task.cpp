/*
Megoldás lényege:
Egy település változásának nagyságát két egymást követő nap hőmérséklete közti abszolút különbség adja, az előjel nem számít.
Soronként egyetlen bejárással meghatározzuk minden település legnagyobb napi változását, így a teljes táblázatot sem kell eltárolni.
Ezután megkeressük az összes település közül a legnagyobb változást, és kiírjuk azoknak a településeknek a sorszámát, akiknél ez elérhető, növekvő sorrendben.
Az idő O(N · M).
*/
/*
Hint 1: || Egy változás nagysága nem függ az iránytól, ezért két szomszédos nap különbségének abszolút értékével dolgozz. ||
Hint 2: || Minden településhez tárold a legnagyobb ilyen különbséget, majd keresd meg az összes település közül a legnagyobbat, és írd ki az azt elérő települések sorszámát. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> change(n, 0);
    for (int i = 0; i < n; i++) {
        int prev;
        cin >> prev;
        for (int j = 1; j < m; j++) {
            int cur;
            cin >> cur;
            change[i] = max(change[i], abs(cur - prev));
            prev = cur;
        }
    }

    int best = *max_element(change.begin(), change.end());
    vector<int> chosen;
    for (int i = 0; i < n; i++)
        if (change[i] == best)
            chosen.push_back(i + 1);

    cout << chosen.size();
    for (int x : chosen)
        cout << ' ' << x;
    cout << '\n';
    return 0;
}
