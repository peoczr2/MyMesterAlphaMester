/*
Megoldás lényege:
A legnagyobb fátlan téglalap mindegyik oldala vagy a terület szélére esik, vagy egy fa zárja le. Ha a téglalap alját egy fa zárja le, akkor a téglalap alsó sora a fa sora alatt van, és a fa oszlopa a téglalap oszlopai közé esik. Ilyenkor a fák sorait csökkenő sorrendben bejárva, felfelé haladva a horgony oszlopát tartalmazó szabad oszlopintervallum egyre szűkül, és minden lépésben a jelenlegi intervallum és a magasság szorzata egy üres téglalap területe.
A felső határt záró téglalapokat ugyanígy kapjuk, ha a sorok sorrendjét megfordítjuk (a tábla fejjel lefelé fordul) és ugyanazt a bejárást futtatjuk. A teljes magasságú téglalapok területét a fák oszlopai közötti legnagyobb szabad sáv és M szorzata adja.
Az időigény O(K²), ami K ≤ 7000 mellett belefér az időkorlátba.
*/
/*
Hint 1: || Ha a téglalap alját egy fa zárja le, akkor a téglalap alsó széle a fa sora alatt van, és a fa oszlopának a téglalap oszlopai között kell lennie. Mivel K ≤ 7000, fánként egy O(K)-s bejárás már elfér az időkorlátban. ||
Hint 2: || A horgony fától felfelé haladj a fák sorai szerint csökkenő sorrendben, és tartsd nyilván a horgony oszlopának bal és jobb oldalán az eddigi legközelebbi fa oszlopát. Minden fa előtt a jelenlegi oszlopintervallum és a magasság szorzata már egy üres téglalap területe. ||
Hint 3: || Ha egy fa a horgony oszlopában áll, a felfelé haladás véget ér, de a területet ebben a lépésben még számold ki, mielőtt a széleket szűkíted. A felső határt záró téglalapokat a sorok sorrendjének megfordításával, ugyanezzel az eljárással kapod meg. ||
Hint 4: || A teljes magasságú téglalapok területe M · (a fák oszlopai közötti legnagyobb szabad sáv), ezt külön számold ki. A területek akár 10^14-ig is nőhetnek, ezért használj long long típust. ||
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Alsó horgonyos keresés. A fákat (sor, oszlop) párként kapja, sor szerint csökkenő sorrendben.
// Minden i fára a téglalap alsó sora t[i].sor - 1, és a téglalap oszlopai között kell lennie t[i].oszlop-nak.
ll alsoHorgonyosKereses(const vector<pair<ll, ll>> &t, ll N) {
    int k = t.size();

    // startIdx[i]: az első olyan index, ahol a sor kisebb, mint t[i] sora.
    vector<int> startIdx(k);
    for (int i = 0; i < k;) {
        int j = i;
        while (j < k && t[j].first == t[i].first) j++;
        for (int x = i; x < j; x++) startIdx[x] = j;
        i = j;
    }

    ll best = 0;
    for (int i = 0; i < k; i++) {
        ll bottom = t[i].first - 1;
        ll ci = t[i].second;
        if (bottom < 1) continue;

        ll L = 1, R = N;  // a horgony oszlopát tartalmazó szabad oszlopintervallum
        bool blocked = false;
        for (int j = startIdx[i]; j < k; j++) {
            ll rj = t[j].first, cj = t[j].second;
            // Téglalap: sorok (rj, bottom], oszlopok [L, R].
            best = max(best, (bottom - rj) * (R - L + 1));
            if (cj == ci) {
                blocked = true;
                break;
            }
            if (cj < ci) {
                if (cj >= L) L = cj + 1;
            } else {
                if (cj <= R) R = cj - 1;
            }
        }
        if (!blocked) best = max(best, bottom * (R - L + 1));
    }
    return best;
}

int main() {
    ll M, N;
    int K;
    cin >> M >> N >> K;

    vector<pair<ll, ll>> tr(K);
    for (auto &p : tr) cin >> p.first >> p.second;

    auto byRowDesc = [](const pair<ll, ll> &x, const pair<ll, ll> &y) { return x.first > y.first; };

    sort(tr.begin(), tr.end(), byRowDesc);
    ll best = alsoHorgonyosKereses(tr, N);

    // A sorok megfordítása (fejjel lefelé fordítás): a felső horgonyos téglalapok így alsóként kerülnek elő.
    vector<pair<ll, ll>> flipped(K);
    for (int i = 0; i < K; i++) flipped[i] = {M + 1 - tr[i].first, tr[i].second};
    sort(flipped.begin(), flipped.end(), byRowDesc);
    best = max(best, alsoHorgonyosKereses(flipped, N));

    // Teljes magasságú téglalapok: a fák oszlopai közötti legnagyobb szabad sáv.
    vector<ll> cols;
    for (auto &p : tr) cols.push_back(p.second);
    sort(cols.begin(), cols.end());
    cols.erase(unique(cols.begin(), cols.end()), cols.end());
    ll prevCol = 0, gap = 0;
    for (ll c : cols) {
        gap = max(gap, c - prevCol - 1);
        prevCol = c;
    }
    gap = max(gap, N + 1 - prevCol - 1);
    best = max(best, M * gap);

    cout << best << "\n";
    return 0;
}
