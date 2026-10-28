/*
Megoldás lényege: Klasszikus intervallum-ütemezés: a munkákat befejezési idő szerint növekvően rendezzük, és mindig a legkorábban befejeződő, még elvállalható munkát vesszük. Mivel a kezdés és a befejezés napja zárt intervallumot ad, egy munka akkor fér be, ha kezdése nagyobb az utoljára kiválasztott munka befejezésénél. A korábban záródó munka mindig legalább annyi lehetőséget hagy a többinek, mint bármelyik másik választás (csereargumentum), ezért a mohó megoldás optimális. Időigény: O(N log N).
*/
/*
Hint 1: || Ha minél több intervallumot akarsz kiválasztani, érdemes minél korábban „felszabadítani” az idővonalat. ||
Hint 2: || Rendezd a munkákat befejezési idő szerint, és mohón válogass. ||
Hint 3: || Zárt intervallumnál a feltétel: új_kezdés > utolsó_befejezés. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Job {
    int s, e, id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<Job> a(N);
    for (int i = 0; i < N; ++i) {
        cin >> a[i].s >> a[i].e;
        a[i].id = i + 1;
    }

    sort(a.begin(), a.end(), [](const Job& x, const Job& y) {
        if (x.e != y.e) return x.e < y.e;
        if (x.s != y.s) return x.s < y.s;
        return x.id < y.id;
    });

    vector<int> chosen;
    int lastEnd = 0;
    for (const auto& j : a) {
        if (j.s > lastEnd) {
            chosen.push_back(j.id);
            lastEnd = j.e;
        }
    }

    cout << chosen.size() << '\n';
    for (int i = 0; i < (int)chosen.size(); ++i) {
        if (i) cout << ' ';
        cout << chosen[i];
    }
    cout << '\n';
    return 0;
}
