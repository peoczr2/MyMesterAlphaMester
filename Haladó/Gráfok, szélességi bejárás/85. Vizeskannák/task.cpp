/*
Megoldás lényege:
Az állapot a három kannában lévő víz mennyisége. Mivel a vizek összmennyisége mindig M1 liter marad,
elég két kanna tartalmát nyilvántartani, a harmadik ebből kiszámolható.
Szélességi bejárással (BFS) keressük a legkevesebb átöntéssel elérhető olyan állapotot, ahol valamelyik kannában pontosan L liter van:
a BFS rétegei az átöntések számát adják, így az első olyan réteg, amelyben L literes állapot van, adja a választ.
Egy állapotból i-es kannából j-be úgy öntünk, hogy annyi víz megy át, amennyi a forrásban van, vagy amennyi a célban elfér – a kisebbik.
Minden állapotot csak egyszer látogatunk meg, így az időigény és a memória is arányos az állapotok számával, azaz kb. M1 * M2.
*/
/*
Hint 1: || Az összes víz mennyisége nem változik, ezért elég az első két kanna tartalmát nyilvántartani: a harmadik mindig M1 - a - b. ||
Hint 2: || Szélességi bejárást használj: a rétegek az átöntések számát jelölik, így az első olyan állapot, amelyben valamelyik kannában L liter van, már a minimális átöntésszámot adja. ||
Hint 3: || Egy átöntésnél az i-edik kannából a j-edikbe a forrás tartalma és a cél szabad helye közül a kisebb mennyiség folyik át. Minden állapotot csak egyszer vegyél fel a sorba, egy tömbbel jelölve. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int cap[3];
    int L;
    cin >> cap[0] >> cap[1] >> cap[2] >> L;

    const int total = cap[0];
    const size_t width = (size_t)cap[1] + 1;
    // Állapot: (a, b), a az 1. kanna, b a 2. kanna vize; a 3. kanna vize total - a - b.
    vector<bool> seen((size_t)(cap[0] + 1) * width, false);
    auto index = [&](int a, int b) { return (size_t)a * width + (size_t)b; };

    vector<pair<int, int>> level = {{cap[0], 0}};
    seen[index(cap[0], 0)] = true;
    int depth = 0;

    while (!level.empty()) {
        vector<pair<int, int>> next;
        for (auto [a, b] : level) {
            int s[3] = {a, b, total - a - b};
            if (s[0] == L || s[1] == L || s[2] == L) {
                cout << depth << '\n';
                return 0;
            }
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (i == j || s[i] == 0 || s[j] == cap[j]) {
                        continue;
                    }
                    int amount = min(s[i], cap[j] - s[j]);
                    int t[3] = {s[0], s[1], s[2]};
                    t[i] -= amount;
                    t[j] += amount;
                    size_t id = index(t[0], t[1]);
                    if (!seen[id]) {
                        seen[id] = true;
                        next.push_back({t[0], t[1]});
                    }
                }
            }
        }
        level.swap(next);
        ++depth;
    }

    cout << -1 << '\n';
    return 0;
}
