/*
Megoldás lényege:
Két menetben dolgozunk. Először az indulási idő szerint növekvő sorrendben haladunk a vonatokon: az 1. állomásról bármikor
indulhatunk, egy másik állomáson pedig akkor szállhatunk fel, ha az ott elérhető legkorábbi érkezési idő kisebb a vonat
indulási idejénél. Így megkapjuk a célállomásra érkezés legkorábbi idejét (T). Másodszor az indulási idő szerint csökkenő
sorrendben haladunk visszafelé: egy vonat akkor "jó", ha a célállomásra pontosan T-kor ér, vagy később induló jó vonatra
tud átszállni az érkezése után. Minden állomáson a legnagyobb jó indulási időt tároljuk, így egy vonat ellenőrzése
konstans idejű. A válasz az 1. állomásról induló jó vonatok legnagyobb indulási ideje. Az időigény O(M log M).
*/
/*
Hint 1: || Az időpontokat két irányban érdemes bejárni: előre, hogy megtudd a célállomásra érkezés legkorábbi idejét, majd
visszafelé, hogy megtudd, mikor kell legkésőbb elindulni ahhoz, hogy ez az idő még elérhető legyen. ||
Hint 2: || Átszálláskor az érkezés szigorúan kisebb legyen a következő vonat indulásánál, ezért a vonatokat indulási idő szerint
rendezd. Visszafelé haladva minden állomásra tárold a legnagyobb olyan indulási időt, amellyel onnan jó vonat indul. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Train {
    int from, to, dep, arr;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Train> trains(m);
    for (Train& t : trains) {
        cin >> t.from >> t.to >> t.dep >> t.arr;
    }

    // A vonatok indulási idő szerint növekvő sorrendben.
    vector<int> order(m);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) { return trains[a].dep < trains[b].dep; });

    // Előre: az egyes állomásokra érkezés legkorábbi ideje.
    const int INF = INT_MAX;
    vector<int> earliest(n + 1, INF);
    earliest[1] = 0;  // az 1. állomásról bármikor indulhatunk
    for (int i : order) {
        const Train& t = trains[i];
        if (earliest[t.from] < t.dep) {
            earliest[t.to] = min(earliest[t.to], t.arr);
        }
    }

    if (earliest[n] == INF) {
        cout << -1 << '\n';
        return 0;
    }
    const int best = earliest[n];

    // Hátra: latestGood[s] az s állomásról induló jó vonatok legnagyobb indulási ideje (-1, ha nincs ilyen).
    vector<int> latestGood(n + 1, -1);
    int answer = -1;
    for (auto it = order.rbegin(); it != order.rend(); ++it) {
        const Train& t = trains[*it];
        bool good = (t.to == n) ? (t.arr == best) : (latestGood[t.to] > t.arr);
        if (good) {
            latestGood[t.from] = max(latestGood[t.from], t.dep);
            if (t.from == 1) {
                answer = max(answer, t.dep);
            }
        }
    }

    cout << best << '\n' << answer << '\n';
    return 0;
}
