/*
Megoldás lényege:
A lakások árát a feladat szerint nem kell figyelembe venni, csak az alapterületekkel dolgozunk.
Az alapterületeket csökkenő sorrendbe rendezzük, a rendezett sorozat K. eleme (nullától indexelve a K-1. helyen) adja a K. legnagyobb alapterületet.
A válasz azoknak a lakásoknak a száma, amelyek alapterülete ennél nem kisebb: ha nincs ismétlődés, ez pontosan K, egyébként ennél több is lehet.
Az időigény O(N log N), ami N ≤ 100 mellett bőven elég.
*/
/*
Hint 1: || Az ár nem befolyásolja a választ, csak az alapterületek számítanak; ezeket érdemes csökkenő sorrendbe rendezni. ||
Hint 2: || A rendezett sorban a K. elem értékét tekintsd határnak, és számold meg, hány lakás alapterülete nem kisebb ennél; így az egyenlő alapterületű lakások is beleszámítanak. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> meret(n);
    for (int i = 0; i < n; i++) {
        int ar;
        cin >> ar >> meret[i];
    }

    sort(meret.begin(), meret.end(), greater<int>());
    int hatar = meret[k - 1];  // a K. legnagyobb alapterület

    int db = 0;
    for (int m : meret)
        if (m >= hatar) db++;
    cout << db << '\n';
    return 0;
}
