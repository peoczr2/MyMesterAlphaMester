/*
Megoldás lényege:
Minden versenyzőt külön vizsgálunk a sorszám szerinti sorrendben. Egy versenyző akkor megbízható, ha hat dobása közül egyik sem sikertelen (-1), és a legnagyobb és a legkisebb dobása között legfeljebb 500 cm a különbség. A hat dobást egy tömbbe olvassuk, és ha van közöttük -1, a versenyző kiesik. Különben a tömb minimumából és maximumából kiszámoljuk a különbséget, és ha az legfeljebb 500, a sorszámot felvesszük a listába. Mivel a sorszámok növekvő sorrendben kerülnek a listába, a kiírás már rendezett. A futásidő N·6 lépés.
*/
/*
Hint 1: || Egy versenyző megbízhatóságát két feltétel dönti el, és mindkettő csak a saját hat dobásától függ: nincs köztük sikertelen dobás (-1), és a legnagyobb és a legkisebb dobás különbsége legfeljebb 500. ||
Hint 2: || Versenyzőnként olvasd be a hat dobást egy tömbbe, először nézd meg, van-e benne -1, majd a tömb minimumából és maximumából számold a különbséget. A megfelelő sorszámokat tedd egy listába, és a végén először a listaméretet, utána a listát írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> megbizhato;
    for (int i = 1; i <= n; ++i) {
        int d[6];
        bool sikertelen = false;
        for (int j = 0; j < 6; ++j) {
            cin >> d[j];
            if (d[j] == -1) {
                sikertelen = true;
            }
        }
        if (sikertelen) {
            continue;
        }

        int legkisebb = *min_element(d, d + 6);
        int legnagyobb = *max_element(d, d + 6);
        if (legnagyobb - legkisebb <= 500) {
            megbizhato.push_back(i);
        }
    }

    cout << megbizhato.size() << '\n';
    for (size_t k = 0; k < megbizhato.size(); ++k) {
        if (k > 0) {
            cout << ' ';
        }
        cout << megbizhato[k];
    }
    cout << '\n';
    return 0;
}
