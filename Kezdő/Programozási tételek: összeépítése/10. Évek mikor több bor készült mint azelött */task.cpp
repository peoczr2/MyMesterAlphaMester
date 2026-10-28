/*
Megoldás lényege:
Az ár nem befolyásolja a feladatot, csak a mennyiségek számítanak. Egy év akkor „rekord”, ha a mennyisége nagyobb, mint az összes korábbi év mennyiségének maximuma. Ezt egy végigmenéssel számoljuk, közben nyilvántartjuk az eddigi legnagyobb mennyiséget. Az első évnek nincs korábbi éve, ezért rá a feltétel nem vonatkozik. A szigorú nagyobb reláció miatt az azonos mennyiségű év nem számít rekordnak (a minta példája is ezt mutatja). A kimenetbe a rekordok darabszáma kerül, utána a sorszámaik; ha nincs rekord, a darabszám 0, és ez lesz az egyetlen kiírt szám. Az időigény O(N), ami 100 éves adatnál elhanyagolható.
*/
/*
Hint 1: || Az ár a feladatban nem számít, csak a mennyiség. Azt kell eldönteni, hogy egy év mennyisége nagyobb-e az összes korábbi év mennyiségénél. ||
Hint 2: || Futó maximumot használj: egy változóban tartsd az eddigi legnagyobb mennyiséget, és minden év előtt nézd meg, nagyobb-e nála. Az első évet külön kezeld, mert neki nincs korábbi éve. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> rekordok;
    int legnagyobb = 0;
    for (int i = 1; i <= n; i++) {
        int mennyiseg, ar;
        cin >> mennyiseg >> ar;
        if (i > 1 && mennyiseg > legnagyobb) {
            rekordok.push_back(i);
        }
        legnagyobb = max(legnagyobb, mennyiseg);
    }

    cout << rekordok.size();
    for (int x : rekordok) cout << " " << x;
    cout << endl;
    return 0;
}
