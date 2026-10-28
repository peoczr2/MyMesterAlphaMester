/*
Megoldás lényege:
Minden lakást egyesével olvasunk be, és megnézzük, hogy az alapterület nagyobb-e 100 négyzetméternél, az ára pedig kisebb-e 40 millió forintnál.
Ha mindkét feltétel teljesül, növeljük a számlálót, így a lakások tárolására nincs szükség.
A két feltétel egyetlen logikai ÉS kifejezésben szerepel, az időigény O(N).
*/
/*
Hint 1: || Minden lakásra külön kell eldöntened, hogy az alapterületre és az árra is teljesül-e a feltétel. ||
Hint 2: || Nem kell tömbben tárolni az adatokat: a lakásokat soronként olvashatod be, és egy számlálóval összegezheted a megfelelőket. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int db = 0;
    for (int i = 0; i < n; i++) {
        int terulet, ar;
        cin >> terulet >> ar;
        if (terulet > 100 && ar < 40) {
            db++;
        }
    }
    cout << db << endl;
    return 0;
}
