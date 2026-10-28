/*
Megoldás lényege:
A munkák határidő szerint vannak sorban, ezért egy kiválasztott részhalmaz akkor ütemezhető, ha a sorrendben vett
végrehajtási idők összege minden kiválasztott munkánál nem nagyobb annak határidejénél.
Állapotnak tekintjük az eddig kiválasztott munkák (T, P) párját: T az összidő, P az elért haszon. Az (T, P) állapotot
dominálja az (T', P'), ha T' <= T és P' >= P, mert onnan minden további munka ugyanúgy beilleszthető. Ezért minden lépésben
csak a Pareto-optimális állapotokat tartjuk meg: T szerint növekvő sorrendben, a haszon szigorúan nő.
Új munkánál a meglévő állapotokból (T + t, P + h) állapot képezhető, ha T + t <= határidő; a két rendezett listát
összefésüljük, és a dominált állapotokat kiszűrjük. A kiválasztott munkák halmazát 64 bites maszkban tároljuk (N <= 50),
így a végén visszaadható az ütemezés. Mintán és véletlen adatokon az állapotok száma kicsi, az idő gyakorlatilag nulla.
*/
/*
Hint 1: || Ha a munkák határidő szerint vannak rendezve, elég azt ellenőrizni, hogy a kiválasztott munkák végrehajtási idejének összege minden határidőnél beleférjen. ||
Hint 2: || Egy állapot az eddigi összidő és haszon párja; ha valamelyik állapotnál ugyanannyi vagy kisebb idő alatt ugyanannyi vagy több haszon van, a rosszabb állapot nem kell tovább vinni. ||
Hint 3: || Az N <= 50 miatt a kiválasztott munkák egy 64 bites maszkban is elférnek, így az ütemezés visszaadása egyszerű. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct State {
    long long time;
    long long profit;
    unsigned long long mask;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> deadline(n), duration(n), gain(n);
    for (auto &x : deadline) cin >> x;
    for (auto &x : duration) cin >> x;
    for (auto &x : gain) cin >> x;

    vector<State> cur{{0, 0, 0ULL}};

    for (int j = 0; j < n; ++j) {
        vector<State> cand;
        cand.reserve(cur.size());
        for (const State &s : cur) {
            long long finish = s.time + duration[j];
            if (finish <= deadline[j]) {
                cand.push_back({finish, s.profit + gain[j], s.mask | (1ULL << j)});
            }
        }

        // Mindkét lista T szerint rendezett; egyenlő T-nél a nagyobb hasznot vesszük előre.
        vector<State> merged;
        merged.reserve(cur.size() + cand.size());
        size_t a = 0, b = 0;
        long long bestProfit = -1;
        while (a < cur.size() || b < cand.size()) {
            State x;
            bool takeCur = b >= cand.size() ||
                           (a < cur.size() && (cur[a].time < cand[b].time ||
                                               (cur[a].time == cand[b].time && cur[a].profit >= cand[b].profit)));
            if (takeCur) {
                x = cur[a++];
            } else {
                x = cand[b++];
            }
            if (x.profit > bestProfit) {
                merged.push_back(x);
                bestProfit = x.profit;
            }
        }
        cur.swap(merged);
    }

    // A haszon szerint rendezett Pareto-lista utolsó eleme a legjobb.
    State best = cur.back();

    vector<int> chosen;
    for (int j = 0; j < n; ++j) {
        if (best.mask >> j & 1ULL) {
            chosen.push_back(j + 1);
        }
    }

    cout << best.profit << "\n";
    cout << chosen.size() << "\n";
    for (size_t i = 0; i < chosen.size(); ++i) {
        if (i) cout << ' ';
        cout << chosen[i];
    }
    cout << "\n";
    return 0;
}
