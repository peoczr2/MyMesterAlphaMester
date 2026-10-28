/*
Megoldás lényege:
Egy megállóban a villamos annyit várakozik, amennyi az indulási és az érkezési idő különbsége (Indi - Erki), és ha ez nulla, ott nem állt meg. A kimenet első száma az útközben lévő megállók darabszáma, vagyis N - 1, utána ezeknek a várakozási idői következnek sorrendben. A végállomás (az utolsó sor) várakozása nem kerül a kimenetbe. Egyetlen beolvasás, időigény O(N).
*/
/*
Hint 1: || Egy megállóban a várakozás az indulási és az érkezési idő különbsége, ami minden sorból egyszerűen kiszámítható. ||
Hint 2: || A kimenet első száma az útközbeni megállók száma (N - 1). Ezért az utolsó sor adatát nem kell kiírni: az első N - 1 sor várakozását tárold el, és azt írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> varakozas;
    for (int i = 0; i < n; i++) {
        long long tav, erk, ind;
        cin >> tav >> erk >> ind;
        if (i < n - 1) {
            varakozas.push_back(ind - erk);
        }
    }
    cout << varakozas.size();
    for (long long v : varakozas) {
        cout << ' ' << v;
    }
    cout << '\n';
    return 0;
}
