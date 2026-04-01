/*
Feladat: Egynapos munkákat kell határidőre elvégezni, naponta vállalkozónként legfeljebb egy munkával. Minimalizálni kell a vállalkozók számát, és konkrét beosztást is kell adni.
Ötlet: A minimális K vállalkozószám az a legkisebb érték, amelyre minden d napig eső prefixre teljesül: db(határidő <= d) <= K*d. Ebből K = max_d ceil(prefix[d]/d). Ezután a munkákat határidő szerint rendezzük, és sorban kiosztjuk a globális sorszámú slotokra: s=1,2,...; nap=(s-1)/K+1, vállalkozó=(s-1)%K+1. A prefix-korlát miatt minden kiosztott nap <= munka határideje.
Hint 1: || d nap alatt összesen K*d egynapos munka fér be K vállalkozóval. ||
Hint 2: || A szükséges K az összes d-re vett ceil(prefix[d]/d) maximuma. ||
Hint 3: || Ha K fix, akkor határidő szerinti sorrendben a slotok (nap, vállalkozó) kiosztása közvetlenül működik. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Job {
    int h, id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<Job> jobs(N);
    int maxH = 0;
    for (int i = 0; i < N; ++i) {
        cin >> jobs[i].h;
        jobs[i].id = i + 1;
        maxH = max(maxH, jobs[i].h);
    }

    vector<int> cnt(maxH + 1, 0);
    for (const auto& j : jobs) cnt[j.h]++;

    int K = 0;
    int pref = 0;
    for (int d = 1; d <= maxH; ++d) {
        pref += cnt[d];
        K = max(K, (pref + d - 1) / d);
    }

    sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
        if (a.h != b.h) return a.h < b.h;
        return a.id < b.id;
    });

    vector<int> worker(N + 1), day(N + 1);
    for (int s = 1; s <= N; ++s) {
        int idx = s - 1;
        int d = (idx / K) + 1;
        int w = (idx % K) + 1;
        int id = jobs[idx].id;
        worker[id] = w;
        day[id] = d;
    }

    cout << K << '\n';
    for (int id = 1; id <= N; ++id) {
        cout << id << ' ' << worker[id] << ' ' << day[id] << '\n';
    }
    return 0;
}
