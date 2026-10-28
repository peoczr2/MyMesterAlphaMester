/*
Megoldás lényege:
A palindrom-vizsgálat előtt a szöveget tisztítjuk: a szóközöket elhagyjuk, a betűket kisbetűssé alakítjuk. Ezután két mutatóval az elejéről és a végéről indulunk befelé, és páronként hasonlítjuk a karaktereket. Az első eltérésnél a szöveg nem palindrom, így a vizsgálat azonnal abbamarad, a fordított szöveget nem kell tárolni. Ha minden pár egyezik, a szöveg palindrom. Az időigény O(L), ahol L ≤ 300 000 a szöveg hossza.
*/
/*
Hint 1: || A szóközöket és a kis- és nagybetű közötti különbséget figyelmen kívül kell hagyni: a beolvasott sorból először hagyj ki minden nem betű karaktert, a betűket pedig alakítsd kisbetűssé. ||
Hint 2: || Egy szöveg akkor palindrom, ha az elejéről és a végéről induló karakterek páronként egyeznek. Két indexszel haladj befelé, és az első eltérésnél már tudod a választ, így nincs szükség a fordított szöveg tárolására. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    string line;
    getline(cin, line);

    // Szóközök és nem betű karakterek elhagyása, kisbetűsítés
    string t;
    for (char c : line) {
        if (isalpha(static_cast<unsigned char>(c))) {
            t += static_cast<char>(tolower(static_cast<unsigned char>(c)));
        }
    }

    bool palindrom = true;
    int i = 0;
    int j = static_cast<int>(t.size()) - 1;
    while (i < j) {
        if (t[i] != t[j]) {
            palindrom = false;
            break;
        }
        i++;
        j--;
    }

    cout << (palindrom ? "igen" : "nem") << "\n";
    return 0;
}
