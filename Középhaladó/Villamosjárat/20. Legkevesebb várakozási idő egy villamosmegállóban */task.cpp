/*
Megoldás lényege:
Egy megállónál a villamos várakozási ideje az indulási és az érkezési idő különbsége. Ha ez nulla, a villamos ott nem állt meg, ezért az ilyen megállót ki kell hagyni. A többi megállót egyetlen menetben végigjárjuk, és nyilvántartjuk a legkisebb pozitív várakozási időt és az ehhez tartozó sorszámot. A szigorú összehasonlítás miatt egyenlőség esetén a korábbi, azaz a kisebb sorszámú megálló marad meg. Az időigény O(N), ami N ≤ 100 mellett elhanyagolható.
*/
/*
Hint 1: || Egy megállónál csak az indulási és az érkezési idő különbségére van szükség. Ha a két idő egyenlő, a villamos ott nem állt meg, ezt a megállót nem szabad figyelembe venni. ||
Hint 2: || Egy ciklusban olvasd be a megállókat, és tartsd nyilván az eddigi legkisebb pozitív várakozási időt és a hozzá tartozó sorszámot. Szigorú < összehasonlítást használj, így egyenlőségnél a korábbi megálló marad meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int bestIdx = 0;
    int bestWait = INT_MAX;
    for (int i = 1; i <= n; i++) {
        int dist, arr, dep;
        cin >> dist >> arr >> dep;
        int wait = dep - arr;
        if (wait > 0 && wait < bestWait) {
            bestWait = wait;
            bestIdx = i;
        }
    }

    cout << bestIdx << ' ' << bestWait << '\n';
    return 0;
}
