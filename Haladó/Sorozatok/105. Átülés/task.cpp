/*
Megoldás lényege:
Az ülésrend egy permutáció, amely ciklusokra bontható. Egy nem helyén ülő ciklusban a diákok
egy üres székkel körbe tudnak forogni, és egy k hosszú ciklus rendezéséhez pontosan k+1 lépés kell.

Az összes minimális lépésszám ezért a nemtriviális ciklusok hosszának összege plusz a ciklusok száma.
*/
// Hint 1: || A plusz üres szék miatt egy ciklus körbepörgethető, nem kell külön csere. ||
// Hint 2: || Egy k hosszú rossz ciklushoz k+1 átülés kell. ||

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> seatOfStudent(N + 1);
    for (int seat = 1; seat <= N; ++seat) {
        int student;
        cin >> student;
        seatOfStudent[student] = seat;
    }

    vector<char> vis(N + 1, 0);
    long long ans = 0;
    for (int i = 1; i <= N; ++i) {
        if (vis[i] || seatOfStudent[i] == i) continue;
        int v = i, len = 0;
        while (!vis[v]) {
            vis[v] = 1;
            v = seatOfStudent[v];
            ++len;
        }
        ans += len + 1;
    }

    cout << ans << '\n';
    return 0;
}
