/*
Megoldás lényege:
Az ügyfelek a bemenetben már érkezési sorrendben vannak, ezért őket egyesével, ebben a sorrendben szimuláljuk. Egy ügyfél a legkorábbi olyan időpontban kezdi az ügyét, amikor már megérkezett, az előtte álló ügyfél már sorra került, és van szabad pult; ekkor a legkisebb sorszámú szabad pultot választja. A foglalt pultok felszabadulási idejét prioritásos sorban (min-heap) tartjuk, a szabad pultok sorszámait rendezett halmazban, így a legközelebbi szabad pult gyorsan megtalálható. A munkanap végét a legnagyobb befejezési idő, a legnagyobb várakozást a kezdési és érkezési idő különbségének maximuma adja. A váróteremben egyszerre lévők száma egy t időpontban a t-ig érkezettek és a t-ig már sorra kerültek számának különbsége; mivel mindkét sorozat nemcsökkenő, ez kétmutatós bejárással végigvehető. Az időigény O(N log M).
*/
/*
Hint 1: || Az ügyfelek már érkezési sorrendben vannak, így a sor egy FIFO: minden ügyfél csak az előtte álló után kezdhet, ezért a kezdési idők nem csökkenhetnek. Elég egyesével, sorban szimulálni. ||
Hint 2: || Tartsd nyilván a foglalt pultok felszabadulási idejét egy prioritásos sorban, a szabad pultok sorszámait pedig külön halmazban. Egy ügyfél kezdési ideje az érkezési idő, az előző kezdési idő és az első felszabadulás közül a legnagyobb, és ekkor a legkisebb sorszámú szabad pultot kapja. ||
Hint 3: || A váróteremben lévők száma egy t időpontban: hányan érkeztek legkésőbb t-ig, mínusz hányan kezdték meg az ügyüket legkésőbb t-ig. Mivel a kezdési idők is növekvők, az érkezési időpontokon egy kétmutatós bejárással az összes eset megvizsgálható. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n;  // m: a kiszolgálópultok száma, n: az ügyfelek száma
    cin >> m >> n;
    vector<long long> arrive(n), dur(n), start(n);
    for (int i = 0; i < n; i++) cin >> arrive[i] >> dur[i];

    vector<int> serving(n);  // az adott ügyfelet kiszolgáló pult sorszáma
    set<int> freeCounters;   // szabad pultok; a legkisebb sorszám a legközelebbi
    for (int p = 1; p <= m; p++) freeCounters.insert(p);
    // foglalt pultok: (felszabadulás ideje, pult sorszáma)
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> busy;

    long long prevStart = 0;
    for (int i = 0; i < n; i++) {
        long long t = max(arrive[i], prevStart);
        while (!busy.empty() && busy.top().first <= t) {
            freeCounters.insert(busy.top().second);
            busy.pop();
        }
        if (freeCounters.empty()) {
            // egyik pult sem szabad: a legkorábbi felszabadulásig várakozik
            t = busy.top().first;
            while (!busy.empty() && busy.top().first <= t) {
                freeCounters.insert(busy.top().second);
                busy.pop();
            }
        }
        int p = *freeCounters.begin();
        freeCounters.erase(freeCounters.begin());
        start[i] = t;
        serving[i] = p;
        busy.push({t + dur[i], p});
        prevStart = t;
    }

    long long endTime = 0, maxWait = 0;
    for (int i = 0; i < n; i++) {
        endTime = max(endTime, start[i] + dur[i]);
        maxWait = max(maxWait, start[i] - arrive[i]);
    }

    // a váróteremben egyszerre lévők maximuma: érkezettek száma - már sorra kerültek száma
    long long maxInside = 0;
    int ptr = 0;
    for (int j = 0; j < n; j++) {
        while (ptr < n && start[ptr] <= arrive[j]) ptr++;
        maxInside = max(maxInside, (long long)(j + 1) - ptr);
    }

    cout << endTime << " " << maxWait << " " << maxInside << "\n";
    for (int i = 0; i < n; i++) cout << serving[i] << "\n";
    return 0;
}
