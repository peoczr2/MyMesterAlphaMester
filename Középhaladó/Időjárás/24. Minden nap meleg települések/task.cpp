/*
Megoldás lényege:
Egy település akkor felel meg, ha az M napra jósolt hőmérséklete mind nagyobb 0-nál. A táblázatot soronként olvassuk be, és minden településhez egy logikai jelzővel nyilvántartjuk, előfordult-e közöttük 0 vagy annál kisebb érték. Így a teljes táblázatot nem kell tárolni. A megfelelő települések sorszámait a beolvasás sorrendjében, tehát növekvő sorrendben írjuk ki, előtte a darabszámmal. Az idő O(N·M), a memória O(N).
*/
/*
Hint 1: || Egy település akkor felel meg, ha az összes napi előrejelzése 0 foknál nagyobb. Már egyetlen 0 vagy annál kisebb érték kizárja a települést. ||
Hint 2: || Soronként olvasd be a hőmérsékleteket, és egy logikai jelzővel jegyezd, volt-e közöttük nem pozitív érték. A sort akkor is végig kell olvasni, ha a település már kiesett, különben a következő település adatai elcsúsznak. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> jo;
    for (int i = 1; i <= n; i++) {
        bool minden_pozitiv = true;
        for (int j = 0; j < m; j++) {
            int h;
            cin >> h;
            if (h <= 0) minden_pozitiv = false;
        }
        if (minden_pozitiv) jo.push_back(i);
    }

    cout << jo.size();
    for (int s : jo) cout << ' ' << s;
    cout << '\n';
    return 0;
}
