/*
Megoldás lényege:
Eseményvezérelt szimulációt futtatunk. Minden vonat következő szakaszra való indulási kérését egy prioritási sorba tesszük, a sor a kérési idő szerint rendezett, egyenlőség esetén a Kukutyin felől induló vonat áll előbb. Egy szakasz V vágánnyal legfeljebb V vonatot enged egyszerre, és egy vonat T percig foglalja. A szakaszon a már lefoglalt kezdési időpontokból egy lineáris bejárással megkeressük a legkorábbi kérés utáni olyan indulási időt, amely nem ütközik a foglalásokkal. Köztes állomáson a vonat érkezése után legalább Perc percet vár, és a következő kérés ettől az időponttól kerül a sorba. A kiírás érkezési idő szerint rendezett, egyenlőségnél a Piripócsra érkező vonat áll előbb.
*/
/*
Hint 1: || Ne léptesd az időt percenként. Elég a kéréseket időrendben feldolgozni, mert egy vonat következő kérése mindig későbbi, mint az előző. ||
Hint 2: || Egy szakasz foglaltságát a már ráeső indulási időpontok adják: egy vonat [t, t+T) intervallumon foglal. Egy vágánynál a legkorábbi szabad t az, amelynél nincs átfedés egyetlen korábbi foglalással sem. ||
Hint 3: || Két vágánynál a telített tartományok a rendezett indulási időpontok i. és (i+1). elemei között keletkeznek. A t kezdési időt úgy toltad előre, hogy az ilyen tartományok végét átugorod, és így nem ütközöl. ||
*/
#include <bits/stdc++.h>
using namespace std;

// s: a szakaszon már foglalt kezdési időpontok (rendezve), L: a szakasz bejárási ideje,
// c: a vágányok száma, r: a legkorábbi kérési idő. Visszaadja a legkorábbi szabad kezdést.
long long placeTrain(const vector<long long>& s, long long L, int c, long long r) {
    long long t = r;
    int k = (int)s.size();
    // Az r - L-nél nem későbbi kezdések tartományai már véget értek, ezeket kihagyjuk
    int i0 = (int)(upper_bound(s.begin(), s.end(), r - L) - s.begin());
    for (int i = i0; i + c - 1 < k; i++) {
        long long a = s[i + c - 1];  // innentől c vonat fut egyszerre
        long long b = s[i] + L;      // eddig tart a c-szeres lefedettség
        if (a >= t + L) break;
        if (a >= b) continue;
        if (t < b) t = b;
    }
    return t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m1, m2, perc;
    cin >> n >> m1 >> m2 >> perc;
    vector<long long> len(n + 1, 0);
    for (int i = 1; i <= n - 1; i++) cin >> len[i];
    vector<int> cap(n + 1, 1);
    for (int i = 1; i <= n - 1; i++) cin >> cap[i];

    int total = m1 + m2;
    vector<int> pos(total), dir(total);
    // (kérési idő, irány: 0 = Kukutyin felől, 1 = Piripócs felől, vonat azonosító)
    priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<>> pq;
    for (int i = 0; i < m1; i++) {
        long long d;
        cin >> d;
        pos[i] = 1;
        dir[i] = 1;
        pq.emplace(d, 0, i);
    }
    for (int i = 0; i < m2; i++) {
        long long d;
        cin >> d;
        int id = m1 + i;
        pos[id] = n;
        dir[id] = -1;
        pq.emplace(d, 1, id);
    }

    vector<vector<long long>> starts(n + 1);
    vector<pair<long long, int>> arrivals;  // (érkezési idő, végállomás)
    arrivals.reserve(total);

    while (!pq.empty()) {
        auto [r, dp, id] = pq.top();
        pq.pop();
        int seg = (dir[id] == 1) ? pos[id] : pos[id] - 1;
        int nxt = pos[id] + dir[id];
        long long L = len[seg];
        long long e = placeTrain(starts[seg], L, cap[seg], r);
        auto it = upper_bound(starts[seg].begin(), starts[seg].end(), e);
        starts[seg].insert(it, e);
        long long arr = e + L;
        pos[id] = nxt;
        if (nxt == 1 || nxt == n) {
            arrivals.push_back({arr, nxt});
        } else {
            pq.emplace(arr + perc, dp, id);
        }
    }

    sort(arrivals.begin(), arrivals.end(), [](const pair<long long, int>& x, const pair<long long, int>& y) {
        if (x.first != y.first) return x.first < y.first;
        return x.second > y.second;  // egyenlő időben a Piripócsra érkező előbb
    });
    for (auto& [tm, st] : arrivals) {
        cout << (st == 1 ? 1 : 2) << ' ' << tm << '\n';
    }
    return 0;
}
