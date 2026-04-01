/*
Megoldasi otlet:
Tekintsuk azt, hogy mely eredeti A[i] elemeket tudjuk valtozatlanul megtartani. Ha ket megtartott
elem a j. es az i. helyen all (j < i), akkor a koztuk levo i-j-1 poziciot csak olyan bubajokkal
tolthetjuk ki, amelyek erteke A[j] es A[i] koze esik. Ha B-ben a kisebb A-ertek alatt smaller[j], a
masik alatt smaller[i] darab elem van, akkor pontosan smaller[i]-smaller[j] darab buvaj esik a ket
ertek koze. Tehat j utan i akkor teheto, ha A[j] < A[i] es smaller[i]-smaller[j] >= i-j-1.

Legyen key[i] = smaller[i] - i. Ekkor az atmeneti feltetel: key[j] <= key[i] + 1, mikozben A[j] < A[i].
Az elso megtartott elemhez meg az kell, hogy legyen eleg kisebb buvaj elotte: smaller[i] >= i. Az utolso
megtartott elem utan pedig legyen eleg nagyobb buvaj: M-smaller[i] >= N-1-i.

Igazi feladatunk tehat: maximalizalni a megtarthato eredeti elemek szamat. Legyen dp[i] a legnagyobb ilyen
darabszam, ha az i. hely az utolso megtartott eredeti elem. Ekkor

dp[i] = 1 + max(dp[j]) minden olyan j < i esetre, amelyre A[j] < A[i] es key[j] <= key[i] + 1.

Ez egy haromdimenzios dominancia-DP (index, ertek, key). Az index szerinti j < i feltetelt CDQ oszd-meg-
es-uralkodj modon kezeljuk, a masik ket feltetelt pedig Fenwick-faval: a bal felbol csak a kisebb A-ju
pontokat aktivjuk, es kozben prefixmaximumot kerdezunk key szerint. A valasz N - maximalisan megtarthato
eredeti elemek szama.
*/
/*
Hint 1: || Ket megtartott eredeti elem kozotti reshez pontosan annyi B-ertek kell, ahany poziciot ki kell tolteni. ||
Hint 2: || Szamold ki minden A[i]-re, hogy hany B elem kisebb nala; ezzel a resfeltetel egy egyszeru egyenlotlensegge alakul. ||
Hint 3: || A DP-atmenet egyszerre fugg az indextol, az A-ertektol es a key = smaller - index mennyisegtol. ||
Hint 4: || A j < i feltetelt CDQ-val, az A[j] < A[i] es key[j] <= key[i]+1 felteteleket Fenwick-fas prefixmaximummal lehet gyorsan kezelni. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct FenwickMax {
    int n;
    vector<int> bit;
    vector<int> touched;

    explicit FenwickMax(int n) : n(n), bit(n + 1, 0) {
        touched.reserve(n);
    }

    void update(int idx, int value) {
        for (int i = idx; i <= n; i += i & -i) {
            if (bit[i] == 0) touched.push_back(i);
            if (bit[i] < value) bit[i] = value;
        }
    }

    int query(int idx) const {
        int answer = 0;
        for (int i = idx; i > 0; i -= i & -i) {
            if (answer < bit[i]) answer = bit[i];
        }
        return answer;
    }

    void clear() {
        for (int idx : touched) bit[idx] = 0;
        touched.clear();
    }
};

int n, m;
vector<int> a;
vector<int> key_value;
vector<int> key_pos;
vector<int> query_pos;
vector<int> dp;
vector<int> smaller;
vector<int> sorted_b;
vector<int> coords;
FenwickMax* fenwick;

void solve(int left, int right) {
    if (left == right) return;

    int middle = (left + right) / 2;
    solve(left, middle);

    vector<int> left_ids;
    vector<int> right_ids;
    left_ids.reserve(middle - left + 1);
    right_ids.reserve(right - middle);

    for (int i = left; i <= middle; ++i) left_ids.push_back(i);
    for (int i = middle + 1; i <= right; ++i) right_ids.push_back(i);

    sort(left_ids.begin(), left_ids.end(), [](int first, int second) {
        return a[first] < a[second];
    });
    sort(right_ids.begin(), right_ids.end(), [](int first, int second) {
        return a[first] < a[second];
    });

    int pointer = 0;
    for (int id : right_ids) {
        while (pointer < static_cast<int>(left_ids.size()) && a[left_ids[pointer]] < a[id]) {
            if (dp[left_ids[pointer]] > 0) {
                fenwick->update(key_pos[left_ids[pointer]], dp[left_ids[pointer]]);
            }
            ++pointer;
        }
        int best = fenwick->query(query_pos[id]);
        if (best > 0 && dp[id] < best + 1) dp[id] = best + 1;
    }
    fenwick->clear();

    solve(middle + 1, right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    a.resize(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    sorted_b.resize(m);
    for (int i = 0; i < m; ++i) cin >> sorted_b[i];
    sort(sorted_b.begin(), sorted_b.end());

    smaller.resize(n);
    key_value.resize(n);
    coords.reserve(n);
    for (int i = 0; i < n; ++i) {
        smaller[i] = lower_bound(sorted_b.begin(), sorted_b.end(), a[i]) - sorted_b.begin();
        key_value[i] = smaller[i] - i;
        coords.push_back(key_value[i]);
    }

    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());

    key_pos.resize(n);
    query_pos.resize(n);
    for (int i = 0; i < n; ++i) {
        key_pos[i] = lower_bound(coords.begin(), coords.end(), key_value[i]) - coords.begin() + 1;
        query_pos[i] = upper_bound(coords.begin(), coords.end(), key_value[i] + 1) - coords.begin();
    }

    dp.assign(n, 0);
    for (int i = 0; i < n; ++i) {
        if (smaller[i] >= i) dp[i] = 1;
    }

    FenwickMax bit(static_cast<int>(coords.size()));
    fenwick = &bit;
    solve(0, n - 1);

    int best_keep = 0;
    for (int i = 0; i < n; ++i) {
        if (m - smaller[i] >= n - 1 - i && best_keep < dp[i]) {
            best_keep = dp[i];
        }
    }

    cout << n - best_keep << '\n';
    return 0;
}