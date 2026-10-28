/*
Megoldás lényege:
Kezdetben minden helyen egy halom áll, egy konténerrel. Egy átrakásnál egy egész halom mozog át
egy szomszédos halomra, és ez csak akkor lehetséges, ha a két halom számai egymás utáni egész
számokból állnak (az egyik legnagyobbja eggyel kisebb a másik legkisebbjénél). Így minden halom
összefüggő számtartományt fed le, és a halmok sorrendje a sorban sosem változik. Két szomszédos
halom összevonása egy helyet szabadít fel. Az összevonhatóság egy összevonás után is megmarad,
ezért az összevonások sorrendje nem számít: a végállapot egyértelmű. Elég addig összevonni a
szomszédos, összevonható halmokat, amíg lehet. Ezt láncolt listával és munkaveremmel O(N)
időben végezzük. A felszabadítható helyek száma N mínusz a végén maradt halmok száma.
*/
/*
Hint 1: || Egy halom számai akkor vonhatók össze egy másikkal, ha a két halom értékei egy összefüggő számtartományt adnak. Vizsgáld meg, mikor lehet két szomszédos halmot egymásra rakni. ||
Hint 2: || A halmok sorrendje mindig megmarad, így csak a szomszédos halmokat kell nézni. Minden halomnál tárold a legkisebb és a legnagyobb számát: két szomszédos halom összevonható, ha az egyik legnagyobbja eggyel kisebb a másik legkisebbjénél. ||
Hint 3: || Egy összevonás után az összevont halom szomszédai újra összevonhatóvá válhatnak. Tárold a vizsgálandó halmokat egy veremben, és összevonás után az összevont halmot és az előző halmot vedd be újra. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> lo(n), hi(n), prv(n), nxt(n);
    vector<char> alive(n, 1);
    for (int i = 0; i < n; ++i) {
        cin >> lo[i];
        hi[i] = lo[i];
        prv[i] = i - 1;
        nxt[i] = (i + 1 < n) ? i + 1 : -1;
    }

    // A halmok: lo és hi a legkisebb és legnagyobb szám; láncolt lista a sorrendhez
    vector<int> work(n);
    for (int i = 0; i < n; ++i) work[i] = i;
    int blocks = n;
    while (!work.empty()) {
        int l = work.back();
        work.pop_back();
        if (!alive[l]) continue;
        int r = nxt[l];
        if (r == -1) continue;
        if (hi[l] + 1 == lo[r] || hi[r] + 1 == lo[l]) {
            lo[l] = min(lo[l], lo[r]);
            hi[l] = max(hi[l], hi[r]);
            alive[r] = 0;
            nxt[l] = nxt[r];
            if (nxt[r] != -1) prv[nxt[r]] = l;
            --blocks;
            work.push_back(l);
            if (prv[l] != -1) work.push_back(prv[l]);
        }
    }

    cout << n - blocks << '\n';
    return 0;
}
