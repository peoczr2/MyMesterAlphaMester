/*
Megoldás lényege:
Egy település akkor felel meg, ha van két egymást követő napja, amelyek hőmérséklete legalább 10 fokkal eltér egymástól. Soronként egyszer végigmegyünk az értékeken, és minden napot az előzővel vetünk össze az abszolút különbség szerint. Ha találunk 10 vagy nagyobb eltérést, a település bekerül a listába. A sor végéig minden értéket be kell olvasni, hogy a következő település adatai ne csússzanak el. Az idő O(N·M), a memória O(N).
*/
/*
Hint 1: || Egy település akkor felel meg, ha van olyan két egymás utáni nap, amelyek hőmérséklete legalább 10 fokkal különbözik. Az irány, vagyis az emelkedés vagy csökkenés nem számít. ||
Hint 2: || Soronként haladj végig az értékeken, és mindig az előző nappal vesd össze az aktuálisat, az abszolút különbséget nézve. Ha találsz 10 vagy nagyobb különbséget, a település megfelel, de a sor többi számát is be kell olvasni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> nagy;
    for (int i = 1; i <= n; i++) {
        int elozo;
        cin >> elozo;
        bool nagy_valtozas = false;
        for (int j = 1; j < m; j++) {
            int h;
            cin >> h;
            if (abs(h - elozo) >= 10) nagy_valtozas = true;
            elozo = h;
        }
        if (nagy_valtozas) nagy.push_back(i);
    }

    cout << nagy.size();
    for (int s : nagy) cout << ' ' << s;
    cout << '\n';
    return 0;
}
