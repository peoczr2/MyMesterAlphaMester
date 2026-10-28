/*
Megoldás lényege:
Egy sziget egy összefüggő szárazföldi szakasz. A hajók két szomszédos sziget között legfeljebb T darab 0-t tudnak átszelni, ezért a bal szélső szigetről indulva csak addig juthatunk el, amíg egy T-nél szélesebb tengerszakasz nem állja az utat. Így a balról elérhető szigetek egy prefixet alkotnak, és ezt egyetlen balról jobbra haladó bejárással megszámoljuk. Jobbról ugyanez a számítás a tömb megfordításával adódik. A kiinduló szigetet is beleszámoljuk, az időigény O(N).
*/
/*
Hint 1: || Egy sziget egy összefüggő 1-esekből álló szakasz. Azt kell megnézned, hogy a bal szélső szigettől kezdve hány sziget érhető el úgy, hogy két szomszédos sziget közötti 0-k száma legfeljebb T. ||
Hint 2: || Balról haladva számold a 0-k egymást követő számát. Amikor új szigethez érsz, ellenőrizd, hogy az előtte lévő tengerszakasz legfeljebb T hosszú volt-e; ha nem, a bejárást abbahagyod. ||
Hint 3: || A jobb oldali eredmény ugyanez a számítás, csak a tömböt fordított sorrendben nézed. A kiinduló szigetet mindkét esetben be kell számolni. ||
*/
#include <bits/stdc++.h>
using namespace std;

// A tömb elejéről (bal szélső szigetről) indulva megszámolja az elérhető szigeteket.
int elerhetoSzigetek(const vector<int>& a, int t) {
    int szam = 1;   // a kiinduló sziget
    int nullak = 0; // az aktuális tengerszakasz hossza
    for (size_t i = 1; i < a.size(); i++) {
        if (a[i] == 0) {
            nullak++;
        } else {
            if (nullak > t) break;  // túl széles tengerszakasz, tovább nem jutnak
            if (nullak > 0) szam++; // új sziget
            nullak = 0;
        }
    }
    return szam;
}

int main() {
    int n, t;
    cin >> n >> t;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> forditott(a.rbegin(), a.rend());
    cout << elerhetoSzigetek(a, t) << " " << elerhetoSzigetek(forditott, t) << "\n";
    return 0;
}
