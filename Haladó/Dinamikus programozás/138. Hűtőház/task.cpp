/*
Megoldasi otlet:
Az allapot nem irhato le pusztan azzal, hogy az elso i termeket milyen batch-ekre bontottuk,
mert ugyanaz az ossz-fagyasztasi ido kulonbozo valos idoallasokhoz vezethet, es ez befolyasolja,
hogy a kovetkezo termek meg belefer-e a sajat hataridejebe. Ezert dinamikus programozast vegzunk
prefixekre es aktualis idokesesre.

Legyen dp[i][d] a minimalis osszes futasi ido, amikor az elso i termek mar le van fagyasztva, es a
kovetkezo termeket legkorabban E[i] + d idopontban tudjuk elkezdeni. Itt d csak 0..V lehet, mert ha a
kovetkezo termek kezdese mar E[i] + V utanra csuszik, az az allapot eleve ervenytelen. Egy allapotbol
egy uj batch-et inditunk az i-edik termekkel. Ha a batch az i..r szakaszt tartalmazza, akkor a batch
ideje M = max(Mi..Mr), az osszsuly nem lehet nagyobb K-nal, es a batch legkorabbi ervenyes inditasa
max(E[i] + d, E[r] - M). Ha ez az ido legfeljebb E[i] + V, akkor a batch pontosan megvalosithato,
vege pedig start + M. Innen a kovetkezo allapot deltaja a kovetkezo erkezeshez viszonyitott csuszas.

Az allapotok kozul eleg csak a Pareto-optimalisakat tovabbvinni: ha ugyanahhoz a prefixhez egy kisebb
vagy azonos csuszassal mar nem nagyobb koltseggel el tudunk jutni, akkor a kesobbi allapot soha nem
lehet jobb. Ezzel a V <= 100 korlat miatt prefixenkent legfeljebb 101 deltaval dolgozunk.
*/
/*
Hint 1: || Egy batch nem csak egy szakaszkoltseg: az is szamit, hogy a batch utan a valos idoben mikor vegzunk. ||
Hint 2: || Az i..r batch legkorabbi ervenyes inditasa max(aktualis ido, E[r] - batch_ido). ||
Hint 3: || A kovetkezo allapothoz nem abszolut idot, hanem a kovetkezo termek erkezesehez kepesti csuszast eleg tarolni. ||
*/
#include <algorithm>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, v;
    cin >> n >> k >> v;

    vector<int> e(n), s(n), m(n);
    for (int i = 0; i < n; ++i) {
        cin >> e[i] >> s[i] >> m[i];
    }

    const int inf = numeric_limits<int>::max() / 4;
    const int width = v + 1;
    vector<int> dp((n + 1) * width, inf);

    auto cell = [&](int index, int delta) -> int& {
        return dp[index * width + delta];
    };

    cell(0, 0) = 0;
    int best_answer = inf;
    int max_prefix = 0;

    for (int i = 0; i < n; ++i) {
        vector<pair<int, int>> frontier;
        int best_cost = inf;
        for (int delta = 0; delta <= v; ++delta) {
            int value = cell(i, delta);
            if (value < best_cost) {
                frontier.push_back({delta, value});
                best_cost = value;
            }
        }

        if (frontier.empty()) {
            continue;
        }

        const int latest_start = e[i] + v;
        const int latest_reachable_arrival = latest_start + 100;

        for (const auto& state : frontier) {
            int delta = state.first;
            int base_cost = state.second;
            int current_time = e[i] + delta;
            int sum_weight = 0;
            int batch_time = 0;

            for (int r = i; r < n; ++r) {
                if (e[r] > latest_reachable_arrival) {
                    break;
                }

                sum_weight += s[r];
                if (sum_weight > k) {
                    break;
                }

                batch_time = max(batch_time, m[r]);
                int start_time = max(current_time, e[r] - batch_time);
                if (start_time > latest_start) {
                    continue;
                }

                int total_cost = base_cost + batch_time;
                max_prefix = max(max_prefix, r + 1);

                if (r == n - 1) {
                    best_answer = min(best_answer, total_cost);
                    continue;
                }

                int next_delta = start_time + batch_time - e[r + 1];
                if (next_delta < 0) {
                    next_delta = 0;
                }
                if (next_delta <= v) {
                    cell(r + 1, next_delta) = min(cell(r + 1, next_delta), total_cost);
                }
            }
        }
    }

    if (best_answer < inf) {
        cout << best_answer << '\n';
    } else {
        cout << -max_prefix << '\n';
    }

    return 0;
}