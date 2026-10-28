/*
Megoldás lényege:
A sorozatot balról jobbra haladva daraboljuk. Egy szakasz kezdő elemétől addig lépünk előre, amíg a következő szám nagyobb az előzőnél, így megkapjuk a legtovább tartó szigorúan növekvő szakaszt.
Ha ez a szakasz legalább két elemből áll, leválasztható szakasznak számít, ezért növeljük a számlálót. A következő szakasz a végpont utáni elemmel indul, mert a végpont már a korábbi szakaszhoz tartozik.
Minden elemen legfeljebb kétszer haladunk át, így az időigény O(N).
*/
/*
Hint 1: || A feladat egy végigmenéssel megoldható: egy mutatóval haladj a sorozaton balról jobbra, és közben figyeld, meddig tart a szigorú növekedés. ||
Hint 2: || Egy belső ciklus léptesse a mutatót, amíg a következő elem nagyobb az aktuális elemnél. A ciklus után a mutató az aktuális szakasz végpontján áll. ||
Hint 3: || Ha a szakasz legalább két elemből áll, növeld a számlálót, majd a külső ciklus a végpont utáni elemnél folytatódjon. Az egyelemű „szakasz” nem számít. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int db = 0;
    int i = 0;
    while (i < n) {
        int j = i;
        while (j + 1 < n && a[j] < a[j + 1]) {
            j++;
        }
        if (j > i) {
            db++;
        }
        i = j + 1;
    }
    cout << db << endl;
    return 0;
}
