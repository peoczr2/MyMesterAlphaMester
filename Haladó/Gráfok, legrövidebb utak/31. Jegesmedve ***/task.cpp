/*
Megoldás lényege:
A hőmérséklet napról napra nő, ezért a medve által elérhető jégtáblák halmaza csak szűkülhet: a kiindulási cellát tartalmazó komponens minden nappal kisebb vagy egyenlő lesz az előzővel. Ha az l-edik napon F hal érhető el, akkor az l-edik nap és a k-adik nap közötti k−l+1 napon összesen legfeljebb F halat lehet enni, mert ezeken a napokon már nem nő az elérhető halak száma. Ezért az első k nap halevése pontosan akkor lehetséges, ha minden l ≤ k napra a [l..k] napok száma nem nagyobb az l-edik napon elérhető halak számánál (Hall-tétel egymásba ágyazott halmazokra). A keresett nap így a min_j (j + F_j) érték, és elég ezt a komponens-változások napjain kiszámolni: az első napon és minden olvadási hőmérséklet + 1 napon. A cellákat a legmelegebbtől a hidegebb felé haladva, unió-kereső (DSU) segítségével egyesítjük, így az idő O(NM log(NM)), ami a 0.3 mp-es korláton belül van.
*/
/*
Hint 1: || Figyeld meg, hogy a hőmérséklet növekedésével a medve elérhető jégtábláinak halmaza csak szűkülhet, így a későbbi napokon a halakból sosem lesz több. ||
Hint 2: || Ha az l-edik napon F hal érhető el, akkor az l-edik naptól a k-adik napig tartó napokon összesen legfeljebb F halat lehet enni, tehát ezt a korlátot kell minden l-re ellenőrizni. ||
Hint 3: || Elég azokat a napokat vizsgálni, amikor a komponens megváltozik (az első nap, és minden olvadási hőmérséklet + 1); a cellákat a legmelegebbtől haladva unió-kereséssel egyesítsd, és a kiindulási cella komponensének halszámát olvasd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> parent_, sizeOf;
vector<long long> fishSum;

int findRoot(int x) {
    while (parent_[x] != x) {
        parent_[x] = parent_[parent_[x]];
        x = parent_[x];
    }
    return x;
}

void unite(int a, int b) {
    a = findRoot(a);
    b = findRoot(b);
    if (a == b) return;
    if (sizeOf[a] < sizeOf[b]) swap(a, b);
    parent_[b] = a;
    sizeOf[a] += sizeOf[b];
    fishSum[a] += fishSum[b];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int total = n * m;
    vector<long long> melt(total), fish(total);
    for (auto &x : melt) cin >> x;
    for (auto &x : fish) cin >> x;

    int bear = -1;
    for (int i = 0; i < total; i++)
        if (melt[i] == -1) bear = i;

    parent_.resize(total);
    iota(parent_.begin(), parent_.end(), 0);
    sizeOf.assign(total, 1);
    fishSum.assign(total, 0);
    for (int i = 0; i < total; i++) fishSum[i] = fish[i];

    // a cellák olvadási hőmérséklet szerint csökkenő sorrendben "járhatóvá" válnak hidegebb napokon át,
    // ezért a melegebbtől a hidegebb felé haladva a járható cellák halmaza csak nő
    vector<int> order;
    for (int i = 0; i < total; i++)
        if (i != bear) order.push_back(i);
    sort(order.begin(), order.end(), [&](int a, int b) { return melt[a] > melt[b]; });

    // a komponens csak a 0 napon (T = 0) és az olvadási hőmérséklet + 1 napokon változik
    vector<long long> temps;
    temps.push_back(0);
    for (int i = 0; i < total; i++)
        if (melt[i] >= 0) temps.push_back(melt[i]);
    sort(temps.begin(), temps.end(), greater<long long>());
    temps.erase(unique(temps.begin(), temps.end()), temps.end());

    vector<char> added(total, 0);
    added[bear] = 1;
    size_t p = 0;
    long long answer = LLONG_MAX;
    for (long long t : temps) {
        // a t hőmérsékleten (ez a t+1-edik nap) járható cellák: olvadási hőmérséklet > t
        while (p < order.size() && melt[order[p]] > t) {
            int c = order[p++];
            added[c] = 1;
            int r = c / m, col = c % m;
            if (r > 0 && added[c - m]) unite(c, c - m);
            if (r + 1 < n && added[c + m]) unite(c, c + m);
            if (col > 0 && added[c - 1]) unite(c, c - 1);
            if (col + 1 < m && added[c + 1]) unite(c, c + 1);
        }
        long long reachableFish = fishSum[findRoot(bear)];
        long long day = t + 1;
        answer = min(answer, day + reachableFish);
    }
    cout << answer << '\n';
    return 0;
}
