/*
Megoldás lényege:
Legyen W az összes fehér üveg száma, M a rekeszenkénti üvegszám. A végállapotban k = W / M rekesz lesz tisztán fehér, a maradék r = W % M fehér üveg egyetlen vegyes rekeszben marad (ha r > 0), a többi rekesz tisztán színes.
Egy csere egyetlen fehér üveget mozgat át egyik rekeszből a másikba, ezért a minimális cserék száma azoknak a fehér üvegeknek a száma, amelyeknek ki kell kerülniük a jelenlegi rekeszükből.
A legtöbb fehér üveget tartalmazó k rekeszt érdemes tisztán fehérnek hagyni, így ezekből nem kell fehéret kivinni; a maradék rekeszek fehér üvegeit összeadjuk.
Ha r > 0, a vegyes rekesz (a maradék rekeszek közül a legtöbb fehérrel) min(U, r) fehér üveget megtarthat, ezt a végén levonjuk.
A rendezés miatt az időigény O(N log N).
*/
/*
Hint 1: || Egy csere egyetlen fehér üveget mozgat át egy másik rekeszbe; gondold végig, hány tiszta fehér rekesz lehet a végén, és hány fehér üveg marad a vegyes rekeszben. ||
Hint 2: || Rendezd a rekeszeket a bennük lévő fehér üvegek száma szerint csökkenő sorrendbe: a legtöbb fehér üveget tartalmazó rekeszeket érdemes tisztán fehérnek hagyni, mert ezekből nem kell fehéret kivinni. ||
Hint 3: || A többi rekesz fehér üvegei közül minden fehér kiszállításra kerül, kivéve azt, ami a vegyes rekeszben maradhat: ez a rekesz a maradék rekeszek közül a legtöbb fehérrel rendelkező, és itt legfeljebb a maradék darabszám (W mod M) fehér maradhat. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long m;
    int n;
    cin >> m >> n;
    vector<long long> u(n);
    long long w = 0;
    for (auto &x : u) {
        cin >> x;
        w += x;
    }

    sort(u.rbegin(), u.rend());  // csökkenő sorrend: a legtöbb fehér elöl

    long long full = w / m;  // tisztán fehér rekeszek száma
    long long rem = w % m;   // a vegyes rekeszben maradó fehér üvegek száma

    long long ans = 0;
    for (long long i = full; i < n; i++) ans += u[i];
    if (rem > 0) ans -= min(u[full], rem);

    cout << ans << '\n';
    return 0;
}
