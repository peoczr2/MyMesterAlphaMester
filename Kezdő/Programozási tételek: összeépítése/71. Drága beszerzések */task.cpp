/*
Megoldás lényege:
Az adatok ár szerint csökkenően rendezettek, ezért nem kell újra rendezni őket. Ha X a vizsgált ár, akkor azoknak a termékeknek az eladásait kell összeadni, amelyek ára legalább X, és ezt az összeget az összes eladás felével kell összevetni. A csökkenő sorrendben haladva az eladási darabszámok prefixösszege egyre nő, ezért az első olyan pozíciónál, ahol a prefixösszeg legalább az összes eladás fele, a pozícióhoz tartozó ár lesz a legnagyobb megfelelő ár. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Az ár szerint csökkenő sorrend miatt a legnagyobb ártól haladva egyre több eladott termék kerül a vizsgált csoportba. ||
Hint 2: || Számold a darabszámok prefixösszegét, és az első olyan pozíciónál, ahol 2 * prefixösszeg legalább az összes eladás, írd ki az ott álló árat. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> ar(n), db(n);
    long long osszes = 0;
    for (int i = 0; i < n; i++) {
        cin >> ar[i] >> db[i];
        osszes += db[i];
    }

    long long elso = 0;
    for (int i = 0; i < n; i++) {
        elso += db[i];
        if (2 * elso >= osszes) {
            cout << ar[i] << "\n";
            return 0;
        }
    }

    return 0;
}
