/*
Megoldás lényege:
Az állapot a négy kanna pillanatnyi tartalma. Kezdetben a három ismert kanna közül a legnagyobb tele van (ez adja a tej teljes mennyiségét, M), a többi üres. Az állapotokat szélességi bejárással (BFS) járjuk be: bármely kannából bármely másikba öntünk, annyit, amennyi a forrásban van, illetve amennyi a célban elfér. A negyedik kanna űrtartalma M-nél nagyobb, ezért oda a forrás teljes tartalma beleönthető. A bejárás után összegyűjtjük, milyen mennyiségek fordulnak elő a negyedik kannában, és kiírjuk az 1 és M-1 közötti azokat az értékeket, amelyek nem szerepelnek közöttük (ha nincs ilyen, egyetlen 0-t). Az állapotok száma legfeljebb 31^4, így a futásidő elhanyagolható.
*/
/*
Hint 1: || Állapotnak tekintsd a négy kanna pillanatnyi tartalmát, és a tej teljes mennyisége a három ismert kanna közül a legnagyobbé. Az összes elérhető állapotot szélességi bejárással (BFS) gyűjtsd össze. ||
Hint 2: || Egy lépésben egy kannából egy másikba öntesz: az átöntött mennyiség a forrás tartalma és a cél szabad helye közül a kisebb. A negyedik kanna szabad helye elég nagy, így oda mindig a teljes tartalom átönthető. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int cap[4];
    cin >> cap[0] >> cap[1] >> cap[2];
    cap[3] = 1000; // a negyedik kanna a legnagyobb, a tej (legfeljebb 30 liter) biztosan elfér benne

    int full = 0;
    for (int i = 1; i < 3; ++i)
        if (cap[i] > cap[full]) full = i;
    int M = cap[full];

    // Az állapot kódolása: a négy tartalom 31-es számrendszerben (mindegyik legfeljebb M <= 30).
    auto encode = [](const array<int, 4> &x) { return ((x[0] * 31 + x[1]) * 31 + x[2]) * 31 + x[3]; };

    vector<char> seen(31 * 31 * 31 * 31, 0);
    vector<char> inFourth(M + 1, 0);

    array<int, 4> start = {0, 0, 0, 0};
    start[full] = M;
    queue<array<int, 4>> q;
    q.push(start);
    seen[encode(start)] = 1;

    while (!q.empty()) {
        array<int, 4> s = q.front();
        q.pop();
        inFourth[s[3]] = 1;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j) {
                if (i == j || s[i] == 0) continue;
                int amount = min(s[i], cap[j] - s[j]);
                if (amount <= 0) continue;
                array<int, 4> t = s;
                t[i] -= amount;
                t[j] += amount;
                int code = encode(t);
                if (!seen[code]) {
                    seen[code] = 1;
                    q.push(t);
                }
            }
    }

    vector<int> ans;
    for (int v = 1; v < M; ++v)
        if (!inFourth[v]) ans.push_back(v);
    if (ans.empty()) ans.push_back(0);

    for (size_t i = 0; i < ans.size(); ++i) cout << ans[i] << (i + 1 < ans.size() ? " " : "\n");
    return 0;
}
