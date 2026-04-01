/*
Megoldási ötlet:
Az autó 1 kilométerhez 1 egység benzint fogyaszt, ezért minden benzinkútnál ugyanaz a klasszikus tankolási mohó stratégia
érvényes. Ha a mostani kúttól elérhető tartományban van olyan későbbi kút, ahol nem drágább a benzin, akkor csak addig
tankolunk, amíg biztosan elérjük az első ilyen kutat. Ha nincs ilyen, akkor tele tankolunk.

A gyors kereséshez a kutak fölött szegmensfát építünk, amely a minimum árat tárolja. Egy kúttól indulva előbb kétmutatós
módszerrel meghatározzuk, meddig jutunk el tele tankkal, majd a szegmensfában megkeressük az első nem drágább kutat ezen a
szakaszon. Ezután a megvett üzemanyag mennyisége már egyértelmű.
*/
/*
Hint 1: || Ha van elérhető nem drágább kút, akkor nem érdemes annál továbbra előre drága benzint venni. ||
Hint 2: || Ha nincs ilyen, akkor a jelenlegi kútnál érdemes a lehető legtöbbet vásárolni. ||
Hint 3: || Az „első elérhető nem drágább kút” kereséséhez hasznos egy minimumot tároló szegmensfa. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class SegTree {
public:
    explicit SegTree(const vector<int>& price) : n(static_cast<int>(price.size()) - 1), tree(4 * n, 0), prices(price) {
        build(1, 1, n);
    }

    int firstAtMost(int node, int left, int right, int ql, int qr, int limit) const {
        if (qr < left || right < ql || tree[node] > limit) return -1;
        if (left == right) return left;
        int mid = (left + right) >> 1;
        int result = firstAtMost(node << 1, left, mid, ql, qr, limit);
        if (result != -1) return result;
        return firstAtMost(node << 1 | 1, mid + 1, right, ql, qr, limit);
    }

private:
    int n;
    vector<int> tree;
    const vector<int>& prices;

    void build(int node, int left, int right) {
        if (left == right) {
            tree[node] = prices[left];
            return;
        }
        int mid = (left + right) >> 1;
        build(node << 1, left, mid);
        build(node << 1 | 1, mid + 1, right);
        tree[node] = min(tree[node << 1], tree[node << 1 | 1]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, tank;
    cin >> n >> tank;
    vector<int> dist(n + 1), price(n + 2);
    vector<long long> position(n + 2, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> dist[i] >> price[i];
    }
    price[n + 1] = 0;
    for (int i = 1; i <= n; ++i) position[i + 1] = position[i] + dist[i];

    SegTree seg(price);
    vector<long long> bought(n + 1, 0);
    long long totalCost = 0;
    long long fuel = 0;

    int reach = 1;
    for (int i = 1; i <= n; ++i) {
        while (reach + 1 <= n + 1 && position[reach + 1] - position[i] <= tank) ++reach;
        int target = -1;
        if (i + 1 <= reach) target = seg.firstAtMost(1, 1, n + 1, i + 1, reach, price[i]);
        long long desiredFuel = (target == -1 ? tank : position[target] - position[i]);
        if (desiredFuel > fuel) {
            long long add = desiredFuel - fuel;
            bought[i] = add;
            totalCost += add * price[i];
            fuel = desiredFuel;
        }
        fuel -= dist[i];
    }

    vector<pair<int, long long>> answer;
    for (int i = 1; i <= n; ++i) {
        if (bought[i] > 0) answer.push_back({i, bought[i]});
    }

    cout << totalCost << ' ' << answer.size() << '\n';
    for (const auto& [index, amount] : answer) {
        cout << index << ' ' << amount << '\n';
    }
    return 0;
}