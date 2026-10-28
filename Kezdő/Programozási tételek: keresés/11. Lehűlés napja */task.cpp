/*
Megoldás lényege:
Minden naphoz beolvassuk a várható minimum- és maximumhőmérsékletet, és az előző napi minimumot egy változóban őrizzük.
Az első olyan napnál, amelyen a napi maximum kisebb az előző napi minimumnál, megállunk, és ennek a napnak a sorszámát írjuk ki.
Ha ilyen nap nincs, a válasz -1. Az időigény O(N), mert minden napot legfeljebb egyszer nézünk meg.
*/
/*
Hint 1: || A keresett nap a 2. naptól kezdve lehet, és az összehasonlításhoz elég az előző nap adatát ismerni. ||
Hint 2: || Tárold el az előző nap minimumát, és minden napnál hasonlítsd a mai maximumot ehhez; az első találatnál a sorszámot megjegyezve már nem kell tovább keresni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int prevMin = 0;
    int ans = -1;
    for (int i = 1; i <= n; i++) {
        int minT, maxT;
        cin >> minT >> maxT;
        if (i > 1 && ans == -1 && maxT < prevMin) {
            ans = i;
        }
        prevMin = minT;
    }

    cout << ans << endl;
    return 0;
}
