/*
Megoldás lényege:
A N tanuló jegyeit egyenként olvassuk be, és minden beolvasott jegynél megnézzük, hogy 1-es-e.
Az 1-eseket egyetlen számlálóban gyűjtjük, így nincs szükség tömbre. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Nem kell tömbbe gyűjteni a jegyeket: minden jegy beolvasás után azonnal eldönthető, hogy 1-es-e. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int db = 0;
    for (int i = 0; i < n; i++) {
        int o;
        cin >> o;
        if (o == 1) db++;
    }
    cout << db << endl;
    return 0;
}
