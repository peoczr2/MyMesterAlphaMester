/*
Megoldás lényege:
A munkákat határidő szerint növekvő sorrendben dolgozzuk fel, és közben egy halmazban tartjuk azokat
a munkákat, amelyek egymás után elvégezve mind határidőre készülnek. Új munka felvételekor az összidő nő;
ha ez meghaladja az aktuális munka határidejét, a halmazból a legidőigényesebb munkát kivesszük, mert
így a megmaradók összideje a legkisebb. A kivétel mindig egyetlen munkát jelent, és a legnagyobb elem
gyors megtalálására prioritásos sort (max-heap) használunk. A végső sorrend a határidő szerinti sorrend
a megmaradt munkákra, így minden kiválasztott munka időben elkészül. Az időigény O(N log N).
*/
/*
Hint 1: || Rendezd a munkákat határidő szerint növekvően, és ebben a sorrendben dolgozd fel őket. Ha az eddig felvett munkák összideje nem fér bele az aktuális határidőbe, valamelyik munkát ki kell hagyni. ||
Hint 2: || Melyik munkát érdemes kihagyni? Azt, amelyik a legtöbb időt veszi igénybe, így a megmaradó munkák összideje a legkisebb lesz. A legnagyobb időigényű munkát egy prioritásos sorban (max-heap) gyorsan megtalálod. ||
Hint 3: || Minden felvétel után elég egyszer ellenőrizni, és legfeljebb egy munkát kell kivenni. A végén a meg nem jelölt munkák sorszámait a határidő szerinti sorrendben írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> dur(n), dl(n);
    for (int i = 0; i < n; i++) {
        cin >> dur[i] >> dl[i];
    }

    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    stable_sort(order.begin(), order.end(), [&](int a, int b) { return dl[a] < dl[b]; });

    vector<bool> removed(n, false);
    priority_queue<pair<int, int>> heap; // (időigény, pozíció a határidő szerinti sorban)
    long long total = 0;

    for (int pos = 0; pos < n; pos++) {
        int job = order[pos];
        heap.push({dur[job], pos});
        total += dur[job];
        if (total > dl[job]) {
            auto top = heap.top();
            heap.pop();
            total -= top.first;
            removed[top.second] = true;
        }
    }

    vector<int> chosen;
    for (int pos = 0; pos < n; pos++) {
        if (!removed[pos]) {
            chosen.push_back(order[pos] + 1);
        }
    }

    cout << chosen.size() << '\n';
    for (size_t i = 0; i < chosen.size(); i++) {
        if (i > 0) cout << ' ';
        cout << chosen[i];
    }
    cout << '\n';
    return 0;
}
