/*
Megoldás lényege:
Mivel a feldolgozás a lehető leghamarabb történik, minden nap a kapacitást (K kg) teljesen kihasználjuk, az utolsó nap kivételével.
Így a napok száma M = ceil(összes mennyiség / K), és az egyes napok mennyisége is rögzített.
Az árengedmény miatt a d. napon (1-től számolva) vett 1 kg ára: ár - F * (d - 1), ami minden termelőre azonos mértékű csökkenés,
ezért a költség csak a napi mennyiségektől függ, és az, hogy melyik termelőtől veszünk, nem változtatja meg.
A termelőket ezért ár szerint növekvő sorrendbe rakjuk (egyenlő áraknál a kisebb sorszám előre), és a napokat sorban, kapacitásig töltjük.
A költséget 64 bites egészekkel számoljuk, és a napi bontást a feladat formátumában írjuk ki. Időigény: O(N log N + M).
*/
/*
Hint 1: || Minden nap a lehető legtöbb málnát kell feldolgozni, így a napok száma és a napi mennyiségek már előre adottak. Csak azt kell eldönteni, melyik termelőtől melyik napon veszel. ||
Hint 2: || Egy napon minden termelő ára ugyanannyival csökken, így a költség a napi mennyiségektől függ, nem attól, kitől veszed. A d. napon vett 1 kg ára ár - F * (d - 1). ||
Hint 3: || Rendezd a termelőket ár szerint növekvően, majd töltsd a napokat egymás után, mindig a sorban következő termelőtől véve, amíg a nap kapacitása el nem fogy. Egyenlő áraknál a kisebb sorszám legyen előbb. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long K, N, F;
    cin >> K >> N >> F;
    vector<long long> q(N + 1), ar(N + 1);
    for (int i = 1; i <= N; i++) cin >> q[i] >> ar[i];

    // Olcsóbbtól a drágábbig; egyenlő áraknál a kisebb sorszám megy előre.
    vector<int> order(N);
    iota(order.begin(), order.end(), 1);
    stable_sort(order.begin(), order.end(), [&](int a, int b) { return ar[a] < ar[b]; });

    vector<vector<pair<int, long long>>> plan(1);   // plan[nap] = (termelő, mennyiség) párok
    long long cap = K, cost = 0;
    int day = 0;                                    // 0-tól számolva
    for (int p : order) {
        long long r = q[p];
        while (r > 0) {
            if (cap == 0) {
                plan.push_back({});
                cap = K;
                day++;
            }
            long long take = min(r, cap);
            plan[day].push_back({p, take});
            cost += take * (ar[p] - F * day);   // a day. napon (0-tól) F-fel olcsóbb
            r -= take;
            cap -= take;
        }
    }

    cout << plan.size() << " " << cost << "\n";
    for (auto &d : plan) {
        bool first = true;
        for (auto [p, x] : d) {
            if (!first) cout << " ";
            cout << p << " " << x;
            first = false;
        }
        cout << "\n";
    }
    return 0;
}
