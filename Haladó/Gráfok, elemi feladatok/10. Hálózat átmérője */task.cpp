/*
Megoldás lényege:
Mivel minden I. gép szülője J < I, a csúcsokat N-től 2-ig csökkenő sorrendben dolgozhatjuk fel: amikor egy csúcshoz érünk, minden gyereke már feldolgozva van, így ismerjük a csúcsból lefelé vezető leghosszabb utat. Minden csúcsnál nyilvántartjuk a két leghosszabb gyerekágat (a legnagyobbat és a második legnagyobbat); ezek összege az adott csúcson átmenő legnagyobb út hossza. A hálózat átmérője ezeknek az összegeknek a maximuma, élben mérve. A fát nem kell élek szerint bejárni, az idő O(N), a memória O(N).
*/
/*
Hint 1: || A szülő sorszáma mindig kisebb, ezért a fát nem kell bejárni: a gépeket N-től 2-ig csökkenő sorrendben dolgozd fel, és közben a szülőjüket frissítsd. ||
Hint 2: || Minden csúcshoz tárold a két leghosszabb lefelé vezető ág hosszát. Egy gyerek feldolgozása után a szülő két ágát frissítsd, és az átmérőt a két ág összegének maximumával növeld. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> parent(n + 1, 0);
    for (int i = 2; i <= n; i++) cin >> parent[i];

    vector<int> longest(n + 1, 0), second(n + 1, 0);
    int diameter = 0;
    for (int i = n; i >= 2; i--) {
        int p = parent[i];
        int depth = longest[i] + 1;
        if (depth > longest[p]) {
            second[p] = longest[p];
            longest[p] = depth;
        } else if (depth > second[p]) {
            second[p] = depth;
        }
        diameter = max(diameter, longest[p] + second[p]);
    }

    cout << diameter << "\n";
    return 0;
}
