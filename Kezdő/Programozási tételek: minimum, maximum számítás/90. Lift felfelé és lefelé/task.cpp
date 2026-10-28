/*
Megoldás lényege:
Minden utas vagy felfelé, vagy lefelé utazik: a felfelé menet csak emelkedik, a lefelé menet csak süllyed, így egy utas csak abban a menetben szállítható, amelynek az irányába esik az útja. Egy utas a honnan és a hova közötti összes emeletközi szakaszon utazik. Ezért a két menet kapacitásigénye külön-külön az adott irányú utasok szakaszonkénti egyidejű számának maximuma, a kettő független, és a válasz a két maximum nagyobbika. A szakaszonkénti számot különbségi tömbbel rögzítjük: a kezdő szakasz indexén +1, a célszint indexén -1 áll, majd az előtagösszeg adja az adott szakasz utasszámát. Az időigény O(N + M), a memóriaigény O(N).
*/
/*
Hint 1: || Minden utas egyetlen irányba utazik, ezért a felfelé és a lefelé menet terhelését külön-külön kell számolni. ||
Hint 2: || Az emeletközi szakaszokra nézve számold, hány utas utazik rajtuk egyszerre: egy különbségi tömb elég, és az előtagösszege adja a szakasz utasszámát. ||
Hint 3: || A két menet kapacitása egymástól független, ezért a válasz a felfelé és a lefelé menet szakaszonkénti maximumának nagyobbika. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // fel[k]: a k. és (k+1). emelet közötti szakaszon felfelé utazók különbségi tömbje
    // le[k]: ugyanez lefelé utazókra
    vector<int> fel(n + 2, 0), le(n + 2, 0);
    for (int i = 0; i < m; i++) {
        int honnan, hova;
        cin >> honnan >> hova;
        if (honnan < hova) {
            fel[honnan]++;
            fel[hova]--;
        } else {
            le[hova]++;
            le[honnan]--;
        }
    }

    int felMax = 0, leMax = 0;
    int felSzam = 0, leSzam = 0;
    for (int k = 0; k < n; k++) {
        felSzam += fel[k];
        leSzam += le[k];
        felMax = max(felMax, felSzam);
        leMax = max(leMax, leSzam);
    }

    cout << max(felMax, leMax) << "\n";
    return 0;
}
