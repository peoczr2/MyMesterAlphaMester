/*
Minden tranzakciobol kiszamoljuk az egyes emberek netto egyenleget. Ha X Y-tol P penzt kert,
akkor X-nek P-t vissza kell majd fizetnie, Y pedig P-t kap vissza. Ezert X egyenlege -P,
Y egyenlege +P iranyban valtozik.

Az optimalis kiegyenlitesnel az atutalt teljes penzosszeg pontosan a pozitiv egyenlegek osszege,
mert ennyit kell a hitelezoknek osszesen megkapniuk, es ennyit fizetnek ki osszesen az adosok is.
Egy konkret optimalis atutalasi sorozatot ket mutatoval tudunk elkesziteni: sorra parositjuk a
negativ es pozitiv egyenlegu embereket, es mindig a kisebb maradekot rendezzuk.
*/
/*
Hint 1: || Először ne a tranzakciók sorrendjével foglalkozz, hanem azzal, hogy a végén ki mennyivel tartozik vagy mennyit kap. ||
Hint 2: || A minimális összeg nem függ a konkrét sorozattól: az összes pozitív nettó egyenleg összege lesz. ||
Hint 3: || Az adósokat és a hitelezőket két listába gyűjtve kapzsian össze lehet őket párosítani. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int k;
    cin >> k;

    vector<long long> balance(n + 1, 0);
    for (int i = 0; i < k; ++i) {
        int x, y;
        long long amount;
        cin >> x >> y >> amount;
        balance[x] -= amount;
        balance[y] += amount;
    }

    vector<pair<int, long long>> debtors;
    vector<pair<int, long long>> creditors;
    long long total = 0;

    for (int person = 1; person <= n; ++person) {
        if (balance[person] < 0) {
            debtors.push_back({person, -balance[person]});
        } else if (balance[person] > 0) {
            creditors.push_back({person, balance[person]});
            total += balance[person];
        }
    }

    vector<tuple<int, int, long long>> answer;
    size_t debtorIndex = 0;
    size_t creditorIndex = 0;

    while (debtorIndex < debtors.size() && creditorIndex < creditors.size()) {
        long long transferred = min(debtors[debtorIndex].second, creditors[creditorIndex].second);
        answer.push_back({debtors[debtorIndex].first, creditors[creditorIndex].first, transferred});
        debtors[debtorIndex].second -= transferred;
        creditors[creditorIndex].second -= transferred;
        if (debtors[debtorIndex].second == 0) ++debtorIndex;
        if (creditors[creditorIndex].second == 0) ++creditorIndex;
    }

    cout << total << '\n';
    for (const auto& [from, to, amount] : answer) {
        cout << from << ' ' << to << ' ' << amount << '\n';
    }
    return 0;
}