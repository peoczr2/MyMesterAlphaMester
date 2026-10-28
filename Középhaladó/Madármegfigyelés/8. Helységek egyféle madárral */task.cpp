/*
Megoldás lényege:
Helységenként megszámoljuk, hány különböző madárfaj fordult elő ott, vagyis hány
darabszám nagyobb nullánál. Csak azok a helységek érdekesek, ahol ez a szám pontosan
1. A darabszám nagysága nem számít, csak az, hogy volt-e belőle megfigyelés.
Soronként egyszer olvassuk be a számokat, és közben számoljuk a pozitív értékeket.
Az idő O(M*N), ami bőven belefér az 0,1 mp-es időlimitbe.
*/
/*
Hint 1: || Egy helységről elég tudni, hány különböző fajt láttál benne. Egy faj akkor számít, ha a darabszáma nagyobb nullánál. ||
Hint 2: || Soronként egy számlálóval mehetsz végig a N számon: minden pozitív számnál növeld. A sor végén, ha a számláló pontosan 1, tedd a sor sorszámát a listába. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;

    vector<int> lista;
    for (int i = 1; i <= m; i++) {
        int fajok = 0;
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            if (x > 0) fajok++;
        }
        if (fajok == 1) lista.push_back(i);
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
