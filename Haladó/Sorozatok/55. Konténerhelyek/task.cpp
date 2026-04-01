/*
Megoldas lenyege:
Egy blokk akkor pakolhato egyetlen toronnyá, ha a blokkon belul ujra es ujra le lehet venni
balrol vagy jobrol egy olyan kontenert, amely az aktualis blokk minimuma vagy maximuma.
Ez a szeparalhato-permutacios rekurzio pontosan a megengedett szomszedos torony-osszevonasokat
irja le.

Legyen L[r] a legkorabbi kezdoindex, ahonnan az r-ben vegzodo blokk meg jo. A jo kezdoindexek
mindig egy osszefuggo suffixet alkotnak. Egy uj jobb veg akkor tarthat meg egy korabbi jo blokkot,
ha a jobb veg uj minimum vagy uj maximum az adott reszben. Ezen felul balra tovabb lehet nyujtani
a blokkot minden olyan pozicion, amelynek eleme az aktualis jobb vegig minimum vagy maximum marad.
Ezekbol egy O(N log N) megoldas adodik monoton veremmel szamolt elozo/kovetkezo kisebb-nagyobb
poziciokkal es egy szegmensfaval.
*/
/*
Hint 1: || Egy blokk jo, ha vegig lebonthato ugy, hogy mindig valamelyik vegpont a jelenlegi minimum vagy maximum. ||
Hint 2: || Fix jobb vegre a jo kezdoindexek egy suffixet alkotnak. ||
Hint 3: || A balra hosszabbitast az donti el, meddig marad az adott bal veg minimum vagy maximum a blokkban. ||
*/
#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
public:
    explicit SegmentTree(const vector<int>& values) {
        int n = (int)values.size();
        size = 1;
        while (size < n) size <<= 1;
        tree.assign(2 * size, INT_MAX);
        for (int i = 0; i < n; ++i) tree[size + i] = values[i];
        for (int i = size - 1; i >= 1; --i) tree[i] = min(tree[2 * i], tree[2 * i + 1]);
    }

    explicit SegmentTree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        tree.assign(2 * size, INT_MAX);
    }

    void setValue(int index, int value) {
        int node = index + size;
        tree[node] = value;
        for (node >>= 1; node >= 1; node >>= 1) {
            tree[node] = min(tree[2 * node], tree[2 * node + 1]);
            if (node == 1) break;
        }
    }

    int rangeMin(int queryLeft, int queryRight) const {
        int left = queryLeft + size;
        int right = queryRight + size;
        int answer = INT_MAX;
        while (left <= right) {
            if (left & 1) answer = min(answer, tree[left++]);
            if (!(right & 1)) answer = min(answer, tree[right--]);
            left >>= 1;
            right >>= 1;
        }
        return answer;
    }

    int findLastLessThan(int rightExclusive, int threshold) const {
        return findLastLessThan(1, 0, size, rightExclusive, threshold);
    }

private:
    int size;
    vector<int> tree;

    int findLastLessThan(int node, int left, int right, int rightExclusive, int threshold) const {
        if (left >= rightExclusive || tree[node] >= threshold) return -1;
        if (right - left == 1) return left;

        int mid = (left + right) / 2;
        int answer = findLastLessThan(2 * node + 1, mid, right, rightExclusive, threshold);
        if (answer != -1) return answer;
        return findLastLessThan(2 * node, left, mid, rightExclusive, threshold);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    vector<int> prevSmaller(n, -1), prevGreater(n, -1), nextSmaller(n, n), nextGreater(n, n);
    vector<int> st;

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && a[st.back()] > a[i]) st.pop_back();
        prevSmaller[i] = st.empty() ? -1 : st.back();
        st.push_back(i);
    }

    st.clear();
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && a[st.back()] < a[i]) st.pop_back();
        prevGreater[i] = st.empty() ? -1 : st.back();
        st.push_back(i);
    }

    st.clear();
    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && a[st.back()] > a[i]) st.pop_back();
        nextSmaller[i] = st.empty() ? n : st.back();
        st.push_back(i);
    }

    st.clear();
    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && a[st.back()] < a[i]) st.pop_back();
        nextGreater[i] = st.empty() ? n : st.back();
        st.push_back(i);
    }

    vector<int> reach(n);
    for (int i = 0; i < n; ++i) {
        reach[i] = max(nextSmaller[i], nextGreater[i]) - 1;
    }

    SegmentTree segTree(reach);
    vector<int> leftmostGoodStart(n, 0);
    leftmostGoodStart[0] = 0;
    for (int right = 1; right < n; ++right) {
        int keepAsMin = max(leftmostGoodStart[right - 1], prevSmaller[right] + 1);
        int keepAsMax = max(leftmostGoodStart[right - 1], prevGreater[right] + 1);
        int baseStart = min(keepAsMin, keepAsMax);
        int lastBlocking = segTree.findLastLessThan(baseStart, right);
        leftmostGoodStart[right] = lastBlocking + 1;
    }

    vector<int> dp(n + 1, INT_MAX / 2);
    SegmentTree dpTree(n + 1);
    dp[0] = 0;
    dpTree.setValue(0, 0);
    for (int right = 0; right < n; ++right) {
        dp[right + 1] = dpTree.rangeMin(leftmostGoodStart[right], right) + 1;
        dpTree.setValue(right + 1, dp[right + 1]);
    }

    cout << n - dp[n] << '\n';
    return 0;
}