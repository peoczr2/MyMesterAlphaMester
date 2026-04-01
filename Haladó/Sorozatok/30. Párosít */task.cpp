/*
Megoldas lenyege:
Balról jobbra haladva mindig az aktuális első ládát akarjuk a párjával
összerendezni. Ha a következő helyen már a párja áll, akkor ezt a blokkot késznek
tekintjük. Ha nem, akkor a párt a sor későbbi részéből egyetlen cserével az
aktuális blokk második helyére hozzuk, majd továbblépünk. Ez a mohó lépés
minden blokkra külön optimalis.
*/
/*
Hint 1: || Minden bolt két egymás melletti ládát akar kapni. ||
Hint 2: || Az aktuális első láda párját mindig a következő helyre érdemes húzni. ||
Hint 3: || Egy ilyen javítás után a korábbi blokkok már nem romlanak el. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(2 * n + 1), pos(n + 1);
    for (int i = 1; i <= 2 * n; ++i) {
        cin >> a[i];
        pos[a[i]] = i;
    }

    int swaps = 0;
    for (int i = 1; i <= 2 * n; i += 2) {
        int x = a[i];
        if (a[i + 1] == x) continue;
        int j = pos[x];
        int y = a[i + 1];
        swap(a[i + 1], a[j]);
        pos[x] = i + 1;
        pos[y] = j;
        ++swaps;
    }

    cout << swaps << '\n';
    return 0;
}
