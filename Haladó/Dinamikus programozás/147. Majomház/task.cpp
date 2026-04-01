/*
Ötlet:
Legyen P az A tömb prefixösszege, M = K + 1 pedig a végső csoportok száma.
Ha az utolsó csoport a (j+1..i) intervallum, akkor ennek költsége
(i-j) * (P[i] - P[j]), ezért egy rögzített lambda büntetés mellett a DP:

dp[i] = min_j { dp[j] + (i-j) * (P[i] - P[j]) + lambda }.

Minden állapothoz eltároljuk azt is, hogy az optimális penalizált megoldás
hány csoportot használ. Két jelölt j < k összehasonlításakor a költségkülönbség:

(dp[j] + j*P[j]) - (dp[k] + k*P[k]) + i*(P[k] - P[j]) + P[i]*(k-j),

ami i szerint szigorúan növekszik, mert i és P[i] is növekvő. Ez azt jelenti,
hogy két jelölt legfeljebb egyszer cserél sorrendet, tehát a legjobb elődök
érvényes tartományai egymás után következnek. Emiatt egy deque-ben tudjuk
tárolni a jelölteket, és minden új jelölthöz bináris kereséssel meghatározható,
honnan lesz jobb az előzőknél.

Egy adott lambda mellett így az egész DP O(N log N). A lambda növelése bünteti
az új csoportok nyitását, ezért az optimális csoportszám monoton csökken.
Binárisan megkeressük a legnagyobb olyan lambda értéket, amely mellett még
legalább M csoport használható. Ha az ehhez tartozó penalizált optimum értéke X,
akkor a valódi optimum X - lambda * M.
*/
/*
Hint 1: || Prefixösszeggel az [l..r] szakasz költsége egyetlen szorzattá egyszerűsödik. ||
Hint 2: || Előbb ne pontosan K vágást keress, hanem adj minden csoportért ugyanakkora lambda büntetést. ||
Hint 3: || Két lehetséges előd közül az egyik egy összefüggő i-tartományban jobb, utána a másik marad jobb. ||
Hint 4: || Ha egy adott lambda mellett tudod az optimális költséget és a felhasznált csoportszámot, akkor lambda-ra binárisan lehet keresni. ||
*/

#include <iostream>
#include <vector>

using i64 = long long;
using i128 = __int128_t;

struct Result {
    i64 cost;
    int groups;
};

struct Candidate {
    int index;
    int from;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;
    const int target_groups = k + 1;

    std::vector<i64> prefix(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        i64 value;
        std::cin >> value;
        prefix[i] = prefix[i - 1] + value;
    }

    std::vector<i64> dp(n + 1, 0);
    std::vector<int> used_groups(n + 1, 0);

    auto solve = [&](i64 lambda) -> Result {
        std::vector<Candidate> deque;
        deque.push_back({0, 1});
        int head = 0;

        auto value_of = [&](int previous, int position) -> i64 {
            return dp[previous] + 1LL * (position - previous) * (prefix[position] - prefix[previous]) + lambda;
        };

        auto better = [&](int left, int right, int position) -> bool {
            i64 left_value = value_of(left, position);
            i64 right_value = value_of(right, position);
            if (left_value != right_value) {
                return left_value < right_value;
            }
            return used_groups[left] > used_groups[right];
        };

        dp[0] = 0;
        used_groups[0] = 0;

        for (int i = 1; i <= n; ++i) {
            while (head + 1 < static_cast<int>(deque.size()) && deque[head + 1].from <= i) {
                ++head;
            }

            int best_previous = deque[head].index;
            dp[i] = value_of(best_previous, i);
            used_groups[i] = used_groups[best_previous] + 1;

            if (i == n) {
                continue;
            }

            int start = i + 1;
            while (static_cast<int>(deque.size()) > head) {
                int last_index = deque.back().index;
                int first_check = deque.back().from;
                if (first_check < i + 1) {
                    first_check = i + 1;
                }

                if (better(i, last_index, first_check)) {
                    deque.pop_back();
                    continue;
                }

                if (!better(i, last_index, n)) {
                    start = n + 1;
                    break;
                }

                int low = first_check + 1;
                int high = n;
                while (low < high) {
                    int mid = (low + high) / 2;
                    if (better(i, last_index, mid)) {
                        high = mid;
                    } else {
                        low = mid + 1;
                    }
                }
                start = low;
                break;
            }

            if (start <= n) {
                if (static_cast<int>(deque.size()) == head) {
                    start = i + 1;
                }
                deque.push_back({i, start});
            }
        }

        return {dp[n], used_groups[n]};
    };

    const i64 bound = 40000000000000000LL;
    i64 low = -bound;
    i64 high = bound;

    while (low < high) {
        i64 mid = low + (high - low + 1) / 2;
        Result current = solve(mid);
        if (current.groups >= target_groups) {
            low = mid;
        } else {
            high = mid - 1;
        }
    }

    Result best = solve(low);
    i128 answer = static_cast<i128>(best.cost) - static_cast<i128>(low) * target_groups;
    std::cout << static_cast<i64>(answer) << '\n';
    return 0;
}