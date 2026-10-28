/*
Megoldás lényege:
Egy állomáson nincs utasforgalom, ha sem nem szállt le, sem nem szállt fel senki, vagyis a leszállók és a felszállók száma is nulla. Minden állomást egyszer beolvasunk, és ha mindkét szám nulla, növeljük a számlálót. A végén a számlálót írjuk ki. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Egy állomás akkor nem forgalmas, ha se nem szállt le, se nem szállt fel senki, vagyis mindkét szám nulla. ||
Hint 2: || Minden sort egyszer beolvasol, és ha a leszállók és a felszállók száma is nulla, növeled a számlálót. A számlálót a végén írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int count = 0;
    for (int i = 0; i < n; i++) {
        int le, fel;
        cin >> le >> fel;
        if (le == 0 && fel == 0) count++;
    }

    cout << count << "\n";
    return 0;
}
