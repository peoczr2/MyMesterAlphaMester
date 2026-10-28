/*
Megoldás lényege:
Minden napra megszámoljuk, hány településen lesz a hőmérséklet 0 foknál kevesebb. A településeket nem kell külön tárolni: soronként olvassuk be az adatokat, és a megfelelő nap számlálóját növeljük. Ezután a napok sorszámait rendezzük: elsőként a számláló szerint csökkenő, egyenlőség esetén a sorszám szerint növekvő sorrendben. Az idő O(N·M + M log M), a memória O(M).
*/
/*
Hint 1: || Minden nap külön oszlopnak tekinthető: elég napon belül számolni, hány településen negatív az érték. Nem kell az egész táblázatot egyszerre tárolni. ||
Hint 2: || Készíts egy M hosszú számláló-tömböt, és olvasás közben minden negatív értéknél növeld a megfelelő nap számlálóját. Rendezéshez a napok sorszámait tárold egy tömbben, a rendezésnél az elsődleges kulcs a számláló csökkenő, a másodlagos a sorszám növekvő legyen. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // fagyos[j]: hány településen lesz a j. napon 0 foknál kevesebb
    vector<int> fagyos(m, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int h;
            cin >> h;
            if (h < 0) fagyos[j]++;
        }
    }

    vector<int> napok(m);
    iota(napok.begin(), napok.end(), 0);
    sort(napok.begin(), napok.end(), [&](int a, int b) {
        if (fagyos[a] != fagyos[b]) return fagyos[a] > fagyos[b];
        return a < b;
    });

    for (int k = 0; k < m; k++) {
        if (k > 0) cout << ' ';
        cout << napok[k] + 1;
    }
    cout << '\n';
    return 0;
}
