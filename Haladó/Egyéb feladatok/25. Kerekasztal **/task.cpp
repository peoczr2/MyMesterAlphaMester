/*
Megoldás:
Egy kiválasztott eltolásnál a kívánt végállapot egy rögzített körkörös elforgatása az 1..N
sorozatnak. Ha a jelenlegi ülésrendből ehhez akarunk eljutni tetszőleges párcserékkel, akkor a
szükséges cserék száma N mínusz a megfelelő permutáció ciklusainak száma.

Az s eltolás esetén a pos helyen ülő k lovag célhelye (s + k) mod N. Ebből közvetlenül felírható
a permutáció, és megszámolható a ciklusainak száma. Minden lehetséges eltolást végigpróbálunk,
és a minimális csereigényt választjuk.

Mivel N legfeljebb 10000, az O(N^2) vizsgálat még elfogadható.
*/
/*
Hint 1: || Egy rögzített körkörös célrendre a minimális párcsereszámot a ciklusfelbontásból lehet megkapni. ||
Hint 2: || Nem kell minden célrendet külön tárolni: egy lovag célhelye az eltolásból és a sorszámából azonnal kiszámítható. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<unsigned short> knights(n);
    for (int i = 0; i < n; ++i) {
        int knight;
        cin >> knight;
        knights[i] = static_cast<unsigned short>(knight - 1);
    }

    vector<char> visited(n);
    int best = n;

    for (int shift = 0; shift < n; ++shift) {
        fill(visited.begin(), visited.end(), 0);
        int cycles = 0;
        for (int i = 0; i < n; ++i) {
            if (visited[i]) {
                continue;
            }
            ++cycles;
            int current = i;
            while (!visited[current]) {
                visited[current] = 1;
                current = knights[current] + shift;
                if (current >= n) {
                    current -= n;
                }
            }
        }
        best = min(best, n - cycles);
    }

    cout << best << '\n';
    return 0;
}