/*
Megoldási ötlet:
Minden tagnak legfeljebb egy A- és egy B-típusú közvetlen beosztottja lehet, tehát minden csúcsnak két
„helye” van. Az új tag pontosan akkor helyezhető be egy csúcs alá, ha az adott csúcs valamelyik helye még üres.

Ezért minden csúcs részfájára kiszámítjuk, hány üres A/B hely található benne. Egy csúcs saját hozzájárulása
0, 1 vagy 2 attól függően, hogy az A- és B-gyereke közül melyik hiányzik. A részfaösszeg ezek összege.
Az első kérdés a gyökér saját üres helyeinek száma, a második a gyökér A-gyerekének részfájában levő üres helyek száma,
a harmadik pedig a gyökér B-gyerekének részfájára ugyanez.
*/
/*
Hint 1: || Egy új tag csak közvetlen beosztottként kerül valaki alá, tehát valójában az üres gyerekhelyeket kell számolni. ||
Hint 2: || Minden tagnál legfeljebb két hely lehet: egy A és egy B. ||
Hint 3: || A második és harmadik kérdéshez nem kell külön logika: elég a megfelelő gyökérgyerek részfájában összeszámolni az üres helyeket. ||
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> childA(n + 1, 0), childB(n + 1, 0);
    for (int node = 2; node <= n; ++node) {
        int boss;
        char type;
        cin >> boss >> type;
        if (type == 'A') {
            childA[boss] = node;
        } else {
            childB[boss] = node;
        }
    }

    vector<int> subtreeFree(n + 1, 0);
    for (int node = n; node >= 1; --node) {
        subtreeFree[node] = (childA[node] == 0) + (childB[node] == 0);
        if (childA[node] != 0) {
            subtreeFree[node] += subtreeFree[childA[node]];
        }
        if (childB[node] != 0) {
            subtreeFree[node] += subtreeFree[childB[node]];
        }
    }

    cout << (childA[1] == 0) + (childB[1] == 0) << '\n';
    cout << (childA[1] ? subtreeFree[childA[1]] : 0) << '\n';
    cout << (childB[1] ? subtreeFree[childB[1]] : 0) << '\n';
    return 0;
}
