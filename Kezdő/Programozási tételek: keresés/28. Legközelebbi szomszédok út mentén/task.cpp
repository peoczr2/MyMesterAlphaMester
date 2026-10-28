/*
Megoldás lényege:
A települések pozíciói növekvő sorrendben vannak, ezért minden település K legközelebbi szomszédja egy K+1 hosszú, őt tartalmazó összefüggő indexszakaszt alkot. Egy [l, l+K] szakasz költsége az aktuális településtől a két szélső elemig mért nagyobbik távolság, és l növelésével ez először csökken, majd nő. A minimális költségű l-t bináris kereséssel keressük meg: az első olyan l-nél, ahol a jobboldali távolság nem kisebb a baloldalinál, a kettő közül a jelölt-párt vizsgáljuk. Egyenlő költségnél a kisebb l, vagyis a baloldalibb szakasz nyer. A kiírt érték a szakasz két szélső sorszáma az aktuális település nélkül, az időigény O(N log N).
*/
/*
Hint 1: || A települések egy egyenes mentén vannak, ezért a legközelebbi szomszédok halmaza mindig egy összefüggő sorozatrész lesz, amely tartalmazza az aktuális települést. ||
Hint 2: || Egy K+1 hosszú szakasz költsége az aktuális településtől a két szélső elemig mért távolságok maximuma. Ez a kezdőindex növelésével előbb csökken, majd nő. ||
Hint 3: || A jó kezdőindexet bináris kereséssel találod meg: keresd azt az első l értéket, ahol a jobboldali távolság már nem kisebb a baloldalinál. A két környező jelölt közül a kisebb költségűt válaszd, egyenlőségnél a kisebb indexűt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<long long> t(n);
    for (auto &x : t) cin >> x;

    for (int i = 0; i < n; i++) {
        // Az l kezdőindex lehetséges tartománya: [l, l+k] tartalmazza i-t
        int lo = max(0, i - k), hi = min(i, n - 1 - k);

        // Első l a tartományban, ahol a jobboldali távolság nem kisebb a baloldalinál
        int a = lo, b = hi + 1;
        while (a < b) {
            int mid = (a + b) / 2;
            if (t[mid + k] - t[i] >= t[i] - t[mid]) b = mid;
            else a = mid + 1;
        }

        // A két jelölt közül a kisebb költségű; egyenlőségnél a kisebb l (előbb vizsgált) nyer
        int best = -1;
        long long bestCost = LLONG_MAX;
        for (int l : {a - 1, a}) {
            if (l < lo || l > hi) continue;
            long long cost = max(t[i] - t[l], t[l + k] - t[i]);
            if (cost < bestCost) {
                bestCost = cost;
                best = l;
            }
        }

        // A szakasz szélei az i-edik település nélkül
        int r = best + k;
        int first = (best == i) ? best + 1 : best;
        int last = (r == i) ? r - 1 : r;
        cout << first + 1 << ' ' << last + 1 << '\n';
    }
    return 0;
}
