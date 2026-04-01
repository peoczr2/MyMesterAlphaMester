/*
Minden ajanlat egy [A,B] idointervallumot foglal le es C penzt er. Egyszerre csak egy munkat lehet
vegezni, tehat sulyozott intervallum-kivalasztast kell megoldani. Az ajanlatokat a befejezesi ido
szerint rendezzuk, es minden munkahoz megkeressuk az utolso kompatibilis elodot, amelynek a vege
szigoruan kisebb a mostani kezdetnel. Ha dp[i] az elso i rendezett ajanlatbol elerheto legnagyobb
kereset, akkor dp[i] = max(dp[i-1], dp[p[i]] + C_i). A keresett maximum dp[n].
*/
/*
Hint 1: || Egy munkat csak olyan masik kovethet, amelyik legkesobb a kezdet elott befejezodik. ||
Hint 2: || A klasszikus ket eset itt is mukodik: kihagyjuk az i-edik munkat, vagy felvesszuk. ||
Hint 3: || Nagy N miatt a kompatibilis elozo munkat rendezes utan erdemes binary search-csel keresni. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Job {
    int start;
    int finish;
    int gain;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Job> jobs(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> jobs[i].start >> jobs[i].finish >> jobs[i].gain;
    }

    sort(jobs.begin() + 1, jobs.end(), [](const Job& left, const Job& right) {
        if (left.finish != right.finish) {
            return left.finish < right.finish;
        }
        if (left.start != right.start) {
            return left.start < right.start;
        }
        return left.gain < right.gain;
    });

    vector<int> finishes(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        finishes[i] = jobs[i].finish;
    }

    vector<int> previous(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        previous[i] = static_cast<int>(lower_bound(finishes.begin() + 1, finishes.begin() + i, jobs[i].start) - finishes.begin()) - 1;
    }

    vector<long long> dp(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        dp[i] = max(dp[i - 1], dp[previous[i]] + jobs[i].gain);
    }

    cout << dp[n] << '\n';
    return 0;
}