/*
Megoldás lényege:
Minden alapanyag egységárát egy tömbben tároljuk a sorszámával indexelve, így a recept egy sorából az ár azonnal kikereshető. A recept egy sora az alapanyag sorszámát és a felhasznált darabszámot tartalmazza, ennek költsége az egységár és a darabszám szorzata. Az étel nyersanyagköltsége ezeknek a költségeknek az összege, amelyet egy long long változóban gyűjtünk. Az időigény O(N + K), a legnagyobb érték 100 * 1000 * 1000 = 10^8, ezért long long típust használunk.
*/
/*
Hint 1: || Egy recept-sor költsége az alapanyag egységára szorozva a felhasznált darabszámmal. A sorszám alapján melyik egységárat kell használnod? ||
Hint 2: || Tárold az egységárakat egy tömbben 1-től indexelve, így a recept sorszáma közvetlenül indexként használható. Az összeget long long változóban gyűjtsd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> egyseg(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> egyseg[i];
    }

    int k;
    cin >> k;

    long long koltseg = 0;
    for (int j = 0; j < k; j++) {
        int s;
        long long d;
        cin >> s >> d;
        koltseg += egyseg[s] * d;
    }

    cout << koltseg << "\n";
    return 0;
}
