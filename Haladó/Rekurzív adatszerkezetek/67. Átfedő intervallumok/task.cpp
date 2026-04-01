/*
Megoldási ötlet:
Az értékek csak 0-tól 9-ig tartanak, és minden művelet egy intervallum minden elemét 1-gyel növeli 10-es maradék szerint.
Ezért egy szegmensfában minden csomópontra elég megjegyezni, hogy az adott szakaszon hány darab 0, 1, ..., 9 érték van,
valamint a szakasz összegét.

Egy teljes lefedésű frissítés csak a 10 darab számláló körbeforgatása. A lekérdezés a szakaszösszeg, majd utána jön a
körbeforgatás.
*/
/*
Hint 1: || Az értékek csak 10-féleképpen változhatnak, ezért a lusta jelölés is csak 0..9 lehet. ||
Hint 2: || Ha egy egész szakaszt 1-gyel növelsz, a darabszámok körbefordulnak. ||
Hint 3: || Minden művelet előtt előbb kérdezz, utána frissítsd ugyanazt az intervallumot. ||
*/

#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    array<int, 10> cnt{};
    long long sum = 0;
    int lazy = 0;
};

int n, m;
vector<Node> seg;
string initial;

void pull(int node) {
    seg[node].sum = seg[node * 2].sum + seg[node * 2 + 1].sum;
    for (int i = 0; i < 10; ++i) {
        seg[node].cnt[i] = seg[node * 2].cnt[i] + seg[node * 2 + 1].cnt[i];
    }
}

void apply(int node, int shift, int l, int r) {
    if (shift == 0) return;
    array<int, 10> next{};
    for (int i = 0; i < 10; ++i) next[(i + shift) % 10] = seg[node].cnt[i];
    seg[node].cnt = next;
    seg[node].lazy = (seg[node].lazy + shift) % 10;
    seg[node].sum = 0;
    for (int i = 0; i < 10; ++i) seg[node].sum += 1LL * i * seg[node].cnt[i];
}

void push(int node, int l, int r) {
    if (seg[node].lazy == 0 || l == r) return;
    int shift = seg[node].lazy;
    apply(node * 2, shift, l, (l + r) / 2);
    apply(node * 2 + 1, shift, (l + r) / 2 + 1, r);
    seg[node].lazy = 0;
}

void build(int node, int l, int r) {
    if (l == r) {
        int d = initial[l - 1] - '0';
        seg[node].cnt[d] = 1;
        seg[node].sum = d;
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    pull(node);
}

long long query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return seg[node].sum;
    push(node, l, r);
    int mid = (l + r) / 2;
    long long ans = 0;
    if (ql <= mid) ans += query(node * 2, l, mid, ql, qr);
    if (qr > mid) ans += query(node * 2 + 1, mid + 1, r, ql, qr);
    return ans;
}

void update(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        apply(node, 1, l, r);
        return;
    }
    push(node, l, r);
    int mid = (l + r) / 2;
    if (ql <= mid) update(node * 2, l, mid, ql, qr);
    if (qr > mid) update(node * 2 + 1, mid + 1, r, ql, qr);
    pull(node);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    cin >> initial;
    seg.assign(4 * n + 4, Node{});
    build(1, 1, n);

    while (m--) {
        int a, b;
        cin >> a >> b;
        cout << query(1, 1, n, a, b) << '\n';
        update(1, 1, n, a, b);
    }
    return 0;
}
