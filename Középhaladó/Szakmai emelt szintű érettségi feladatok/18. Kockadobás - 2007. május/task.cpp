/*
Megoldás lényege:
A sorozatot maximális, nem növekvő szakaszokra bontjuk: új szakasz ott kezdődik, ahol egy elem nagyobb az előzőnél, mert ott a monoton csökkenő részsorozat megszakad. A szakaszok diszjunktak, ezért a leghosszabb részsorozat mindig egy szakasz teljes hosszával egyezik. Egyetlen menetben haladunk végig, nyilvántartjuk az aktuális szakasz kezdő indexét és hosszát, és ha a hossz szigorúan nagyobb az eddigi legjobbnál, frissítjük a rekordot; a szigorú összehasonlítás miatt az azonos hosszúságúak közül a legkorábbi marad. Az időigény O(N).
*/
/*
Hint 1: || Egy monoton csökkenő részsorozat ott szakad meg, ahol egy elem nagyobb az előzőnél, így a teljes sorozat egymás utáni, egymást nem fedő szakaszokra bomlik. ||
Hint 2: || Egy menetben haladj végig: ha az aktuális elem nagyobb az előzőnél, új szakasz kezdődik ezen az indexen, különben a szakasz hossza eggyel nő; minden lépésben hasonlítsd össze a hosszt az eddigi legjobbal. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> e(n);
    for (int i = 0; i < n; i++) cin >> e[i];

    int legjobbHossz = 0, legjobbKezd = 0;
    int hossz = 0, kezd = 0;
    for (int i = 0; i < n; i++) {
        if (i == 0 || e[i] > e[i - 1]) {
            kezd = i;
            hossz = 1;
        } else {
            hossz++;
        }
        if (hossz > legjobbHossz) {
            legjobbHossz = hossz;
            legjobbKezd = kezd;
        }
    }
    cout << legjobbHossz << " " << legjobbKezd + 1 << "\n";
    return 0;
}
