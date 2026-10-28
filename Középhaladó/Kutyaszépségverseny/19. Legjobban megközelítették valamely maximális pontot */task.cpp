/*
Megoldás lényege:
Szempontonként megkeressük a legnagyobb elért pontot, és a győztesek azok a kutyák, akik ezt kapták, holtverseny esetén mindegyik kutya. Ha ez a legnagyobb pont nem éri el az alsó ponthatárt, a szempontban senki sem értékelhető, ekkor nincs győztes. A győzteseket egy logikai tömbben jelöljük, és a végén a megjelölt kutyák számát és sorszámait írjuk ki. Az időigény O(N·M), a memóriaigény O(N·M).
*/
/*
Hint 1: || Szempontonként külön vizsgáld: mekkora a legnagyobb elért pont, és kik kapták. A holtversenyes kutyák is győztesek. ||
Hint 2: || Tárolj egy N elemű jelölőtömböt. Minden szempontnál, ha a legnagyobb pont legalább az alsó ponthatár, jelöld meg az összes olyan kutyát, akinek pontja ezzel egyenlő. A végén a megjelöltek sorszámait írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> mx(m), mn(m);
    for (int &x : mx) cin >> x;
    for (int &x : mn) cin >> x;

    vector<vector<int>> p(n, vector<int>(m));
    for (auto &row : p)
        for (int &x : row) cin >> x;

    vector<bool> win(n, false);
    for (int j = 0; j < m; j++) {
        int best = -1;
        for (int i = 0; i < n; i++) best = max(best, p[i][j]);
        if (best < mn[j]) continue;
        for (int i = 0; i < n; i++)
            if (p[i][j] == best) win[i] = true;
    }

    vector<int> res;
    for (int i = 0; i < n; i++)
        if (win[i]) res.push_back(i + 1);

    cout << res.size();
    for (int x : res) cout << ' ' << x;
    cout << '\n';
    return 0;
}
