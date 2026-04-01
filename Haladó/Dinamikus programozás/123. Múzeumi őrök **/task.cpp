/*
Megoldási ötlet:
A cél az [E,U] teljes napintervallum folytonos lefedése minimum költséggel. Legyen dp[x] a minimális költség,
amellyel az [E,x] intervallum már teljesen lefedhető. Ha egy őr [l,r] intervallumot fed le, akkor csak olyan korábbi
állapotból használható fel, ahol már legalább l-1-ig folyamatos a lefedés, de még nem jutottunk túl r-1-en.

Az intervallumvégek nagyok lehetnek, ezért koordinátakompressziót alkalmazunk az E-1, az összes l-1 és r értékre.
Ezeken a pontokon egy szegmensfában tároljuk a jelenleg ismert legjobb dp-értékeket, így minden őrhöz O(log N)-ben
megkapható a szükséges minimum az [l-1, r-1] tartományon.
*/
/*
Hint 1: || Az [E,x] prefix lefedésének ára természetes DP-állapot. ||
Hint 2: || Egy új intervallum csak akkor illeszthető be, ha a korábban lefedett rész eléri legalább az intervallum kezdete előtti napot. ||
Hint 3: || A nagy nap-sorszámok miatt a releváns végpontokat kompresszáld, és ezek fölött tárolj minimumot. ||
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct Guard {
    int start;
    int finish;
    long long cost;
    int index;
};

struct Best {
    long long value;
    int index;
};

Best better(Best a, Best b) {
    if (a.value != b.value) return (a.value < b.value ? a : b);
    return (a.index < b.index ? a : b);
}

class SegTree {
public:
    explicit SegTree(int n) : size(n), tree(4 * n, {inf(), -1}) {}

    void update(int node, int left, int right, int pos, Best value) {
        if (left == right) {
            tree[node] = better(tree[node], value);
            return;
        }
        int mid = (left + right) >> 1;
        if (pos <= mid) update(node << 1, left, mid, pos, value);
        else update(node << 1 | 1, mid + 1, right, pos, value);
        tree[node] = better(tree[node << 1], tree[node << 1 | 1]);
    }

    Best query(int node, int left, int right, int ql, int qr) const {
        if (qr < left || right < ql) return {inf(), -1};
        if (ql <= left && right <= qr) return tree[node];
        int mid = (left + right) >> 1;
        return better(query(node << 1, left, mid, ql, qr), query(node << 1 | 1, mid + 1, right, ql, qr));
    }

    static long long inf() {
        return numeric_limits<long long>::max() / 4;
    }

private:
    int size;
    vector<Best> tree;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, e, u;
    cin >> n >> e >> u;
    vector<Guard> guards(n);
    vector<int> coords = {e - 1, u};
    for (int i = 0; i < n; ++i) {
        cin >> guards[i].start >> guards[i].finish >> guards[i].cost;
        guards[i].index = i + 1;
        coords.push_back(guards[i].start - 1);
        coords.push_back(guards[i].finish);
    }

    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());

    auto coordIndex = [&](int x) {
        return static_cast<int>(lower_bound(coords.begin(), coords.end(), x) - coords.begin());
    };
    auto lastNotGreater = [&](int x) {
        return static_cast<int>(upper_bound(coords.begin(), coords.end(), x) - coords.begin()) - 1;
    };

    sort(guards.begin(), guards.end(), [](const Guard& a, const Guard& b) {
        if (a.finish != b.finish) return a.finish < b.finish;
        return a.start < b.start;
    });

    int c = static_cast<int>(coords.size());
    vector<long long> dp(c, SegTree::inf());
    vector<int> parentCoord(c, -1), parentGuard(c, -1);
    SegTree tree(c);
    int startPos = coordIndex(e - 1);
    dp[startPos] = 0;
    tree.update(1, 0, c - 1, startPos, {0, startPos});

    for (const Guard& guard : guards) {
        int left = coordIndex(guard.start - 1);
        int right = lastNotGreater(guard.finish - 1);
        if (left > right) continue;
        Best previous = tree.query(1, 0, c - 1, left, right);
        if (previous.value == SegTree::inf()) continue;
        int finishPos = coordIndex(guard.finish);
        long long candidate = previous.value + guard.cost;
        if (candidate < dp[finishPos]) {
            dp[finishPos] = candidate;
            parentCoord[finishPos] = previous.index;
            parentGuard[finishPos] = guard.index;
            tree.update(1, 0, c - 1, finishPos, {candidate, finishPos});
        }
    }

    int targetPos = coordIndex(u);
    if (dp[targetPos] == SegTree::inf()) {
        cout << -1 << '\n';
        return 0;
    }

    vector<int> chosen;
    for (int pos = targetPos; pos != startPos; pos = parentCoord[pos]) {
        chosen.push_back(parentGuard[pos]);
    }
    sort(chosen.begin(), chosen.end());

    cout << dp[targetPos] << '\n';
    cout << chosen.size();
    for (int index : chosen) cout << ' ' << index;
    cout << '\n';
    return 0;
}