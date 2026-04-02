/*
Megoldás:
Rendezzük az intervallumokat bal végpont szerint. Egy rögzített első intervallum [a_i,b_i]
mellé olyan második intervallumot kell választani, amelynek bal vége legfeljebb b_i, mert csak
ekkor van közös pontjuk. A lefedett egyesített szakasz hossza ekkor egyszerűen max(b_j)-a_i,
ahol a maximumot az i..r tartományban vesszük, r az utolsó olyan index, amelyre a_r <= b_i.

Tehát minden i-re meg kell találni a [i,r] tartományban a legnagyobb jobb végpontot. Ezt egy
szegmensfával támogatjuk, miközben kétmutatósan mozgatjuk r-t.

Az algoritmus O(N log N) idejű és O(N) memóriájú.
*/
/*
Hint 1: || Ha az első intervallumot rögzíted, akkor a második csak olyan lehet, amelyik eléri az első jobb végét. ||
Hint 2: || A célfüggvény ekkor a második intervallum minél nagyobb jobb vége lesz. ||
Hint 3: || A rendezés után minden i-hez egy prefixszerű tartomány maximumát kell kérdezni. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Interval {
    int left;
    int right;
};

struct Node {
    int right;
    int index;
};

Node mergeNode(const Node &left, const Node &right) {
    if (left.right >= right.right) {
        return left;
    }
    return right;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Interval> intervals(n);
    for (int i = 0; i < n; ++i) {
        cin >> intervals[i].left >> intervals[i].right;
    }

    sort(intervals.begin(), intervals.end(), [](const Interval &a, const Interval &b) {
        if (a.left != b.left) {
            return a.left < b.left;
        }
        return a.right < b.right;
    });

    int size = 1;
    while (size < n) {
        size <<= 1;
    }
    vector<Node> seg(2 * size, Node{-1, -1});
    for (int i = 0; i < n; ++i) {
        seg[size + i] = Node{intervals[i].right, i};
    }
    for (int i = size - 1; i >= 1; --i) {
        seg[i] = mergeNode(seg[2 * i], seg[2 * i + 1]);
    }

    auto query = [&](int left, int right) {
        Node resultLeft{-1, -1};
        Node resultRight{-1, -1};
        left += size;
        right += size;
        while (left <= right) {
            if (left % 2 == 1) {
                resultLeft = mergeNode(resultLeft, seg[left]);
                ++left;
            }
            if (right % 2 == 0) {
                resultRight = mergeNode(seg[right], resultRight);
                --right;
            }
            left /= 2;
            right /= 2;
        }
        return mergeNode(resultLeft, resultRight);
    };

    long long bestLength = -1;
    int bestFirst = 0;
    int bestSecond = 0;
    int r = 0;

    for (int i = 0; i < n; ++i) {
        while (r < n && intervals[r].left <= intervals[i].right) {
            ++r;
        }
        Node bestInRange = query(i, r - 1);
        long long covered = 1LL * bestInRange.right - intervals[i].left;
        if (covered > bestLength) {
            bestLength = covered;
            bestFirst = i;
            bestSecond = bestInRange.index;
        }
    }

    cout << intervals[bestFirst].left << ' ' << intervals[bestFirst].right << '\n';
    cout << intervals[bestSecond].left << ' ' << intervals[bestSecond].right << '\n';
    return 0;
}