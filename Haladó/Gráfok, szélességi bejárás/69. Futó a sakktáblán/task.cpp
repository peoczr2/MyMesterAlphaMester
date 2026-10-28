/*
Megoldás lényege:
A futó átlósan mozog, és egy lépésben egy átló akadálymentes szakaszán bárhová eljuthat. Két
átlóirány van, és minden cella mindkettőhöz tartozik: az egyik a főátlókhoz, a másik a
mellékátlókhoz. Szélességi bejárást végzünk, de nem cellánként lépegetünk: amikor egy cellát
először érünk el, a rajta átmenő átlószakasz összes még nem elért cellája megkapja a következő
lépésszámot, a szakaszt pedig feldolgozottnak jelöljük, így minden szakaszt legfeljebb egyszer
járunk be. A két átlótípus külön jelölése miatt nem keverjük össze a két irányt. Az időigény
O(N^2), ami N = 1000 mellett is gyors.
*/
/*
Hint 1: || A futó lépései átlós szakaszok, így egy lépésben egy teljes akadálymentes átló bejárható. ||
Hint 2: || Minden cella két átlóhoz tartozik, ezért két külön feldolgozottsági jelölést kell vezetni. ||
Hint 3: || Ha egy átlószakaszt már feldolgoztunk, a rajta lévő többi cella távolsága már véglegesnek számít, így újra nem kell bejárni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<string> board(N);
    for (auto& row : board) cin >> row;

    int ks, ko, cs, co;
    cin >> ks >> ko >> cs >> co;
    int start = (ks - 1) * N + (ko - 1);
    int target = (cs - 1) * N + (co - 1);

    if (start == target) {
        cout << 0 << '\n';
        return 0;
    }

    // 0. típus: főátló iránya (+1,+1) és (-1,-1); 1. típus: mellékátló (+1,-1) és (-1,+1).
    const int dr[2][2] = {{1, -1}, {1, -1}};
    const int dc[2][2] = {{1, -1}, {-1, 1}};

    vector<int> dist(N * N, -1);
    vector<char> done[2] = {vector<char>(N * N, 0), vector<char>(N * N, 0)};
    vector<int> q;
    q.reserve(N * N);

    dist[start] = 0;
    q.push_back(start);
    for (size_t head = 0; head < q.size(); ++head) {
        int cur = q[head];
        int r = cur / N, c = cur % N;
        if (board[r][c] != '-') continue;

        for (int k = 0; k < 2; ++k) {
            if (done[k][cur]) continue;
            done[k][cur] = 1;
            for (int d = 0; d < 2; ++d) {
                int nr = r + dr[k][d], nc = c + dc[k][d];
                while (nr >= 0 && nr < N && nc >= 0 && nc < N && board[nr][nc] == '-') {
                    int nid = nr * N + nc;
                    done[k][nid] = 1;
                    if (dist[nid] == -1) {
                        dist[nid] = dist[cur] + 1;
                        q.push_back(nid);
                    }
                    nr += dr[k][d];
                    nc += dc[k][d];
                }
            }
        }
    }

    cout << dist[target] << '\n';
    return 0;
}
