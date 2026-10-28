/*
Megoldás lényege:
A dolgozókat sorban, egyesével olvassuk be, és minden dolgozónál csak a kort nézzük: ha az K-nál kisebb, a dolgozó sorszámát (1-től indulva) egy vektorba tesszük. A fizetés a kérdésre nem hat, ezért beolvassuk, de nem tároljuk. A sorszámokat a bemenet sorrendjében adjuk hozzá, így a vektor már növekvő sorrendben van, külön rendezésre nincs szükség. A végén kiírjuk a vektor méretét, majd a sorszámokat. Az időigény O(N), ami a korlátok mellett triviális.
*/
/*
Hint 1: || A kérdés csak a korra vonatkozik, a fizetés nem számít. Minden dolgozónál egyetlen összehasonlítást kell végezni: a kor kisebb-e K-nál. ||
Hint 2: || Tartsd nyilván a fiatalok sorszámait egy vektorban. A sorszám a beolvasás sorrendjéből adódik: az i-edik dolgozó sorszáma i. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> fiatalok;
    for (int i = 1; i <= n; i++) {
        int kor, fizetes;
        cin >> kor >> fizetes;
        if (kor < k) {
            fiatalok.push_back(i);
        }
    }

    cout << fiatalok.size();
    for (int sorszam : fiatalok) {
        cout << " " << sorszam;
    }
    cout << "\n";
    return 0;
}
