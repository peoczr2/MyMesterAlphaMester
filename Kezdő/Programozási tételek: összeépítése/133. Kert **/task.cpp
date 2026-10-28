/*
Megoldás lényege:
Egy sorban legfeljebb egy szín lehet többségben: ha egy szín d-szer szerepel a sorban, akkor többségben van, ha d > N − d, azaz 2·d > N. A sor egy rendezett másolatában az azonos színek egymás mellé kerülnek, így a legnagyobb futamhossz adja a legnagyobb d-t. Az egymás melletti azonos színek maximumát az eredeti sorrendben, egy végigmenéssel számoljuk. Mivel M·N ≤ 500 000, a soronkénti rendezés összesen O(M·N log N) időt igényel.
*/
/*
Hint 1: || Ha egy szín darabszáma d, akkor pontosan akkor van többségben, ha 2·d > N. A legnagyobb darabszámot megkapod, ha a sort rendezed, mert az azonos színek egymás mellé kerülnek. ||
Hint 2: || Az egymás melletti azonos színek hosszát az eredeti sorrendben egy végigmenéssel számold: ha az aktuális elem egyezik az előzővel, a futam nő, különben 1-ről indul. ||
*/
#include <bits/stdc++.h>
using namespace std;

// A vektorban a leghosszabb, egymás melletti azonos értékű futam hossza.
int max_run(const vector<int> &v) {
    int best = 0, cur = 0;
    for (size_t j = 0; j < v.size(); ++j) {
        cur = (j > 0 && v[j] == v[j - 1]) ? cur + 1 : 1;
        best = max(best, cur);
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    long long p;
    cin >> m >> n >> p;

    int majority_rows = 0, best_run = 0;
    vector<int> row(n);
    for (int i = 0; i < m; ++i) {
        for (auto &x : row) cin >> x;
        best_run = max(best_run, max_run(row));

        vector<int> sorted_row = row;
        sort(sorted_row.begin(), sorted_row.end());
        if (2 * max_run(sorted_row) > n) ++majority_rows;
    }
    cout << majority_rows << '\n' << best_run << '\n';
    return 0;
}
