/*
Megoldás lényege:
Az i-edik állomásszakasz hossza az i-edik sor első száma, vagyis a távolság az előző megállótól. Egy ciklusban végigmegyünk a szakaszokon sorszám szerint, és ha a hossz nagyobb K-nál, a sorszámát beírjuk egy vektorba. A ciklus 1-től N-ig halad, így a vektor sorszám szerint növekvő sorrendben tartalmazza a találatokat, külön rendezésre nincs szükség. A kiírás első száma a találatok darabszáma, utána következnek a sorszámok. A feltétel szigorú: egyenlő hosszú szakasz nem számít. Időigény O(N), ahol N legfeljebb 100.
*/
/*
Hint 1: || Az állomásszakasz hosszát az első szám adja, az idők erre nincsenek hatással. A feltétel szigorú: a hossznak nagyobbnak kell lennie K-nál, egyenlőnél nem kerül a listába. ||
Hint 2: || Tarts egy vektort a találatok sorszámairól, és a ciklust sorszám szerint haladva töltsd fel. Kiíráskor először a vektor méretét írd ki, utána a sorszámokat szóközzel elválasztva. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> sorszamok;
    for (int i = 1; i <= n; i++) {
        int tav, erk, ind;
        cin >> tav >> erk >> ind;
        if (tav > k) {
            sorszamok.push_back(i);
        }
    }
    cout << sorszamok.size();
    for (int s : sorszamok) {
        cout << ' ' << s;
    }
    cout << '\n';
    return 0;
}
