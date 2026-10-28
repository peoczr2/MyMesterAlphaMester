/*
Megoldás lényege:
Egy helységben akkor fordult elő mindenféle madár, ha az N faj mindegyikéből
legalább egyet láttunk, vagyis a helység sorában nincs nulla. Soronként végignézzük
a számokat, és ha találunk nullát, a helység nem felel meg. A kész sorok sorszámait
növekvő sorrendben írjuk ki. Az idő O(M*N), ami bőven belefér az 0,5 mp-es időlimitbe.
*/
/*
Hint 1: || Egy helység akkor jó, ha a sorában minden darabszám pozitív, vagyis egyetlen 0 sincs közte. ||
Hint 2: || Soronként olvasd be az N számot, és egy jelzővel jegyezd, volt-e közöttük 0. Ha már találtál nullát, a sor maradék számait is be kell olvasni, különben a következő sor beolvasása elcsúszik. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;

    vector<int> lista;
    for (int i = 1; i <= m; i++) {
        bool mindenfele = true;
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            if (x == 0) mindenfele = false;
        }
        if (mindenfele) lista.push_back(i);
    }

    cout << lista.size() << "\n";
    if (!lista.empty()) {
        for (size_t k = 0; k < lista.size(); k++) {
            if (k > 0) cout << " ";
            cout << lista[k];
        }
        cout << "\n";
    }
    return 0;
}
