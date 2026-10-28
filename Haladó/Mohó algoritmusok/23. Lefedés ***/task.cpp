/*
Megoldás lényege: rendezés és duplikátumok törlése után egy csoport költsége a szélső pontok távolsága, egypontos csoportnál 1 (mert a<b). A teljes összhossz így: az összes távolság, mínusz az elvágott rések mérete, plusz az egypontos csoportok száma. Egy rés elvágása a rés méretével csökkenti a hosszt, de ha a rés egyik vagy mindkét szomszédja is el van vágva (a határ is elvágottnak számít), a keletkező egypontos csoport 1-et ér, ezért a rés nettó nyeresége g - (elvágott szomszédok száma). Mohón mindig a legnagyobb pozitív nyereségű rést vágjuk el, legfeljebb K-1-et; a nyereségek csak csökkenhetnek, ezért lusta frissítésű kupaccal az időigény O(N log N).
*/
/*
Hint 1: || Rendezés és duplikátumok törlése után a lefedés szomszédos pontok csoportjaira bontás: egy csoport költsége a szélső pontok távolsága, egypontos csoportnál 1. ||
Hint 2: || Egy rés elvágása a teljes hosszt a rés méretével csökkenti, de a szomszédos elvágások miatt keletkező egypontos csoportok 1-et adnak vissza. ||
Hint 3: || Mindig a legnagyobb pozitív nyereségű rést vágd el, legfeljebb K-1 darabot; a nyereség a szomszédos rések elvágásával csak csökkenhet. ||
Hint 4: || A nyereségeket kupacban tartsd, és kiemelés után számold újra az értéket; ha közben csökkent, visszatéve folytasd. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    vector<long long> v(N);
    for (auto& x : v) cin >> x;
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    int U = (int)v.size();
    int G = U - 1;  // rések száma: gap i a v[i] és v[i+1] között

    vector<char> cut(max(G, 0), 0);
    auto gap = [&](int i) { return v[i + 1] - v[i]; };
    auto delta = [&](int i) {
        long long d = gap(i);
        if (i == 0 || cut[i - 1]) d -= 1;
        if (i == G - 1 || cut[i + 1]) d -= 1;
        return d;
    };

    priority_queue<pair<long long, int>> pq;  // (nyereség, -index)
    for (int i = 0; i < G; ++i) {
        long long d = delta(i);
        if (d > 0) pq.push({d, -i});
    }
    int cuts = 0;
    while (cuts < K - 1 && !pq.empty()) {
        auto [key, negi] = pq.top();
        pq.pop();
        int i = -negi;
        if (cut[i]) continue;
        long long cur = delta(i);
        if (cur <= 0) continue;
        if (cur != key) {
            pq.push({cur, -i});
            continue;
        }
        cut[i] = 1;
        ++cuts;
    }

    long long total = 0;
    vector<pair<long long, long long>> segs;
    int l = 0;
    for (int i = 0; i < U; ++i) {
        if (i == U - 1 || cut[i]) {
            long long a, b;
            if (l == i) {
                a = v[l];
                b = v[l] + 1;
            } else {
                a = v[l];
                b = v[i];
            }
            segs.push_back({a, b});
            total += b - a;
            l = i + 1;
        }
    }

    cout << total << '\n';
    for (auto [a, b] : segs) cout << a << ' ' << b << '\n';
    return 0;
}
