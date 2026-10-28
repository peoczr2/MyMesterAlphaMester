/*
Megoldás lényege:
Az állapot a három ismert kannában lévő tejmennyiség (a, b, c); a negyedik kanna tartalma mindig d = A - a - b - c, mert a teljes tej mennyisége A.
A negyedik kanna legnagyobb, így sosem telik meg: ha bele töltünk, mindig az áttöltött mennyiség a forrás teljes tartalma, vagyis a kapacitása nem korlátoz.
Szélességi bejárással (BFS) bejárjuk az összes elérhető állapotot: egy áttöltésnél a mennyiség min(forrás tartalma, cél szabad helye).
Végül minden elért d értéket megjelölünk, és az 1..A közötti nem megjelölt értékek adják a kimérhetetlen mennyiségeket.
Az állapotok száma legfeljebb (A+1)(B+1)(C+1) ≤ 10^6, így az időigény belefér a 0.1 mp-es korlátba.
*/
/*
Hint 1: || A negyedik kanna tartalma a másik három kanna tartalmából kiszámolható, mert a teljes tej mennyisége mindig A. ||
Hint 2: || Szélességi bejárással járd be az összes elérhető állapotot: egy áttöltésnél a mennyiség a forrás tartalma és a cél szabad helye közül a kisebb. Az elért negyedik-kannabeli értékeket jelöld meg, a többi 1..A közötti érték a kimérhetetlen. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int A, B, C;
    cin >> A >> B >> C;

    // a negyedik kanna (index 3) kapacitása A-nál nagyobb, ezért szinte végtelennek vesszük
    const int INF = 1000000;
    const int cap[4] = {A, B, C, INF};

    // állapot: (a, b, c); a negyedik kanna d = A - a - b - c
    auto id = [&](int a, int b, int c) { return (a * (B + 1) + b) * (C + 1) + c; };
    vector<char> seen((size_t)(A + 1) * (B + 1) * (C + 1), 0);
    vector<char> reachD(A + 1, 0);

    queue<array<int, 3>> q;
    q.push({A, 0, 0});
    seen[id(A, 0, 0)] = 1;
    while (!q.empty()) {
        array<int, 3> cur = q.front();
        q.pop();
        int x[4] = {cur[0], cur[1], cur[2], A - cur[0] - cur[1] - cur[2]};
        reachD[x[3]] = 1;
        for (int i = 0; i < 4; i++) {
            if (x[i] == 0) continue;
            for (int j = 0; j < 4; j++) {
                if (j == i) continue;
                int amount = min(x[i], cap[j] - x[j]);
                if (amount <= 0) continue;
                int y[4] = {x[0], x[1], x[2], x[3]};
                y[i] -= amount;
                y[j] += amount;
                int s = id(y[0], y[1], y[2]);
                if (seen[s]) continue;
                seen[s] = 1;
                q.push({y[0], y[1], y[2]});
            }
        }
    }

    vector<int> missing;
    for (int v = 1; v <= A; v++)
        if (!reachD[v]) missing.push_back(v);

    if (missing.empty()) {
        cout << 0 << '\n';
        return 0;
    }
    cout << missing.size() << '\n';
    for (size_t i = 0; i < missing.size(); i++)
        cout << missing[i] << (i + 1 < missing.size() ? ' ' : '\n');
    return 0;
}
