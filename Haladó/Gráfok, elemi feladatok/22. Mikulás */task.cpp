/*
Megoldás lényege:
Akkor kapja mindenki pontosan egy ajándékot, ha a "kinek ad" leképezés permutáció, vagyis minden tanulót pontosan egyszer céloznak meg.
Egy módosítás egy tanuló célpontját változtatja meg, ezért a legkevesebb módosítás száma pontosan azon tanulók száma, akiket senki sem céloz; ennyi felesleges ajándékozót kell átirányítani.
Egy célponthoz több bejövő él is tartozhat: ezek közül egyet megtartunk, előnyben részesítve azt, amelyet olyan tanuló ad, akit senki sem céloz; a többi ajándékozót átirányítjuk a senki által nem célzott tanulókhoz.
Az átirányított tanuló nem adhat önmagának, ezt a párok ciklikus cseréjével kerüljük el; az időigény O(N).
*/
/*
Hint 1: || Ha minden tanuló pontosan egy ajándékot kap, minden sorszám pontosan egyszer szerepel a bemenetben. Számold meg, hány sorszám hiányzik, és gondold végig, egy módosítás hányat pótolhat. ||
Hint 2: || Ha egy tanulót többen is megcéloztak, közülük legalább egy ajándékozó felesleges; az ő célpontját átállítva egy hiányzó tanulóra már pótolhatod a hiányt. ||
Hint 3: || Ügyelj arra, hogy senki ne adjon önmagának: ha a felesleges ajándékozó éppen a hozzárendelt hiányzó tanuló, a szomszédos párral cseréld meg a párosítást. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> to(n + 1), indeg(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> to[i];
        indeg[to[i]]++;
    }

    // Minden többször megcélzott tanulóhoz pontosan egy bejövő élet tartunk meg.
    // Előnyben részesítjük azt, amelyet olyan tanuló ad, akit senki sem céloz.
    vector<bool> hasKept(n + 1, false);
    vector<bool> stays(n + 1, false);
    for (int i = 1; i <= n; i++) {
        int j = to[i];
        if (indeg[j] >= 2 && indeg[i] == 0 && !hasKept[j]) {
            hasKept[j] = true;
            stays[i] = true;
        }
    }
    for (int i = 1; i <= n; i++) {
        int j = to[i];
        if (indeg[j] >= 2 && !hasKept[j]) {
            hasKept[j] = true;
            stays[i] = true;
        }
    }

    // A felesleges ajándékozók és a senki által nem célzott tanulók párosítása
    vector<int> givers, empties;
    for (int i = 1; i <= n; i++) {
        if (indeg[to[i]] >= 2 && !stays[i]) givers.push_back(i);
    }
    for (int j = 1; j <= n; j++) {
        if (indeg[j] == 0) empties.push_back(j);
    }

    int k = (int)empties.size();
    for (int i = 0; i < k; i++) {
        if (givers[i] == empties[i]) {
            swap(givers[i], givers[(i + 1) % k]);
        }
    }

    cout << k << '\n';
    for (int i = 0; i < k; i++) {
        cout << givers[i] << ' ' << empties[i] << '\n';
    }
    return 0;
}
