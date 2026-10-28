/*
Megoldás lényege:
Szempontonként meghatározzuk a legkisebb pontszámot, de csak az alsó határt elérő (értékelhető) kutyák között. Az a kutya végzett minden szempont szerint utolsón, amelynek minden szempontban ez a minimum a pontszáma; holtverseny az utolsó helyen is számít. Ha valamelyik szempontban nincs értékelhető kutya, akkor senki sem végez minden szempont szerint utolsón. Az idő O(N·M), a memóriaigény O(N·M).
*/
/*
Hint 1: || Szempontonként keresd meg a legkisebb pontszámot, de csak azok közül a kutyák közül, akik eléri az adott szempont alsó határát. ||
Hint 2: || Egy kutya akkor kerül a kimenetbe, ha minden szempontban pontosan ezt a minimumot kapta. Ha valamelyik szempontban nincs ilyen értékelhető kutya, a kimenet 0. ||
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

    vector<int> minErtek(m, INT_MAX);
    for (int j = 0; j < m; j++)
        for (int i = 0; i < n; i++)
            if (p[i][j] >= minPont[j]) minErtek[j] = min(minErtek[j], p[i][j]);

    vector<int> lista;
    for (int i = 0; i < n; i++) {
        bool utolso = true;
        for (int j = 0; j < m; j++) {
            if (minErtek[j] == INT_MAX || p[i][j] != minErtek[j]) {
                utolso = false;
                break;
            }
        }
        if (utolso) lista.push_back(i + 1);
    }

    cout << lista.size();
    for (int x : lista) cout << ' ' << x;
    cout << '\n';
    return 0;
}
