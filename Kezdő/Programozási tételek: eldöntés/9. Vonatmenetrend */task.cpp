/*
Megoldás lényege:
A menetrend minden sorában a 9999-es indulási idő azt jelenti, hogy az adott vonat az ott található városban véget ér.
A kérdés ezért csak az: van-e olyan sor, ahol 9999 az indulási idő, de a város nem Pécs.
Ha van ilyen, valamelyik vonat nem Pécsig közlekedik, a válasz NEM; különben IGEN.
A bemenetet egyetlen bejárással olvassuk végig, így az időigény O(N), ami N ≤ 100 esetén nyilvánvalóan gyors.
*/
/*
Hint 1: || Nem kell a vonatokat egyenként követni: a 9999-es indulási idő jelzi a végállomást, így elég ezeket a sorokat megnézni, és azt ellenőrizni, hogy a városuk Pecs-e. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    bool igen = true;
    for (int i = 0; i < n; i++) {
        string varos;
        int erkezes, indulas;
        cin >> varos >> erkezes >> indulas;

        // 9999 indulás: a vonat itt végállomás, ez csak Pécsen fordulhat elő
        if (indulas == 9999 && varos != "Pecs") {
            igen = false;
        }
    }

    cout << (igen ? "IGEN" : "NEM") << "\n";
    return 0;
}
