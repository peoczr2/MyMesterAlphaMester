/*
Megoldás lényege:
Először kiszűrjük a kieseket: kiesik az a kutya, amelynek valamelyik szempontban az alsó határ alatt van a pontszáma. A bent maradók közül a győztes(ek) az összpontszám szerint legnagyobbak (holtverseny esetén mindkettő). Ezután azok a kutyák a jók, amelyek nem nyertek, és valamelyik szempontban elérik az alsó határt, és a maximum legalább 90 százalékát is (egész számokkal: 10·P ≥ 9·Max). Az idő O(N·M), a memóriaigény O(N·M).
*/
/*
Hint 1: || Egy kutya akkor esik ki, ha bármelyik szempontban a pontszáma kisebb az alsó határnál. A győztes csak a bent maradók közül kerülhet ki, de a kiesett kutya nem nyer. ||
Hint 2: || A bent maradóknál számold ki az összpontszámot (az összes szempont pontjainak összege), keresd meg a legnagyobbat, és minden olyan kutya győztes, akinek ez az összege. ||
Hint 3: || A „legalább 90 százalék” feltétel egész számokkal is leírható: 10 · pontszám ≥ 9 · maximum. Ezt ellenőrizd minden szempontban, de csak akkor, ha a pontszám eléri az adott szempont alsó határát. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> maxPont(m), minPont(m);
    for (int &x : maxPont) cin >> x;
    for (int &x : minPont) cin >> x;

    vector<vector<int>> p(n, vector<int>(m));
    for (auto &sor : p)
        for (int &x : sor) cin >> x;

    vector<bool> kiesett(n, false);
    vector<int> ossz(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (p[i][j] < minPont[j]) kiesett[i] = true;
            ossz[i] += p[i][j];
        }
    }

    int legjobb = -1;
    for (int i = 0; i < n; i++)
        if (!kiesett[i]) legjobb = max(legjobb, ossz[i]);

    vector<bool> nyert(n, false);
    for (int i = 0; i < n; i++)
        nyert[i] = !kiesett[i] && ossz[i] == legjobb;

    vector<int> lista;
    for (int i = 0; i < n; i++) {
        if (nyert[i]) continue;
        bool szinte = false;
        for (int j = 0; j < m; j++) {
            if (p[i][j] >= minPont[j] && 10 * p[i][j] >= 9 * maxPont[j]) szinte = true;
        }
        if (szinte) lista.push_back(i + 1);
    }

    cout << lista.size();
    for (int x : lista) cout << ' ' << x;
    cout << '\n';
    return 0;
}
