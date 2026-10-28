/*
Megoldás lényege:
Minden pozícióban csak a fedő intervallumok száma számít 10-es maradék szerint.
Egy [L, R] intervallum hozzáadása minden érintett pozícióban a maradékot 1-gyel
növeli mod 10, az aktuális maradékok összege pedig a lekérdezett szakasz válasza.
Ezt egy lazított szegmensfa oldja meg: minden csúcsban a 0..9 maradékok darabszámát
tároljuk, a lazy érték pedig a teljes szakasz forgatásának mértéke mod 10.
Idő: O((N + M) * log N * 10)
*/
/*
Hint 1: || Csak a fedő intervallumok száma 10-es maradékának van szerepe, így minden pozícióhoz elég a 0..9 maradékot tárolni. Egy intervallum hozzáadása a szakaszon minden értéket 1-gyel léptet tovább mod 10. ||
Hint 2: || Szegmensfába tegyük: minden csúcsban tárolunk egy tömböt, amely megmondja, hány pozícióban van 0, 1, ..., 9 maradék a szakaszon, és egy lazy értékkel a teljes szakasz tömbjét körbeforgatjuk. ||
Hint 3: || A lekérdezésnél a szakasz összege a sum d * cnt[d] képlettel adódik, a lazy értékek mod 10 összeadódnak, és a gyerek csúcsokhoz lefelé kell átadni a körbeforgatást, mielőtt a részszakaszokat bejárjuk. ||
*/
#include <bits/stdc++.h>
using namespace std;

static const int MAXD = 10;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    if (!(cin >> N >> M)) return 0;
    string s;
    cin >> s;

    int size = 1;
    while (size < N) size <<= 1;
    vector<array<int, MAXD>> cnt(2 * size);
    vector<unsigned char> lazy(2 * size, 0);

    for (int i = 0; i < N; ++i) cnt[size + i][s[i] - '0'] = 1;
    for (int i = size - 1; i >= 1; --i) {
        for (int d = 0; d < MAXD; ++d) cnt[i][d] = cnt[i << 1][d] + cnt[i << 1 | 1][d];
    }

    auto apply = [&](int node, int shift) {
        if (shift == 0) return;
        array<int, MAXD> tmp{};
        for (int d = 0; d < MAXD; ++d) tmp[(d + shift) % MAXD] = cnt[node][d];
        cnt[node] = tmp;
        lazy[node] = (lazy[node] + shift) % MAXD;
    };

    function<void(int)> push = [&](int node) {
        if (lazy[node] != 0) {
            apply(node << 1, lazy[node]);
            apply(node << 1 | 1, lazy[node]);
            lazy[node] = 0;
        }
    };

    function<void(int)> pull = [&](int node) {
        for (int d = 0; d < MAXD; ++d) cnt[node][d] = cnt[node << 1][d] + cnt[node << 1 | 1][d];
    };

    function<void(int,int,int,int,int)> rangeAdd = [&](int node, int nl, int nr, int l, int r) {
        if (l <= nl && nr <= r) {
            apply(node, 1);
            return;
        }
        push(node);
        int mid = (nl + nr) >> 1;
        if (l <= mid) rangeAdd(node << 1, nl, mid, l, r);
        if (r > mid) rangeAdd(node << 1 | 1, mid + 1, nr, l, r);
        pull(node);
    };

    function<int(int,int,int,int,int)> rangeSum = [&](int node, int nl, int nr, int l, int r) -> int {
        if (l <= nl && nr <= r) {
            int sum = 0;
            for (int d = 0; d < MAXD; ++d) sum += d * cnt[node][d];
            return sum;
        }
        push(node);
        int mid = (nl + nr) >> 1;
        int res = 0;
        if (l <= mid) res += rangeSum(node << 1, nl, mid, l, r);
        if (r > mid) res += rangeSum(node << 1 | 1, mid + 1, nr, l, r);
        return res;
    };

    string out;
    out.reserve((size_t)M * 12);
    for (int i = 0; i < M; ++i) {
        int A, B;
        cin >> A >> B;
        --A; --B;
        out += to_string(rangeSum(1, 0, size - 1, A, B));
        out += '\n';
        rangeAdd(1, 0, size - 1, A, B);
    }

    cout << out;
    return 0;
}