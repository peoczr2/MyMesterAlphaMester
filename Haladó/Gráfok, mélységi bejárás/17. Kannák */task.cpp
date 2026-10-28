/*
Megoldás lényege:
Az összes tej mennyisége M, a kezdetben tele lévő, legnagyobb ismert kanna űrtartalma. A három ismert kanna tartalma (x, y, z) egyértelműen leírja az állapotot, a negyedik kannában lévő mennyiség pedig mindig M - x - y - z. Egy lépésben két kanna között annyi tejet öntünk át, amennyi a forráskannából kifolyhat, vagy a célkannába befér. A negyedik kanna korlátlan, ezért oda mindig az egész forrás kiürül. Az állapotokat szélességi bejárással (BFS) járjuk be, és minden elért állapotban feljegyezzük a negyedik kanna tartalmát. Az 1 és M-1 közötti értékek közül azok a válaszok, amelyek sosem fordulnak elő. Az állapotok száma legfeljebb (A+1)(B+1)(C+1), azaz kb. 64 000, így az idő O(ABC).
*/
/*
Hint 1: || Az összes tej mennyisége állandó: a legnagyobb ismert kanna űrtartalma. A negyedik kannában lévő mennyiség így a másik három kanna tartalmából adódik. ||
Hint 2: || Az állapot a három ismert kanna tartalma. Szélességi bejárással próbáld ki az öntögetéseket (egyik kannából a másikba annyit, amennyi kifolyhat vagy befér), és jegyezd fel, mely negyedik kanna-értékek fordulnak elő. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    array<int, 4> cap;
    cin >> cap[0] >> cap[1] >> cap[2];
    const int INF = 1000000000;
    cap[3] = INF;

    int M = max({cap[0], cap[1], cap[2]});
    int big = 0;
    for (int i = 1; i < 3; ++i)
        if (cap[i] > cap[big]) big = i;

    array<int, 4> start = {0, 0, 0, 0};
    start[big] = M;

    int dimB = cap[1] + 1, dimC = cap[2] + 1;
    vector<char> seen((cap[0] + 1) * dimB * dimC, 0);
    vector<char> reachW(M + 1, 0);

    auto key = [&](const array<int, 4> &s) { return (s[0] * dimB + s[1]) * dimC + s[2]; };

    queue<array<int, 4>> q;
    seen[key(start)] = 1;
    q.push(start);
    while (!q.empty()) {
        array<int, 4> s = q.front();
        q.pop();
        reachW[s[3]] = 1;
        for (int i = 0; i < 4; ++i) {
            if (s[i] == 0) continue;
            for (int j = 0; j < 4; ++j) {
                if (i == j || s[j] >= cap[j]) continue;
                int amount = min(s[i], cap[j] - s[j]);
                array<int, 4> t = s;
                t[i] -= amount;
                t[j] += amount;
                int k = key(t);
                if (!seen[k]) {
                    seen[k] = 1;
                    q.push(t);
                }
            }
        }
    }

    vector<int> ans;
    for (int v = 1; v < M; ++v)
        if (!reachW[v]) ans.push_back(v);

    if (ans.empty()) {
        cout << 0 << "\n";
        return 0;
    }
    for (size_t i = 0; i < ans.size(); ++i) cout << ans[i] << (i + 1 < ans.size() ? ' ' : '\n');
    return 0;
}
