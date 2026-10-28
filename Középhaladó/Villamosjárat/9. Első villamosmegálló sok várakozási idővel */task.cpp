/*
Megoldás lényege:
Egy megállóban a villamos várakozási ideje az indulási idő mínusz az érkezési idő. Ha a két idő egyenlő, a villamos ott nem állt meg, a várakozás 0. A távolságokra a kérdés megválaszolásához nincs szükség, ezeket beolvasás után figyelmen kívül hagyjuk. A megállókat a bemenet sorrendjében dolgozzuk fel, és minden megállónál kiszámítjuk a várakozást. Az első olyan megállónál, ahol ez szigorúan nagyobb K-nál, azonnal kiírjuk a megálló sorszámát és a várakozási időt, majd kilépünk. Ha az összes megálló végigvizsgálása után sincs találat, a válasz -1. Az időigény O(N), N ≤ 100, így az időlimit bőven teljesül.
*/
/*
Hint 1: || A várakozási idő egy megállóban az indulási idő és az érkezési idő különbsége. A távolságok ehhez nem kellenek. Azt kell megkeresni, hogy melyik az első megálló, ahol ez a különbség nagyobb K-nál. ||
Hint 2: || Olvasd be a megállókat sorban. Minden megállónál számold ki a különbséget, és ha nagyobb K-nál, azonnal írd ki a sorszámot és a különbséget, majd lépj ki a programból. Ha a ciklus találat nélkül fut le, írj -1-et. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        int t, erk, ind;
        cin >> t >> erk >> ind;
        int var = ind - erk;
        if (var > k) {
            cout << i << ' ' << var << '\n';
            return 0;
        }
    }

    cout << -1 << '\n';
    return 0;
}
