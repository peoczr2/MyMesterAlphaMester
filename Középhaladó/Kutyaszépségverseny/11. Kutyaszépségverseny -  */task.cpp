/*
Megoldás lényege:
Szempontonként külön dolgozunk. Egy kutya a sorban akkor szerepel, ha ebben a szempontban eléri az alsó határt; akit ebből a szempontból kiejtett a határ, az kimarad.
A bennmaradó sorszámokat a pontszámuk szerint csökkenő sorrendbe rendezzük, a holtversenyes kutyák a beolvasási, vagyis sorszám szerinti sorrendben maradnak (stabil rendezés).
A feladat nem rögzíti a holtversenyes kutyák sorrendjét, ezért a stabil rendezés csak egy lehetséges helyes kimenetet ad.
Az idő O(M · N log N), a memóriaigény O(N · M).
*/
/*
Hint 1: || Egy szempontnál csak az adott szempont alsó határát kell nézni: a sorba azok a kutyák kerülnek, akiknek ebben a szempontban a pontszáma legalább a határ. ||
Hint 2: || Gyűjtsd ki a bennmaradó sorszámokat egy vektorba, rendezd őket az adott szempont szerinti pontszám alapján csökkenő sorrendbe (stable_sort), és az M sort egymás után írd ki. ||
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

    for (int i = 0; i < m; i++) {
        vector<int> sorrend;
        for (int j = 0; j < n; j++)
            if (p[j][i] >= minPont[i]) sorrend.push_back(j);

        stable_sort(sorrend.begin(), sorrend.end(),
                    [&](int a, int b) { return p[a][i] > p[b][i]; });

        for (size_t k = 0; k < sorrend.size(); k++) {
            if (k) cout << ' ';
            cout << sorrend[k] + 1;
        }
        cout << '\n';
    }
    return 0;
}
