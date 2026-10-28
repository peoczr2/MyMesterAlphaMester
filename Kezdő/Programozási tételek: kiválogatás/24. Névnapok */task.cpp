/*
Megoldás lényege:
A napokat sorban, egyesével olvassuk be, és minden napnál megnézzük, hogy a napi név egyezik-e a keresett névvel.
Ha igen, a nap sorszámát (1-től indulva) egy vektorba tesszük. Mivel a napokat az év első napjától sorban olvassuk,
a vektor már növekvő sorrendben tartalmazza a sorszámokat, így külön rendezésre nincs szükség.
A végén kiírjuk a találatok számát, majd a sorszámokat egy-egy szóközzel elválasztva. Az időigény O(N), ami a korlátok mellett triviális.
*/
/*
Hint 1: || Minden napnál csak egy nevet kell összevetni a keresettel, így egyetlen bejárás elég. ||
Hint 2: || A nap sorszáma a beolvasás sorrendjéből adódik: az i-edik beolvasott név az i-edik napé. A találatok sorszámait gyűjtsd egy vektorba, és a kiírásnál a vektor méretét írd ki először. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string keresett;
    cin >> n >> keresett;

    vector<int> napok;
    for (int i = 1; i <= n; ++i) {
        string nev;
        cin >> nev;
        if (nev == keresett) napok.push_back(i);
    }

    cout << napok.size();
    for (int nap : napok) cout << ' ' << nap;
    cout << '\n';
    return 0;
}
