/*
Megoldás lényege:
Egy megállóban a várakozási idő az indulási idő mínusz az érkezési idő. Az állomásokat sorban, egyetlen beolvasási ciklusban dolgozzuk fel: ha a várakozási idő nagyobb K-nál, az állomás sorszámát betesszük egy vektorba. Mivel a sorszámokat növekvő sorrendben vizsgáljuk, a vektor már rendezett, nincs szükség rendezésre. Először a darabszámot, majd a sorszámokat írjuk ki egy sorba. Az időigény O(N).
*/
/*
Hint 1: || A várakozási idő az indulási idő és az érkezési idő különbsége. Ezt minden állomásra külön kell kiszámolni, és K-val összehasonlítani. ||
Hint 2: || Egyetlen ciklusban olvasd be az állomásokat sorban. Ha a várakozás nagyobb K-nál, tedd a sorszámot egy vektorba, a ciklus végén pedig írd ki a vektor méretét és elemeit. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        int dist, arr, dep;
        cin >> dist >> arr >> dep;
        if (dep - arr > k) {
            ans.push_back(i);
        }
    }

    cout << ans.size();
    for (int x : ans) {
        cout << ' ' << x;
    }
    cout << '\n';
    return 0;
}
