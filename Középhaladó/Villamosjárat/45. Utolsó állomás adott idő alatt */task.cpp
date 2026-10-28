/*
Megoldás lényege:
Az induló állomástól mért távolság az előző megállók távolságainak összege, ezért a nagyobb sorszámú állomás mindig messzebb van. Az i. állomásra a villamos az érkezési időben ér oda. Egy bejárásban megjegyezzük azt az utolsó állomást, amelyre az érkezési idő kisebb K-nál, és ennek a sorszámát és az érkezési idejét írjuk ki. Mivel az induló állomás 0 perckor van, és K legalább 1, az induló állomás mindig elérhető, így ha egy állomás sem felel meg, a válasz 0 0. Az időigény O(N).
*/
/*
Hint 1: || A távolság az induló állomástól a sorszámmal együtt nő, ezért nem kell összegezni a távolságokat: a legnagyobb sorszámú megfelelő állomás a legtávolabbi. ||
Hint 2: || Kezdetben az eredmény az induló állomás, vagyis 0 és 0. Egy bejárásban minden olyan állomásnál frissítsd az eredményt, ahol az érkezési idő szigorúan kisebb K-nál, így az utolsó ilyen lesz a végeredmény. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    int bestId = 0;
    int bestTime = 0;

    for (int i = 1; i <= n; i++) {
        int dist, arr, dep;
        cin >> dist >> arr >> dep;
        if (arr < k) {
            bestId = i;
            bestTime = arr;
        }
    }

    cout << bestId << ' ' << bestTime << '\n';
    return 0;
}
