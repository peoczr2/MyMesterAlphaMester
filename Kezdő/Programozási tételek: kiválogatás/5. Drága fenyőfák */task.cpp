/*
Megoldás lényege:
A fákat sorban egyszer olvassuk be, és minden fa árát összehasonlítjuk K-val. Ha az ár nagyobb K-nál, a fa sorszámát (1-től számozva) egy vektorba tesszük. Mivel a sorszámokat a beolvasás sorrendjében gyűjtjük, a lista már növekvő sorrendben lesz, rendezésre nincs szükség. A kiírás első száma a találatok darabszáma, utána a sorszámok szóközzel elválasztva következnek. Az idő O(N).
*/
/*
Hint 1: || Minden fa árát pontosan egyszer kell megnézni: ha K-nál nagyobb, a fa sorszámát el kell tárolni. ||
Hint 2: || A sorszámokat az olvasás sorrendjében gyűjtsd egy vektorba; így nem kell rendezni, és a darabszám is a lista mérete lesz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;

    vector<int> sorszamok;
    for (int i = 1; i <= n; i++) {
        long long ar;
        cin >> ar;
        if (ar > k) sorszamok.push_back(i);
    }

    cout << sorszamok.size();
    for (int s : sorszamok) cout << ' ' << s;
    cout << '\n';
    return 0;
}
