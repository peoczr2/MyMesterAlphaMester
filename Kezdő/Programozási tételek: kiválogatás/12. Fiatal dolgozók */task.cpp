/*
Megoldás lényege:
A dolgozókat sorban, egyesével olvassuk be, és minden dolgozónál megnézzük, hogy a kora kisebb-e K-nál.
Ha igen, a dolgozó sorszámát (1-től indulva) egy vektorba tesszük. A fizetést beolvassuk, de a kérdés
nem használja, ezért nem tároljuk. A sorszámokat a bemenet sorrendjében adjuk hozzá, így a vektor már
növekvő sorrendben van, külön rendezésre nincs szükség. A végén kiírjuk a vektor méretét, majd a sorszámokat.
Az időigény O(N), ami a korlátok mellett triviális.
*/
/*
Hint 1: || A kérdés csak a korra vonatkozik: minden dolgozónál azt kell eldönteni, hogy K évnél fiatalabb-e. ||
Hint 2: || A sorszám a bemenet sorrendjét követi: az i-edikként beolvasott dolgozó sorszáma i. A kiíráshoz a sorszámokat egy vektorban gyűjtsd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> young;
    for (int i = 1; i <= n; ++i) {
        int age, salary;
        cin >> age >> salary;
        if (age < k) young.push_back(i);
    }

    cout << young.size();
    for (int id : young) cout << ' ' << id;
    cout << '\n';
    return 0;
}
