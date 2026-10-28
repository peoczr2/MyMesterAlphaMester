/*
Megoldás lényege:
A betegek érkezés szerint kerülnek sorra, ezért minden beteg kezelésének kezdete
max(érkezés, az előző beteg befejezése), a befejezés pedig kezdés + kezelési idő.
Ebből a várakozási idő közvetlenül adódik; a legnagyobb várakozású beteg közül a
legkisebb sorszámút választjuk. Az egyidejűleg a rendelőben lévők maximumát az érkezési és a
befejezési idők két rendezett sorozatának összefésülésével kapjuk: a befejezési idők
is nőnek, így lineáris időben, egy mutatópárral számolható. Ha mindenki kezelése
azonnal kezdődik, mindhárom kiírt szám 0.
*/
/*
Hint 1: || Mivel a betegek érkezés szerint sorra kerülnek, minden beteg kezdési ideje az előző beteg befejezési idejéből és a saját érkezéséből számolható. ||
Hint 2: || Az egyidejű jelenlévők száma: érkezéskor +1, befejezéskor -1; ha az érkezési és befejezési idők nőnek, két mutatóval végig lehet menni rajtuk. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> arr(n), fin(n), wait(n);
    long long freeAt = 0;  // a rendelő szabaddá válásának ideje
    for (int i = 0; i < n; ++i) {
        long long k;
        cin >> arr[i] >> k;
        long long start = max(arr[i], freeAt);
        wait[i] = start - arr[i];
        fin[i] = start + k;
        freeAt = fin[i];
    }

    int bestId = 0;
    long long bestWait = 0;
    for (int i = 0; i < n; ++i) {
        if (wait[i] > bestWait) {  // szigorú >: a legkisebb sorszám marad
            bestWait = wait[i];
            bestId = i + 1;
        }
    }

    // Egyidejű jelenlévők: érkezés +1, befejezés -1; azonos időpontban előbb a befejezés.
    int cur = 0, mx = 0;
    int a = 0, f = 0;
    while (f < n) {
        if (a < n && arr[a] < fin[f]) {
            ++cur;
            ++a;
            mx = max(mx, cur);
        } else {
            --cur;
            ++f;
        }
    }

    if (bestWait == 0) mx = 0;
    cout << bestId << ' ' << bestWait << '\n' << mx << '\n';
    return 0;
}
