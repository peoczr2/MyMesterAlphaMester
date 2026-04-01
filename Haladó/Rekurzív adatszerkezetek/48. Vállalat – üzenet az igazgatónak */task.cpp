/*
Megoldási ötlet:
Egy alkalmazott jelentése pontosan annyi óra alatt jut el az igazgatóhoz, ahány él van közte és az igazgató között,
vagyis ennyi a mélysége a gyökerezett fában. Ezért a feladat egyszerűen az összes K mélységű csúcs kiírása.

Az input az egyes alkalmazottak közvetlen főnökét adja meg, ebből felépíthető a gyereklista. Ezután az 1-es
igazgatóból induló bejárással kiszámoljuk a mélységeket, és növekvő sorrendben kiírjuk azokat, amelyek mélysége K.
Mivel a csúcsokat növekvő sorszám szerint olvassuk be, a végén egy rendezés biztosítja a kért sorrendet.
*/
/*
Hint 1: || Minden továbbítás egy él, tehát a keresett idő éppen a gyökértől mért távolság. ||
Hint 2: || A főnök-listából először érdemes gyereklistát építeni. ||
Hint 3: || A kimenet növekvő sorrendet kér, ezért a végén rendezd a találatokat. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<vector<int>> children(n + 1);
    for (int node = 2; node <= n; ++node) {
        int boss;
        cin >> boss;
        children[boss].push_back(node);
    }

    vector<int> depth(n + 1, 0), result, stack = {1};
    while (!stack.empty()) {
        int node = stack.back();
        stack.pop_back();
        if (depth[node] == k) {
            result.push_back(node);
        }
        for (int child : children[node]) {
            depth[child] = depth[node] + 1;
            stack.push_back(child);
        }
    }

    sort(result.begin(), result.end());
    cout << result.size() << '\n';
    for (int i = 0; i < static_cast<int>(result.size()); ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << result[i];
    }
    cout << '\n';
    return 0;
}