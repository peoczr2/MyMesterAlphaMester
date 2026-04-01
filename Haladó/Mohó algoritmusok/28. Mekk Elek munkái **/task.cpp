/*
Feladat: A lehető legtöbb munkát kell kiválasztani úgy, hogy egyszerre csak egyen lehessen dolgozni.
Ötlet: Klasszikus intervallum-ütemezés: a munkákat befejezési idő szerint rendezzük, és mindig a leghamarabb befejeződő, még vállalható munkát választjuk. Mivel a kezdés-befejezés napok zárt intervallumot jelentenek, két munka csak akkor fér meg egymás után, ha az új munka kezdése nagyobb, mint az előző kiválasztott befejezése.
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
