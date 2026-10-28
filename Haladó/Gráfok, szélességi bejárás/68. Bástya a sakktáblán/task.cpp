/*
Megoldás lényege:
A bástya egy lépésben a sorának vagy oszlopának akadálymentes szakaszán bárhová eljuthat,
ezért nem cellánként, hanem szakaszonként érdemes szélességi bejárást végezni. Egy szakasz
egy maximális, bábumentes, összefüggő sor- vagy oszlopdarab. Amikor egy cellát először érünk el,
a rajta átmenő sor- és oszlopszakasz összes még nem elért cellája megkapja a következő
lépésszámot, a szakaszt pedig feldolgozottnak jelöljük, így minden szakaszt legfeljebb egyszer
járunk be. Az egész bejárás időigénye O(N^2), ami N = 1000 mellett is gyors.
*/
/*
Hint 1: || Egy bástya egy lépésben a sorában vagy oszlopában akadálymentesen bárhová eljuthat, ezért nem kell cellánként lépegetni. ||
Hint 2: || Ha egy cella szakaszát már feldolgoztuk, a szakasz többi cellája is ugyanabban a lépésben elérhető, így nem kell újra bejárni. ||
Hint 3: || Egy szabad cella két szakaszhoz tartozik, a sorához és az oszlopához, ezeket külön-külön kell nyilvántartani. ||
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

    // 0. típus: vízszintes szakasz (sor), 1. típus: függőleges szakasz (oszlop).
    const int dr[2][2] = {{0, 0}, {1, -1}};
    const int dc[2][2] = {{1, -1}, {0, 0}};

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
