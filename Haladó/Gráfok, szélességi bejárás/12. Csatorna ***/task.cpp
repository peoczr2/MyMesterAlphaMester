/*
Megoldás lényege:
A robot csak azokon a csatornaszakaszokon fér át, amelyek átmérője nagyobb a robot méreténél (A > R), ezért először csak ezeket az éleket vesszük figyelembe.
Ezekből diszjunkt halmazokkal (DSU) építjük fel az összefüggő komponenseket.
Az S pontból kitisztítható szakaszok száma az S-t tartalmazó komponens éleinek száma.
Egy komponensen belül egyetlen indítás elég, mert a robot mindkét irányba haladhat, ezért a további indítások száma az S-től különböző, legalább egy élt tartalmazó komponensek száma.
Az időigény O(M·α(N)), ahol α a lassan növekvő inverz Ackermann-függvény.
*/
/*
Hint 1: || Csak azokat a csatornákat vedd figyelembe, amelyek átmérője nagyobb a robot méreténél (A > R). ||
Hint 2: || Az összefüggő részeket DSU-val kezeld: a csatornák két végpontját uniózd össze, majd a gyökerek alapján számolj. ||
Hint 3: || Az első kimenet az S gyökerű komponens éleinek száma; a második azoknak az S-től különböző komponenseknek a száma, amelyekben van él. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> parent;

int findRoot(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

void unite(int a, int b) {
    a = findRoot(a);
    b = findRoot(b);
    if (a != b) parent[a] = b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s, r;
    cin >> n >> m >> s >> r;

    parent.resize(n + 1);
    for (int i = 0; i <= n; i++) parent[i] = i;

    vector<pair<int, int>> pipes;
    for (int i = 0; i < m; i++) {
        int k, v, a;
        cin >> k >> v >> a;
        if (a > r) {
            pipes.push_back({k, v});
            unite(k, v);
        }
    }

    int rs = findRoot(s);
    long long fromS = 0;
    int extra = 0;
    vector<char> counted(n + 1, 0);
    for (auto [k, v] : pipes) {
        int root = findRoot(k);
        if (root == rs) {
            fromS++;
        } else if (!counted[root]) {
            counted[root] = 1;
            extra++;
        }
    }

    cout << fromS << "\n" << extra << "\n";
    return 0;
}
