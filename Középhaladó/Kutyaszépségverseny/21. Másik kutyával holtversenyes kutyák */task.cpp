/*
Megoldás lényege:
Egy kutya akkor holtversenyes, ha valamelyik szempontban a pontszáma megegyezik egy másik kutya pontszámával, és ez a pontszám eléri az adott szempont alsó határát (csak így értékelhető). Szempontonként és kutyánként összevetjük a pontszámokat, így a holtversenyes kutyák sorszáma megkapható. Az idő O(N²·M), a memóriaigény O(N·M).
*/
/*
Hint 1: || Egy szempontban a kutya pontszámát csak akkor kell figyelembe venni, ha eléri az adott szempont alsó határát; a többi kutya ebben a szempontban nem értékelhető. ||
Hint 2: || Egy kutya ugyanúgy holtversenyes, ha egy másik, szintén értékelhető kutyával ugyanaz a pontszám van ugyanabban a szempontban. Elég minden kutyára és szempontra megnézni, van-e ilyen másik kutya, és a kimenetben minden kutya csak egyszer szerepeljen. ||
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

    vector<int> lista;
    for (int i = 0; i < n; i++) {
        bool holtverseny = false;
        for (int j = 0; j < m && !holtverseny; j++) {
            if (p[i][j] < minPont[j]) continue;
            for (int k = 0; k < n; k++) {
                if (k != i && p[k][j] == p[i][j]) {
                    holtverseny = true;
                    break;
                }
            }
        }
        if (holtverseny) lista.push_back(i + 1);
    }

    cout << lista.size();
    for (int x : lista) cout << ' ' << x;
    cout << '\n';
    return 0;
}
