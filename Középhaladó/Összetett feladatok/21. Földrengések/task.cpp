/*
Megoldás lényege:
Az évenkénti földrengések számát tömbben tároljuk, és prefixösszegeket készítünk, így bármely E éves ablak földrengésszáma azonnal megkapható. Az 1., 2. és 3. részfeladat a volt-e földrengés jelölő tömbből egy bejárással számítható (a futamok hossza, illetve a szomszédos párok száma). A 4. részfeladatban minden földrengést külön vizsgálunk az időrendi bemeneten: az előző és a következő földrengés közti időtartamot hasonlítjuk össze, a bemenet első és utolsó eseménye kimarad. Az 5. részfeladatban az E éves ablak kezdőéve földrengés-év lehet, a legtöbb földrengést tartalmazó ablakok közül a régebbit választjuk. Az időigény O(N + H).
*/
/*
Hint 1: || Vegyél egy jelölő tömböt a H évre: has[év] = 1, ha volt földrengés abban az évben. Az 1–3. részfeladat ezekből a jelölésekből a nem üres, illetve üres egymást követő évek futamainak hosszaként adódik. ||
Hint 2: || A 4. részfeladatban a sorrend számít: a bemenet időrendi, így minden belső i-edik földrengésnél a T[i - 1], T[i], T[i + 1] értékekből a két szomszédos időköz hasonlítható össze, az első és az utolsó esemény pedig kimarad. ||
Hint 3: || Az 5. részfeladatban az E éves ablak földrengésszáma prefixösszegből adódik: a [s - E + 1, s] ablakban pre[s] - pre[s - E] földrengés van. A kezdőévet csak olyan s évek közül válaszd, ahol volt földrengés, és döntetlennél a régebbi, azaz a nagyobb s legyen az eredmény. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, h, e;
    cin >> n >> h >> e;
    vector<int> t(n);
    for (int i = 0; i < n; i++) cin >> t[i];

    vector<int> has(h + 2, 0), cnt(h + 2, 0), pre(h + 2, 0);
    for (int x : t) {
        has[x] = 1;
        cnt[x]++;
    }
    for (int y = 1; y <= h; y++) pre[y] = pre[y - 1] + cnt[y];

    // 1. részfeladat: a leghosszabb egymást követő év, amikor nem volt földrengés
    int best = 0, cur = 0;
    for (int y = 1; y <= h; y++) {
        if (!has[y]) {
            cur++;
            best = max(best, cur);
        } else {
            cur = 0;
        }
    }
    cout << "#\n" << best << "\n";

    // 2. részfeladat: azon évek száma, amelyeket a következő évben is volt földrengés
    int pairs = 0;
    for (int y = 2; y <= h; y++)
        if (has[y] && has[y - 1]) pairs++;
    cout << "#\n" << pairs << "\n";

    // 3. részfeladat: a leghosszabb időszak, amikor minden évben volt földrengés
    best = 0;
    cur = 0;
    for (int y = 1; y <= h; y++) {
        if (has[y]) {
            cur++;
            best = max(best, cur);
        } else {
            cur = 0;
        }
    }
    cout << "#\n" << best << "\n";

    // 4. részfeladat: azok a földrengések, amelyek után kevesebb idő telt el a következőig,
    // mint amennyi az őket megelőző és az ők közti idő volt (időrendben)
    vector<int> res;
    for (int i = 1; i + 1 < n; i++)
        if (t[i] - t[i + 1] < t[i - 1] - t[i]) res.push_back(t[i]);
    cout << "#\n" << res.size();
    for (int x : res) cout << ' ' << x;
    cout << "\n";

    // 5. részfeladat: az E éves időszak kezdete (régebbi a döntetlennél), és a benne levő földrengések száma
    int bestStart = 0, bestCnt = -1;
    for (int s = h; s >= 1; s--) {
        if (!has[s]) continue;
        int lo = max(0, s - e);
        int c = pre[s] - pre[lo];
        if (c > bestCnt) {
            bestCnt = c;
            bestStart = s;
        }
    }
    cout << "#\n" << bestStart << "\n" << bestCnt << "\n";
    return 0;
}
