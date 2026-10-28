/*
Megoldás lényege:
Egy megállónál a villamos akkor áll meg, ha az indulási idő nagyobb az érkezési időnél, ezt a feltételt kell minden megállóra ellenőrizni. A feladat szerint a 0. és a végállomás (N.) nem számít bele, ezért a számlálás az 1-től N-1-ig tartó sorszámokra terjed. A távolságok nem befolyásolják a döntést, csak beolvassuk őket. Egy bejárással megkapjuk a darabszámot, így az időigény O(N).
*/
/*
Hint 1: || Egy megállóban a villamos akkor áll meg, ha az indulási idő nagyobb az érkezési időnél. Ha a két idő egyenlő, a villamos nem állt meg ott. ||
Hint 2: || Olvasd be a megállókat sorban, és az 1-től N-1-ig tartó sorszámokra számold meg, hányszor teljesül az indulás-nagyobb feltétel. Az utolsó megállót ne vedd figyelembe. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int count = 0;
    for (int i = 1; i <= n; i++) {
        int dist, arr, dep;
        cin >> dist >> arr >> dep;
        if (i < n && arr < dep) {
            count++;
        }
    }

    cout << count << '\n';
    return 0;
}
