/*
Megoldás lényege:
Egy adott nap akkor jó, ha ő maga és az őt megelőző nap vastagsága is nagyobb M-nél, mert így legalább 2 egymást követő napon át nagyobb a jég, és ebbe a korcsolyázás napja is beletartozik.
Ezért a szomszédos napok párjait balról jobbra nézzük, és az első megfelelő pár második napjának sorszámát írjuk ki.
Ha nincs ilyen pár, a válasz -1. Az időigény O(N), mert minden napot legfeljebb egyszer nézünk meg.
*/
/*
Hint 1: || Elég két egymást követő mérést vizsgálni: az i-edik nap akkor jó, ha az (i-1)-edik és az i-edik nap vastagsága is nagyobb M-nél. ||
Hint 2: || Egy ciklus az első ilyen párnál megállhat; a kiírt sorszám 1-től számolt nap legyen, és ha egyetlen pár sincs, a válasz -1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    int ans = -1;
    for (int i = 1; i < n; i++) {
        if (v[i - 1] > m && v[i] > m) {
            ans = i + 1;
            break;
        }
    }

    cout << ans << endl;
    return 0;
}
